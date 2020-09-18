#include <Servo.h> 
#include <LiquidCrystal.h>
#include <Keypad.h>
#include "DHT.h"
#include <String.h>

// DHT
#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// SERVO
Servo myservo; 
int pos = 90;   // initial position
int sens1 = A0; // LRD 1 pin
int sens2 = A1; //LDR 2 pin
int servoHighestLimit=180;
int servoLowestLimit=0;
int tolerance = 2;


// FLAME BUZZER LED
int flame=7;
int buzzer=8;
int led=10;

// LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// KEYPAD
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int servoLimit=0;
String testString = "";
char loopkey;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  pinMode(flame, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode (26, INPUT);//Column 1
  pinMode (27, INPUT);//Column 2
  pinMode (28, INPUT);//Column 3
  pinMode (29, INPUT);//Row 1
  pinMode (22, INPUT);//Row 2
  pinMode (23, INPUT);//Row 3
  pinMode (24, INPUT);//Row 4
  
  myservo.write(pos);
  delay(2000); // a 2 seconds delay while we position the solar panel
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  dht.begin();
}  

void displayTempHumidity(){
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
}

int flameTrack(){
  //flame
  int flameValue=digitalRead(flame);
  if(flameValue==HIGH){
    return 1;
//    digitalWrite(buzzer, HIGH);
//    digitalWrite(led, HIGH);
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("FIRE");
  }else{
    return 0;
//    servoControl();
//    digitalWrite(buzzer, LOW);
//    digitalWrite(led, LOW);
//    lcd.setCursor(12, 0);
//    lcd.print("    ");
  }
}

void servoControl(){
  int val1 = analogRead(sens1); // read the value of sensor 1
  int val2 = analogRead(sens2); // read the value of sensor 2

  if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    //do nothing if the difference between values is within the tolerance limit
  } else {    
    if(val1 > val2)
    {
      pos = --pos;
    }
    if(val1 < val2) 
    {
      pos = ++pos;
    }
  }

  if(pos > servoHighestLimit) { pos = servoHighestLimit; } // reset to highest limit (Default 180) if it goes higher
  if(pos < servoLowestLimit) { pos = servoLowestLimit; } // reset to lowest limit (Default 0) if it goes lower
  
  myservo.write(pos); // write the position to servo
  delay(50);
}

void tempRead(){
  
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int flame = flameTrack();
  if(t<20){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insufficient temp");
    lcd.setCursor(0,1);
    lcd.print("Solar OFF");
    lcd.clear();
  }else if(h>60){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Raining");
    lcd.setCursor(0,1);
    lcd.print("Solar OFF");
    lcd.clear();
  }else if(flame == 1){
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE");
  }
  else{
    displayTempHumidity();
    lcd.setCursor(6, 0);
    lcd.print(t);
    lcd.setCursor(6, 1);
    lcd.print(h);
    servoControl();
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    lcd.setCursor(12, 0);
    lcd.print("    ");
  }
}


void keypadServoControl(){
  char customKey = customKeypad.getKey();
    if(customKey=='*'){
      testString = "";
      while(1){
        loopkey=customKeypad.waitForKey();
        if(loopkey=='#'){
          break;
        }else{
          testString.concat(loopkey);
        }
      }
      servoHighestLimit=testString.toInt();
      Serial.println("Servo Highest Limit: ");
      Serial.print(servoHighestLimit);
    }else if(customKey=='#'){
      testString = "";
      while(1){
        loopkey=customKeypad.waitForKey();
        if(loopkey=='*'){
          break;
        }else{
          testString.concat(loopkey);
        }
      }
      servoLowestLimit=testString.toInt();
      Serial.println("Servo Lowest Limit: ");
      Serial.print(servoLowestLimit);
    }
}


void loop() 
{ 
  //flameTrack();
  tempRead();
  keypadServoControl();
}
