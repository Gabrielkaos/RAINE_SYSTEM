// Raine(????) System code

#include <LiquidCrystal_I2C.h>

// Define Pins
const int soilMoistureSensor = A0;
const int waterLevelPin = A1;
const int pumpPin = 5;
const int alarmPin = 6;

// Define Threshold Values
const int moistureThreshold = 500;
const int waterThreshold = 150;

// Variables
int soilMoisture;
int waterLevel;

LiquidCrystal_I2C lcd(0x27,20,4);

int justWatered = 0;

void setup(){
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin,LOW);
  lcd.init();
  lcd.backlight();

  //lcd.begin();
  lcd.clear();

  //lcd.print("Starting RAINE...");
  //delay(2000);
  //lcd.clear();
  
  pinMode(alarmPin, OUTPUT);
}

void loop() {


  //////////////////////////////////////////////////////
  // Read Water Level Sensor
  waterLevel = analogRead(waterLevelPin);
  //delay(300);
  
  // Check Water Level
  if (waterLevel <= waterThreshold) {
    digitalWrite(alarmPin, HIGH);
    lcd.clear();
    lcd.print("Water Empty!");
    digitalWrite(pumpPin,LOW);
    return;
  } else {
    digitalWrite(alarmPin, LOW);
    lcd.clear();
  }
  //////////////////////////////////////////////////////
  // Read Moisture Sensor
  soilMoisture = analogRead(soilMoistureSensor);

  //delay(800);
  
  // Check Moisture Level
  if (soilMoisture >= moistureThreshold && justWatered == 0){
    lcd.setCursor(0,0);
    lcd.print("Watering....");
    digitalWrite(pumpPin, HIGH);
    delay(2100); // Allow time for watering
    digitalWrite(pumpPin, LOW);
    justWatered = 1;
  }else{
    lcd.setCursor(0,0);
    digitalWrite(pumpPin,LOW);
    lcd.print("No Watering Needed");
    justWatered = 0;
    delay(1000);
  }
  //////////////////////////////////////////////////////

  delay(100);
  lcd.clear();
  lcd.print("Moisture:");
  lcd.setCursor(9,0);
  lcd.print(soilMoisture);
  lcd.setCursor(0,1);
  lcd.print("Water: Not Empty");
  

  delay(2000); // Wait 2 seconds before reading sensors again
  lcd.clear();
}
