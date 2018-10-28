/***************************************************************
---------------- SmartGardenSoft - Version 1.0 ---------------- 
Authors : Sébastien Serre, Mehdi Bahnis
Last Update : 22-05-2017
***************************************************************/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

/****** Variables ******/

boolean PumpON = false;
boolean LightON = true;

int pinSensorHumidity = A0; 
int pinSensorTemp = A1;
int pinSensorWater = A2;

int pinSensorLight = 8;
int pinLight = 6;
int pinPump = 7;

int sensorValueHumidity;
int sensorValueLight;
int sensorValueTemp;
int sensorValueWater;


/****** Arrosage ******/

bool getHumidityValue() {

  sensorValueHumidity = analogRead(pinSensorHumidity);
  
  if (sensorValueHumidity > 700) {
    return true;
  }
  return false;
}

/****** Eclairage ******/

bool getLightValue() {
  
  sensorValueLight = digitalRead(pinSensorLight);
  
  if (sensorValueLight == 1) {
    return true;
  }
  return false; 
}

/****** Température *****/

int getTempValue() {
  
  sensorValueTemp = analogRead(pinSensorTemp);

  lcd.setCursor(5, 3);
  lcd.print("Temp : ");
  lcd.write(sensorValueTemp);

  return sensorValueTemp;
  }

  /******** Niveau D'eau **********/

int getWaterValue() {
  
  sensorValueWater = analogRead(pinSensorWater);

  lcd.setCursor(5, 2);
  lcd.print("Water : ");
  lcd.write(sensorValueWater);

  return sensorValueWater;
  }

  /******** Humidité *********/

  
int getHumidityTest() {
  
  sensorValueHumidity = analogRead(pinSensorHumidity);

  lcd.setCursor(5, 2);
  lcd.print("Humidity : ");
  lcd.write(sensorValueHumidity);

  return sensorValueHumidity;
  }

/****** Relais ******/

void relay() {

  if (PumpON == true) {
    digitalWrite(pinPump, LOW);
  }
  if (LightON == true) {
    digitalWrite(pinLight, LOW);
  }
}

/****** Ecran LCD ******/

void manageLCD() {

  clearLCD();
  
  if (PumpON == true) { //Arrosage en cours
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.write(byte(4));
    lcd.print("  Arrosage  ");
    lcd.write(byte(4));

    lcd.setCursor(0, 2);
    lcd.print("  ");
    lcd.write(byte(4));
    lcd.print("   en cours   ");
    lcd.write(byte(4));
  }

  if (PumpON == false) {   
  
  if (LightON == true) {
    lcd.setCursor(0, 3);
    lcd.print("LIGHT : ON");    
  }
  if (LightON == false) {
    lcd.setCursor(0, 3);
    lcd.print("LIGHT : OFF");    
  }
  
}
}

void clearLCD () {

 lcd.setCursor(0,0);
 lcd.print("                     ");
 lcd.setCursor(0,1);
 lcd.print("                     ");
 lcd.setCursor(0,2);
 lcd.print("                     ");
 lcd.setCursor(0,3);
 lcd.print("                     ");
  
}

/****** LCD Bytes ******/

byte celcius[8] = {
  B01000,
  B10100,
  B01000,
  B00011,
  B00100,
  B00100,
  B00011,
};  

byte sun[8] = {
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000,
  B00000,
};  

byte humidity[8] = {
  B00100,
  B01110,
  B11111,
  B01000,
  B00010,
  B01000,
  B00010,
  B00000,
};

byte temp[8] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110,
};

byte water[8] = {
  B00100,
  B01110,
  B01110,
  B11111,
  B11101,
  B11111,
  B01110,
  B00000,
};

void setup() {
  Serial.begin(9600);

  //pinDigital
  pinMode(pinSensorLight, INPUT);
  pinMode(pinPump, OUTPUT);
  pinMode(pinLight, OUTPUT);
  
  

  //initialisation pin
  digitalWrite(pinLight, HIGH); // Turn OFF (default)
  digitalWrite(pinPump, HIGH); // Turn OFF = HIGH (default);

  //LCD
  lcd.begin(20, 4);
  lcd.createChar(0, celcius);
  lcd.createChar(1, sun);
  lcd.createChar(2, humidity);
  lcd.createChar(3, temp);
  lcd.createChar(4, water);

  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  delay(1000);
  lcd.setCursor(19, 0);
  lcd.write(byte(2));
  delay(1000);
  lcd.setCursor(0, 3);
  lcd.write(byte(3));
  delay(1000);
  lcd.setCursor(19, 3);
  lcd.write(byte(4));
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("    SmartGarden");
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("  ProjetTransverse");
  delay(5000);
}

void loop() {

 // PumpON = getHumidityValue ();
 // LightON = getLightValue ();


  if (PumpON == true) {
    digitalWrite(pinPump, LOW);
  } else {
    digitalWrite(pinPump, HIGH);
  }

  if (LightON == true) {
    digitalWrite(pinLight, LOW);  
  } else { 
    digitalWrite(pinLight, HIGH);
  }

  Serial.print("Temp :");
  Serial.println(getTempValue() );
  Serial.print("Humidity :");
  Serial.println(getHumidityTest() );
  Serial.print("Water Level :");
  Serial.println(getWaterValue () );

  manageLCD();

  delay(5000);
}
