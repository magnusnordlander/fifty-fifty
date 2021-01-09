#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <FlashAsEEPROM.h>
#include <Encoder.h>

#define GRINDER_STATE_IDLE 0
#define GRINDER_STATE_GRINDING 1
#define GRINDER_STATE_MANUAL 2
#define SCREEN_WIDTH 24

const int Encoder_SW_Pin = 4;
const int Encoder_DT_Pin = 3; // Must be interrupt pin
const int Encoder_CLK_Pin = 2; // Must be interrupt pin
const int Manual_Grind_Pin = 14;
const int Ssr_Pin = 15;
const float Grind_Rate = 2.5F; // grams per second

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int Grinder_State = GRINDER_STATE_IDLE;
int Encoder_SW_State = 0;
int Manual_Grind_State = HIGH;
int Timer_Start = 0;
int Encoder_Rotation;
unsigned short Target_Time = 6400;

long Old_Encoder_Position  = 0;

Encoder myEnc(Encoder_DT_Pin, Encoder_CLK_Pin);

void setup(void) {
  pinMode(Manual_Grind_Pin, INPUT_PULLUP);
  pinMode(Ssr_Pin, OUTPUT);

  pinMode(Encoder_SW_Pin, INPUT_PULLUP);
  
  u8g2.begin();

  if (EEPROM.isValid()) {
    Target_Time = readTargetTime();
  }
}

void loop(void) {
  long new_encoder_position = myEnc.read();
  long diff = 0;
  if (new_encoder_position != Old_Encoder_Position) {
    diff = (new_encoder_position - Old_Encoder_Position) * 20;
    Old_Encoder_Position = new_encoder_position;
  }

  
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font


  char target_string[SCREEN_WIDTH];
  float Target_Time_S = (float)Target_Time/1000;
  sprintf(target_string, "Target time: %d.%02d s", (int)Target_Time_S, (int)(Target_Time_S*100)%100);
  u8g2.drawStr(0, 40, target_string);
  
  char target_weight_string[SCREEN_WIDTH];
  float Target_Weight_G = (Target_Time_S * Grind_Rate);
  sprintf(target_weight_string, "Target weight: ~%d.%02d g", (int)Target_Weight_G, (int)(Target_Weight_G*100)%100);
  u8g2.drawStr(0, 50, target_weight_string);

  
  Encoder_SW_State = digitalRead(Encoder_SW_Pin);
  Manual_Grind_State = digitalRead(Manual_Grind_Pin);

  switch (Grinder_State) {
    case GRINDER_STATE_IDLE:
      u8g2.drawStr(0,10,"State: Idle");
      digitalWrite(Ssr_Pin, LOW);

      if (Manual_Grind_State == LOW) {
        Grinder_State = GRINDER_STATE_MANUAL;
        break;
      }
      
      if (Encoder_SW_State == LOW) {
        Grinder_State = GRINDER_STATE_GRINDING;
        Timer_Start = millis();
        saveTargetTime(Target_Time);
      }

      if (diff != 0) {
        if (Target_Time + diff > USHRT_MAX) {
          Target_Time = USHRT_MAX;
        }
        else if (Target_Time + diff < 0) {
          Target_Time = 0;
        } else {
          Target_Time += diff;
        }
      }
      
      break;
    case GRINDER_STATE_MANUAL:
      u8g2.drawStr(0,10,"State: Manual grinding");
      digitalWrite(Ssr_Pin, HIGH);

      if (Manual_Grind_State == HIGH) {
        Grinder_State = GRINDER_STATE_IDLE;
      }
      
      break;
    case GRINDER_STATE_GRINDING:
      int elapsed_ms = elapsed();
      
      char time_string[SCREEN_WIDTH];
      sprintf(time_string, "Time: %d.%02d s", (int)elapsed_ms/1000, (int)(elapsed_ms/10)%100);
      u8g2.drawStr(0,10,"State: GBT");
      u8g2.drawStr(0,20, time_string);
      digitalWrite(Ssr_Pin, HIGH);

      if (elapsed_ms >= Target_Time) {
        Grinder_State = GRINDER_STATE_IDLE;
        Timer_Start = 0;
      }

      if (Manual_Grind_State == LOW) {
        Grinder_State = GRINDER_STATE_MANUAL;
        Timer_Start = 0;
      }
      
      break;     
  }
  
  u8g2.sendBuffer();          // transfer internal memory to the display
}

int elapsed() {
    return millis() - Timer_Start;
}

//*************************************************************************
//        Save Target time to EEPROM @ Pos. MSB->100 & LSB->101
//*************************************************************************
void saveTargetTime(unsigned short Target){
    static unsigned short _Saved_Target = 0;
    
    if (_Saved_Target != Target){
      unsigned short _EEPROM_Target = readTargetTime();
      if (Target != _EEPROM_Target) {
        _Saved_Target != Target;
        byte _High_Byte = Target/255;
        byte _Low_Byte =  Target - (_High_Byte*255); 
        EEPROM.write(100, _High_Byte);
        EEPROM.write(101, _Low_Byte);
        EEPROM.commit();
      } else {
        _Saved_Target = Target;
      }
    }
}

unsigned short readTargetTime() {
  // Read Total Run Time from EEPROM 3 bytes gives 
  byte _High_Byte = EEPROM.read(100);
  byte _Low_Byte = EEPROM.read(101);
  unsigned short Target = _Low_Byte + (_High_Byte*255);
  return Target;
}
