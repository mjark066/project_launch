#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

String serialInput;

float numScrolls = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    
  lcd.begin(16, 2);

  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    lcd.clear();
    lcd.home();
    
    serialInput = Serial.readStringUntil('\n');
    serialInput.trim(); // 
 
    if (!serialInput.compareTo("jump")){ //jumps to second line on lcd screen (i.e., == \n)
      lcd.setCursor(0, 1);
      while (!Serial.available());
      serialInput = Serial.readStringUntil('\n');
      serialInput.trim();
    }

    if (serialInput.length() <  17){
      lcd.print(serialInput);
    }
    else {
      numScrolls = ceil(serialInput.length() / 16.0f);
      while(!Serial.available()){
        for (int ii = 0; ii < numScrolls; ii++){
            lcd.print(serialInput.substring(ii*16, (ii + 1)*16));
            delay(2000);
            lcd.clear();
        }
      } 
    } 
  }
}
