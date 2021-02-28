#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Encoder.h>
#include "NavigationController.h"
#include "ViewControllers/Menus/MenuViewController.h"
#include "ViewControllers/Grinding/ManualGrindViewController.h"
#include "ViewControllers/Settings/PurgeTimeSettingViewController.h"
#include "ViewControllers/Settings/GrindTimeSettingViewController.h"
#include "ViewControllers/Settings/GrindTargetWeightSettingViewController.h"
#include "ViewControllers/Settings/ReactionTimeSettingViewController.h"
#include "ViewControllers/Settings/ScaleDebugViewController.h"
#include "ViewControllers/Grinding/GravimetricGrindViewController.h"
#include "ViewControllers/Settings/ProductivitySettingViewController.h"
#include "ViewControllers/Settings/CalibrationViewController.h"
#include "ViewControllers/Settings/PerformanceDebugViewController.h"
#include "ViewControllers/Grinding/PurgeViewController.h"
#include "ViewControllers/Grinding/TimedGrindViewController.h"
#include "ViewControllers/ScaleViewController.h"
#include "ViewControllers/Menus/MenuItem/ViewControllerMenuItem.h"
#include "ViewControllers/Menus/MenuItem/PopNavigationAndCommitEEPROMMenuItem.h"
#include "ViewControllers/Menus/MenuItem/PurgeMenuItem.h"
#include "ViewControllers/Menus/MenuItem/GrindMenuItem.h"
#include "ViewControllers/Menus/MenuItem/GrindByWeightMenuItem.h"
#include "Settings.h"
#include "ScaleWrapper.h"
#include "ViewControllers/ButtonEvent.h"
#include <types.h>

// DT and CLK must be interrupt pins
#define ENCODER_SW_PIN 4
#define ENCODER_DT_PIN 3
#define ENCODER_CLK_PIN 2

#define MANUAL_GRIND_PIN 14

#define SSR_PIN 15

// DOUT must be interrupt pin
#define ADS1232_PWDN_PIN 10
#define ADS1232_DOUT_PIN 9
#define ADS1232_SCLK_PIN 8

// With the exception of CS, these pins are hardware supported
#define UEXT_SPI_CS_PIN 16
#define UEXT_SPI_SCK_PIN 13
#define UEXT_SPI_MISO_PIN 12
#define UEXT_SPI_MOSI_PIN 11
#define UEXT_I2C_SCL_PIN 19
#define UEXT_I2C_SDA_PIN 18


#ifdef DEBUG_RIG
#define SCROLL_DIRECTION 1
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
#else
#define SCROLL_DIRECTION 1
// Use I2C SCL as SSD1309 DC and I2C SDA as SSD1309 RES
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R2, UEXT_SPI_CS_PIN, UEXT_I2C_SCL_PIN, UEXT_I2C_SDA_PIN);
#endif

int Encoder_SW_State = 0;
long Encoder_Diff = 0;
int Manual_Grind_State = HIGH;

long Old_Encoder_Position  = 0;

microtime_t Button_Press_Started_At = 0;

ButtonEvent currentButtonEvent = BUTTON_INACTIVE;

Encoder myEnc(ENCODER_DT_PIN, ENCODER_CLK_PIN);

ScaleWrapper* scale;
SsrState* ssr = nullptr;
ManualGrindViewController* manualGrindView = nullptr;
NavigationController* nav = nullptr;

TimingStruct timings;

void setup(void) {
    pinMode(MANUAL_GRIND_PIN, INPUT_PULLUP);
    pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

    u8g2.begin();

/*
    delay(5000);
    Serial.begin(9600);
    Serial.println("Starting");
    */

    ssr = new SsrState(SSR_PIN);
    auto settings = new Settings();

    scale = ScaleWrapper::GetInstance(ADS1232_DOUT_PIN, ADS1232_SCLK_PIN, ADS1232_PWDN_PIN, settings);

    manualGrindView = new ManualGrindViewController(ssr);

    auto settingsMenu = new MenuViewController(std::vector<MenuItem*> {{
            new ViewControllerMenuItem("Purge time", new PurgeTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Grind time", new GrindTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Target weight", new GrindTargetWeightSettingViewController(settings)),
            new ViewControllerMenuItem("Reaction time", new ReactionTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Productivity", new ProductivitySettingViewController(settings)),
            new ViewControllerMenuItem("Calibrate (100 g)", new CalibrationViewController(settings, scale)),
            new ViewControllerMenuItem("Scale debug", new ScaleDebugViewController(scale)),
            new ViewControllerMenuItem("Performance debug", new PerformanceDebugViewController()),
            new PopNavigationAndCommitEEPROMMenuItem("Back", settings)
    }});

    auto mainMenu = new MenuViewController(std::vector<MenuItem*> {{
            new PurgeMenuItem(new PurgeViewController(ssr, settings), settings),
            new GrindMenuItem(new TimedGrindViewController(ssr, settings), settings),
            new GrindByWeightMenuItem(new GravimetricGrindViewController(ssr, scale, settings), settings),
            new ViewControllerMenuItem("Scale", new ScaleViewController(scale)),
            new ViewControllerMenuItem("Settings...", settingsMenu),
    }});

    nav = new NavigationController(mainMenu);
}

void updateExternalState() {
    Encoder_Diff = 0;
    long new_encoder_position = myEnc.read();
    if (new_encoder_position != Old_Encoder_Position) {
        Encoder_Diff = (new_encoder_position/4 - Old_Encoder_Position/4);
        #ifdef DEBUG_RIG
        //Serial.println(Encoder_Diff);
        #endif
        Old_Encoder_Position = new_encoder_position;
    }

    Encoder_SW_State = digitalRead(ENCODER_SW_PIN);
    Manual_Grind_State = digitalRead(MANUAL_GRIND_PIN);

    if (Button_Press_Started_At == 0 && Encoder_SW_State == LOW) {
        Button_Press_Started_At = micros();
        currentButtonEvent = BUTTON_PRESS;
    } else if (Button_Press_Started_At > 0 && Encoder_SW_State == LOW) {
        currentButtonEvent = BUTTON_HOLD;
    } else if (Button_Press_Started_At > 0 && Encoder_SW_State == HIGH) {
        microtime_t holdLength = micros() - Button_Press_Started_At;
        if (holdLength > 300000) {
            currentButtonEvent = BUTTON_PRESS_AND_HOLD_LET_UP;
        } else {
            currentButtonEvent = BUTTON_LET_UP;
        }
        Button_Press_Started_At = 0;
    } else { // (Button_Press_Started_At == 0 && Encoder_SW_State == HIGH) {
        currentButtonEvent = BUTTON_INACTIVE;
    }

    scale->refresh();
}

void loop(void) {
    microtime_t start = micros();

    BaseViewController* top = nav->top();

    microtime_t externalStart = micros();
    updateExternalState();

    microtime_t manualStart = micros();
    // Handle manual grind state
    if (top != manualGrindView && Manual_Grind_State == LOW) {
        nav->push(manualGrindView);
    } else if (top == manualGrindView && Manual_Grind_State == HIGH) {
        nav->pop();
    }

    microtime_t buttonStart = micros();
    nav->top()->handleButtonEvent(currentButtonEvent);

    microtime_t rotationStart = micros();
    if (currentButtonEvent == BUTTON_INACTIVE) {
        if (Encoder_Diff != 0) {
            nav->top()->handleRotation(Encoder_Diff * SCROLL_DIRECTION);
        }
    }

    microtime_t tickStart = micros();
    nav->top()->tick(u8g2);

    microtime_t end = micros();

    timings = (TimingStruct){
        .external = manualStart - externalStart,
        .manual = rotationStart - manualStart,
        .rotation = buttonStart - rotationStart,
        .button = tickStart - buttonStart,
        .tick = end - tickStart,
        .loop = end - start,
    };
}