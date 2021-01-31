#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <FlashAsEEPROM.h>
#include <Encoder.h>

#define GRINDER_STATE_MENU 0
#define GRINDER_STATE_PURGING 1
#define GRINDER_STATE_GRINDING 2
#define GRINDER_STATE_MANUAL 3

#define SCREEN_WIDTH 24

#define MENU_SENSITIVITY 3
#define SETTING_SENSITIVITY 4
#define ENCODER_SW_DEAD_TIME 200

#define MENU_STATE_MAIN 0
#define MENU_STATE_SETTINGS 1
#define MENU_STATE_SETTINGS_PURGE_TIME 2
#define MENU_STATE_SETTINGS_GRIND_TIME 3
#define MENU_STATE_SETTINGS_PRODUCTIVITY 4

#define MAIN_MENU_ITEMS 3
#define MAIN_MENU_ITEM_PURGE 0
#define MAIN_MENU_ITEM_TIMED 1
#define MAIN_MENU_ITEM_SETTINGS 2

#define SETTINGS_MENU_ITEMS 4
#define SETTINGS_MENU_ITEM_PURGE_TIME 0
#define SETTINGS_MENU_ITEM_GRIND_TIME 1
#define SETTINGS_MENU_ITEM_PRODUCTIVITY 2
#define SETTINGS_MENU_ITEM_EXIT 3


const int Encoder_SW_Pin = 4;
const int Encoder_DT_Pin = 3; // Must be interrupt pin
const int Encoder_CLK_Pin = 2; // Must be interrupt pin
const int Manual_Grind_Pin = 14;
const int Ssr_Pin = 15;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int Grinder_State = GRINDER_STATE_MENU;
int Encoder_SW_State = 0;
long Encoder_Diff = 0;
int Manual_Grind_State = HIGH;
int Timer_Start = 0;
int Encoder_Rotation;

unsigned short Menu_State = MENU_STATE_MAIN;

unsigned short Main_Menu_Position = 0;
short Main_Menu_Overflow = 0;

unsigned short Settings_Menu_Position = 0;
short Settings_Menu_Overflow = 0;

unsigned short Productivity = 2500; // milligrams per second
unsigned short Purge_Target_Time = 1000;
unsigned short Grind_Target_Time = 6400;

bool Has_EEPROM_Changes = false;

long Old_Encoder_Position  = 0;

Encoder myEnc(Encoder_DT_Pin, Encoder_CLK_Pin);

void setup(void) {
  pinMode(Manual_Grind_Pin, INPUT_PULLUP);
  pinMode(Ssr_Pin, OUTPUT);

  pinMode(Encoder_SW_Pin, INPUT_PULLUP);
  
  u8g2.begin();
  Serial.begin(9600);

  if (EEPROM.isValid()) {
    Purge_Target_Time = readPurgeTargetTime();
    Grind_Target_Time = readGrindTargetTime();
    Productivity = readProductivity();

    validateEEPROMData();
  }
}

void validateEEPROMData() {
  if (Purge_Target_Time > 10000) {
    Purge_Target_Time = 1000;
  }

  if (Grind_Target_Time > 20000) {
    Grind_Target_Time = 6400;
  }

  if (Productivity > 16000) {
    Productivity = 2500;
  }
}

void loop(void) {
  updateExternalState();

  updateSsr();

  updateState();

  renderDisplay();
}


void updateExternalState() {
  Encoder_Diff = 0;
  long new_encoder_position = myEnc.read();
  if (new_encoder_position != Old_Encoder_Position) {
    Encoder_Diff = (new_encoder_position - Old_Encoder_Position);
    Old_Encoder_Position = new_encoder_position;
  }

  Encoder_SW_State = digitalRead(Encoder_SW_Pin);
  Manual_Grind_State = digitalRead(Manual_Grind_Pin);

}

void updateSsr() {
    switch (Grinder_State) {
    case GRINDER_STATE_MENU:
      digitalWrite(Ssr_Pin, LOW);
      break;
    case GRINDER_STATE_MANUAL:
    case GRINDER_STATE_PURGING:
    case GRINDER_STATE_GRINDING:
      digitalWrite(Ssr_Pin, HIGH);
      break;     
  }
}

void transitionToTimedGrinding() {
  Grinder_State = GRINDER_STATE_GRINDING;
  Timer_Start = millis();
}

void transitionToPurging() {
  Grinder_State = GRINDER_STATE_PURGING;
  Timer_Start = millis();
}

void transitionToManual(bool resetTimer = true) {
  Grinder_State = GRINDER_STATE_MANUAL;
  if (resetTimer) {
    Timer_Start = millis();    
  }
}

void transitionToMenu() {
  Grinder_State = GRINDER_STATE_MENU;
  Timer_Start = 0;
}

void handleMainMenu() {
      if (Encoder_SW_State == LOW) {
        switch (Main_Menu_Position) {
          case MAIN_MENU_ITEM_PURGE:
            return transitionToPurging();
          case MAIN_MENU_ITEM_TIMED:
            return transitionToTimedGrinding();
          case MAIN_MENU_ITEM_SETTINGS:
            Settings_Menu_Position = 0;
            Menu_State = MENU_STATE_SETTINGS;
            delay(ENCODER_SW_DEAD_TIME);
            return;
        }
      }

      Main_Menu_Overflow += Encoder_Diff;

      if (Main_Menu_Overflow > MENU_SENSITIVITY) {
        Main_Menu_Overflow = 0;
        Main_Menu_Position = (Main_Menu_Position + 1) % MAIN_MENU_ITEMS;
      }

      if (Main_Menu_Overflow < -MENU_SENSITIVITY) {
        Main_Menu_Overflow = 0;
        if (Main_Menu_Position == 0) {
          Main_Menu_Position = MAIN_MENU_ITEMS-1;
        } else {
          Main_Menu_Position = (Main_Menu_Position - 1) % MAIN_MENU_ITEMS;          
        }
      }
}

void handleSettingsMenu() {
      if (Encoder_SW_State == LOW) {
        switch (Settings_Menu_Position) {
          case SETTINGS_MENU_ITEM_PURGE_TIME:
            Menu_State = MENU_STATE_SETTINGS_PURGE_TIME;
            break;
          case SETTINGS_MENU_ITEM_GRIND_TIME:
            Menu_State = MENU_STATE_SETTINGS_GRIND_TIME;
            break;
          case SETTINGS_MENU_ITEM_PRODUCTIVITY:
            Menu_State = MENU_STATE_SETTINGS_PRODUCTIVITY;
            break;
          case SETTINGS_MENU_ITEM_EXIT:
            commitEEPROM();
            Menu_State = MENU_STATE_MAIN;
            break;
        }

        delay(ENCODER_SW_DEAD_TIME);
        return;
      }

      Settings_Menu_Overflow += Encoder_Diff;

      if (Settings_Menu_Overflow > MENU_SENSITIVITY) {
        Settings_Menu_Overflow = 0;
        Settings_Menu_Position = (Settings_Menu_Position + 1) % SETTINGS_MENU_ITEMS;
      }

      if (Settings_Menu_Overflow < -MENU_SENSITIVITY) {
        Settings_Menu_Overflow = 0;
        if (Settings_Menu_Position == 0) {
          Settings_Menu_Position = SETTINGS_MENU_ITEMS-1;
        } else {
          Settings_Menu_Position = (Settings_Menu_Position - 1) % SETTINGS_MENU_ITEMS;          
        }
      }
}

void handlePurgeTimeMenu() {
      if (Encoder_SW_State == LOW) {
        savePurgeTargetTime(Purge_Target_Time);
        Menu_State = MENU_STATE_SETTINGS;
        delay(ENCODER_SW_DEAD_TIME);
        return;
      }

      int amplified_encoder_diff = Encoder_Diff * SETTING_SENSITIVITY;

      if (amplified_encoder_diff != 0) {
        if (Purge_Target_Time + amplified_encoder_diff > USHRT_MAX) {
          Purge_Target_Time = USHRT_MAX;
        }
        else if (Purge_Target_Time + amplified_encoder_diff < 0) {
          Purge_Target_Time = 0;
        } else {
          Purge_Target_Time += amplified_encoder_diff;
        }
      }
}

void handleGrindTimeMenu() {
      if (Encoder_SW_State == LOW) {
        saveGrindTargetTime(Grind_Target_Time);
        Menu_State = MENU_STATE_SETTINGS;
        delay(ENCODER_SW_DEAD_TIME);
        return;
      }

      int amplified_encoder_diff = Encoder_Diff * SETTING_SENSITIVITY;

      if (amplified_encoder_diff != 0) {
        if (Grind_Target_Time + amplified_encoder_diff > USHRT_MAX) {
          Grind_Target_Time = USHRT_MAX;
        }
        else if (Grind_Target_Time + amplified_encoder_diff < 0) {
          Grind_Target_Time = 0;
        } else {
          Grind_Target_Time += amplified_encoder_diff;
        }
      }
}

void handleProductivityMenu() {
      if (Encoder_SW_State == LOW) {
        saveProductivity(Productivity);
        Menu_State = MENU_STATE_SETTINGS;
        delay(ENCODER_SW_DEAD_TIME);
        return;
      }

      int amplified_encoder_diff = Encoder_Diff * SETTING_SENSITIVITY;

      if (amplified_encoder_diff != 0) {
        if (Productivity + amplified_encoder_diff > USHRT_MAX) {
          Productivity = USHRT_MAX;
        }
        else if (Productivity + amplified_encoder_diff < 0) {
          Productivity = 0;
        } else {
          Productivity += amplified_encoder_diff;
        }
      }
}


void updateState() {
  switch (Grinder_State) {
    case GRINDER_STATE_MENU:
      if (Manual_Grind_State == LOW) {
        return transitionToManual();
      }

      switch (Menu_State) {
        case MENU_STATE_MAIN:
          return handleMainMenu();
        case MENU_STATE_SETTINGS:
          return handleSettingsMenu();
        case MENU_STATE_SETTINGS_PURGE_TIME:
          return handlePurgeTimeMenu();
        case MENU_STATE_SETTINGS_GRIND_TIME:
          return handleGrindTimeMenu();
        case MENU_STATE_SETTINGS_PRODUCTIVITY:
          return handleProductivityMenu();
      }
      
      break;
    case GRINDER_STATE_MANUAL:
      if (Manual_Grind_State == HIGH) {
        return transitionToMenu();
      }
      
      break;
    case GRINDER_STATE_GRINDING:
      return handleTimedState(Grind_Target_Time);
    case GRINDER_STATE_PURGING:
      return handleTimedState(Purge_Target_Time);
  }
}

void handleTimedState(unsigned short targetTime) {
  int elapsed_grind_ms = elapsed();

  if (elapsed_grind_ms >= targetTime) {
    transitionToMenu();
  }

  if (Manual_Grind_State == LOW) {
    transitionToManual(false);
  }
}


//*************************************************************************
//        Display handling
//*************************************************************************

void renderDisplay() {
  preRender();

  switch (Grinder_State) {
    case GRINDER_STATE_MENU:
      switch (Menu_State) {
        case MENU_STATE_MAIN:
          renderMainMenu();
          break;
        case MENU_STATE_SETTINGS:
          renderSettingsMenu();
          break;
        case MENU_STATE_SETTINGS_PURGE_TIME:
          renderPurgeTimeMenu();
          break;
        case MENU_STATE_SETTINGS_GRIND_TIME:
          renderGrindTimeMenu();
          break;
        case MENU_STATE_SETTINGS_PRODUCTIVITY:
          renderProductivityMenu();
          break;
      }
      break;
    case GRINDER_STATE_MANUAL:
      renderManualGrindDisplay();
      break;
    case GRINDER_STATE_PURGING:
      renderPurgingDisplay();
      break;
    case GRINDER_STATE_GRINDING:
      renderTimedGrindingDisplay();
      break;
  }

  postRender();
}

void preRender() {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);
}

void postRender() {
  u8g2.sendBuffer();          // transfer internal memory to the display
}

void renderMainMenu() {
  char timed_grind_string[SCREEN_WIDTH];
  float Grind_Target_Time_S = (float)Grind_Target_Time/1000;
  sprintf(timed_grind_string, "Timed grind (%d.%02d s)", (int)Grind_Target_Time_S, (int)(Grind_Target_Time_S*100)%100);

  char purge_string[SCREEN_WIDTH];
  float Purge_Target_Time_S = (float)Purge_Target_Time/1000;
  sprintf(purge_string, "Purge (%d.%02d s)", (int)Purge_Target_Time_S, (int)(Purge_Target_Time_S*100)%100);

  u8g2.drawBox(0, 2+(Main_Menu_Position*14), 128, 16);
  
  u8g2.drawStr(8,14,purge_string);
  u8g2.drawStr(8,28,timed_grind_string);
  u8g2.drawStr(8,42,"Settings...");
}

void renderSettingsMenu() {
  u8g2.drawBox(0, 2+(Settings_Menu_Position*14), 128, 16);
  
  u8g2.drawStr(8,14,"Set purge time");
  u8g2.drawStr(8,28,"Set grind time");
  u8g2.drawStr(8,42,"Set productivity");
  if (Has_EEPROM_Changes) {
    u8g2.drawStr(8,56,"Save & Exit");    
  } else {
    u8g2.drawStr(8,56,"Exit");  
  }
}

void renderPurgeTimeMenu() {
  char purge_string[SCREEN_WIDTH];
  float Purge_Target_Time_S = (float)Purge_Target_Time/1000;
  sprintf(purge_string, "%d.%02d s", (int)Purge_Target_Time_S, (int)(Purge_Target_Time_S*100)%100);
  
  char target_weight_string[SCREEN_WIDTH];
  float Target_Weight_G = (Purge_Target_Time_S * ((float)Productivity/1000));
  sprintf(target_weight_string, "Approx. %d.%02d g", (int)Target_Weight_G, (int)(Target_Weight_G*100)%100);
  u8g2.drawStr(0, 56, target_weight_string);
  
  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  u8g2.drawStr(24,32,purge_string);
}

void renderGrindTimeMenu() {
  char grind_string[SCREEN_WIDTH];
  float Grind_Target_Time_S = (float)Grind_Target_Time/1000;
  sprintf(grind_string, "%d.%02d s", (int)Grind_Target_Time_S, (int)(Grind_Target_Time_S*100)%100);
  
  char target_weight_string[SCREEN_WIDTH];
  float Target_Weight_G = (Grind_Target_Time_S * ((float)Productivity/1000));
  sprintf(target_weight_string, "Approx. %d.%02d g", (int)Target_Weight_G, (int)(Target_Weight_G*100)%100);
  u8g2.drawStr(0, 56, target_weight_string);
  
  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  u8g2.drawStr(24,32,grind_string);
}

void renderProductivityMenu() {
  char productivity_string[SCREEN_WIDTH];
  float Productivity_S = (float)Productivity/1000;
  sprintf(productivity_string, "%d.%02d g/s", (int)Productivity_S, (int)(Productivity_S*100)%100);
    
  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  u8g2.drawStr(8,42,productivity_string);
}

void renderManualGrindDisplay() {
  u8g2.setFont(u8g2_font_helvB12_te);
  u8g2.drawStr(36,56, "Manual");

  int elapsed_ms = elapsed();
  
  char time_string[SCREEN_WIDTH];
  sprintf(time_string, "%d.%02d", (int)elapsed_ms/1000, (int)(elapsed_ms/10)%100);

  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  if (elapsed_ms < 10000) {
    u8g2.drawStr(24,32,time_string);
    u8g2.drawStr(96, 32, "s");
  } else {
    u8g2.drawStr(8,32,time_string);
    u8g2.drawStr(100, 32, "s");
  }
}

void renderPurgingDisplay() {
  u8g2.setFont(u8g2_font_helvB12_te);
  u8g2.drawStr(32,56, "Purging");

  int elapsed_ms = elapsed();
  int remaining_ms = Purge_Target_Time - elapsed_ms;
  
  char time_string[SCREEN_WIDTH];
  sprintf(time_string, "%d.%02d", (int)remaining_ms/1000, (int)(remaining_ms/10)%100);

  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  if (remaining_ms < 10000) {
    u8g2.drawStr(24,32,time_string);
    u8g2.drawStr(96, 32, "s");
  } else {
    u8g2.drawStr(8,32,time_string);
    u8g2.drawStr(100, 32, "s");
  }
}

void renderTimedGrindingDisplay() {
  u8g2.setFont(u8g2_font_helvB12_te);
  u8g2.drawStr(32,56, "Grinding");

  int elapsed_ms = elapsed();
  int remaining_ms = Grind_Target_Time - elapsed_ms;
  
  char time_string[SCREEN_WIDTH];
  sprintf(time_string, "%d.%02d", (int)remaining_ms/1000, (int)(remaining_ms/10)%100);

  u8g2.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
  if (remaining_ms < 10000) {
    u8g2.drawStr(24,32,time_string);
    u8g2.drawStr(96, 32, "s");
  } else {
    u8g2.drawStr(8,32,time_string);
    u8g2.drawStr(100, 32, "s");
  }
}

int elapsed() {
    return millis() - Timer_Start;
}



//*************************************************************************
//        EEPROM setting emulation
//  Grind target time: EEPROM @ Pos. MSB->100 & LSB->101
//  Purge target time: EEPROM @ Pos. MSB->102 & LSB->103
//  Performance: EEPROM @ Pos. MSB->104 & LSB->105
//*************************************************************************
void saveGrindTargetTime(unsigned short Target){
    static unsigned short _Saved_Grind_Target = 0;
    
    if (_Saved_Grind_Target != Target){
      unsigned short _EEPROM_Target = readGrindTargetTime();
      if (Target != _EEPROM_Target) {
        _Saved_Grind_Target != Target;
        byte _High_Byte = Target/255;
        byte _Low_Byte =  Target - (_High_Byte*255); 
        EEPROM.write(100, _High_Byte);
        EEPROM.write(101, _Low_Byte);
        Has_EEPROM_Changes = true;
      } else {
        _Saved_Grind_Target = Target;
      }
    }
}

unsigned short readGrindTargetTime() {
  // Read Total Run Time from EEPROM 3 bytes gives 
  byte _High_Byte = EEPROM.read(100);
  byte _Low_Byte = EEPROM.read(101);
  unsigned short Target = _Low_Byte + (_High_Byte*255);
  return Target;
}

void savePurgeTargetTime(unsigned short Target){
    static unsigned short _Saved_Purge_Target = 0;
    
    if (_Saved_Purge_Target != Target){
      unsigned short _EEPROM_Target = readPurgeTargetTime();
      if (Target != _EEPROM_Target) {
        _Saved_Purge_Target != Target;
        byte _High_Byte = Target/255;
        byte _Low_Byte =  Target - (_High_Byte*255); 
        EEPROM.write(102, _High_Byte);
        EEPROM.write(103, _Low_Byte);
        Has_EEPROM_Changes = true;
      } else {
        _Saved_Purge_Target = Target;
      }
    }
}

unsigned short readPurgeTargetTime() {
  // Read Total Run Time from EEPROM 3 bytes gives 
  byte _High_Byte = EEPROM.read(102);
  byte _Low_Byte = EEPROM.read(103);
  unsigned short Target = _Low_Byte + (_High_Byte*255);
  return Target;
}


void saveProductivity(unsigned short Productivity_Target){
    static unsigned short _Saved_Productivity = 0;
    
    if (_Saved_Productivity != Productivity_Target){
      unsigned short _EEPROM_Productivity = readProductivity();
      if (Productivity_Target != _EEPROM_Productivity) {
        _Saved_Productivity != Productivity_Target;
        byte _High_Byte = Productivity_Target/255;
        byte _Low_Byte =  Productivity_Target - (_High_Byte*255); 
        EEPROM.write(104, _High_Byte);
        EEPROM.write(105, _Low_Byte);
        Has_EEPROM_Changes = true;
      } else {
        _Saved_Productivity = Productivity_Target;
      }
    }
}

unsigned short readProductivity() {
  // Read Total Run Time from EEPROM 3 bytes gives 
  byte _High_Byte = EEPROM.read(104);
  byte _Low_Byte = EEPROM.read(105);
  unsigned short Productivity_Target = _Low_Byte + (_High_Byte*255);
  return Productivity_Target;
}

void commitEEPROM() {
  if (Has_EEPROM_Changes) {
    EEPROM.commit();
    Has_EEPROM_Changes = false;
  }
}
