#include <Arduino.h>
#include <LiquidCrystal.h>
#include <cmath>

//lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long counterTime = 0;
unsigned long indicatorTime = 0;
const long counterInterval = 100;
const long indicatorInterval = 2500; 
float counter = 40.0f;
int indicator = 0;
bool wishes = false;
String text = " ";

//buzzer
unsigned long buzzerTime = 0;
unsigned long buzzerInterval = 0;
int buzzerCounter = 0;
bool playBuzzer = false;


//custom characters
byte exclamation[] = {
  B10101,
  B10101,
  B10101,
  B10101,
  B10101,
  B00000,
  B10101,
  B00000
};

const int buttonPin = 6;

void setup() {
  lcd.begin(16, 2);
  lcd.noBacklight();
  lcd.createChar(0, exclamation);
  pinMode(8, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  while(digitalRead(buttonPin) == HIGH) { //break
    delay(10); 
  }

  delay(1000);
}

void loop() {
  unsigned long curTime = millis();
  if(counter > 0){
    if(curTime - counterTime >= counterInterval) {
      counterTime = curTime; 
      counter-=0.1;
      lcd.setCursor(4, 0);
      if(counter < 10){
        lcd.print(" ");
      }
      lcd.print(abs(counter), 1);
      lcd.print(" sec  ");
      lcd.setCursor(0, 1);
    }
    if(curTime - indicatorTime >= indicatorInterval) {
      indicatorTime = curTime;
      indicator +=1;
      lcd.setCursor(0, 1);
      for(int i = 0; i<indicator; i++){
        lcd.write(255);
      }
    }
    if(curTime - buzzerTime >= buzzerInterval){
      buzzerTime = curTime;
      if(playBuzzer){
        digitalWrite(8, LOW);
        buzzerInterval = 1140-20*buzzerCounter;
        playBuzzer = false;
        Serial.print(buzzerInterval);
      }
      else{
        digitalWrite(8, HIGH);
        buzzerInterval = 150;
        buzzerCounter +=1;
        playBuzzer = true;
      }
    }
  }
  else if(counter <= 0 && wishes == false){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  SZCZESLIWEGO  ");
    lcd.setCursor(0, 1);
    lcd.print("  NOWEGO ROKU");
    lcd.write(byte(0));
  
    wishes = true;
  }
}