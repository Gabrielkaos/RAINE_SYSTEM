// Raine(????) System code

#include <LiquidCrystal_I2C.h>

// Define Pins
const int soilMoistureSensor = A0;
const int waterLevelPin = A1;
const int pumpPin = 4;
const int alarmPin = 6;

// Define Threshold Values
const int moistureThreshold = 500;
const int waterThreshold = 150;

// Variables
int soilMoisture;
int waterLevel;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin,LOW);

  lcd.init();
  lcd.backlight();

  //lcd.begin();
  lcd.clear();

  lcd.print("Starting RAINE...");
  delay(2000);
  lcd.clear();
  
  Serial.begin(9600);
  pinMode(alarmPin, OUTPUT);
}

void loop() {
  //////////////////////////////////////////////////////
  // 
  //////////////////////////////////////////////////////


  //////////////////////////////////////////////////////
  // Read Water Level Sensor
  waterLevel = analogRead(waterLevelPin);
  delay(300);
  
  // Check Water Level
  if (waterLevel <= waterThreshold) {
    Serial.println(waterLevel);
    digitalWrite(alarmPin, HIGH);
    return;
  } else {
    Serial.println(waterLevel);
    digitalWrite(alarmPin, LOW);
  }
  //////////////////////////////////////////////////////
  
  
  // Read Moisture Sensor
  soilMoisture = analogRead(soilMoistureSensor);

  delay(800);
  
  // Check Moisture Level
  if (soilMoisture >= moistureThreshold) {
    lcd.setCursor(0,0);
    lcd.print("Watering....");
    digitalWrite(pumpPin, HIGH);
    delay(10000); // Allow time for watering
    digitalWrite(pumpPin, LOW);
  }else{
    lcd.setCursor(0,0);
    lcd.print("No Watering Needed");
    delay(1000);
  }
  
  //////////////////////////////////////////////////////



  

  lcd.clear();
  // Print Values to Serial Monitor
  Serial.print("Moisture: ");
  Serial.println(soilMoisture);
  Serial.print("Has Water: ");
  Serial.println(waterLevel);

  lcd.print("Moisture:");
  lcd.setCursor(9,0);
  lcd.print(soilMoisture);
  

  delay(5000); // Wait 5 seconds before reading sensors again
  lcd.clear();
}
