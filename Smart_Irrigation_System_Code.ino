#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(2, 3, 4, 5, 6,7);
const int relay_Pin = 8;
const int DHT11_Sesnor = 9;
const int moisture_sensor = A0;
const int rain_Sesnor = 10;

#define DHTTYPE DHT11
int  moisture_sensor_value;
int rain_Sesnor_value;
float humidity_value ,temperature_value;
DHT dht(DHT11_Sesnor, DHTTYPE);

void setup() {
  Serial.begin(9600);  
  pinMode(relay_Pin, OUTPUT);
  pinMode(rain_Sesnor, INPUT);
  Serial.println("Smart Irrigation");
  delay(500);
  Serial.println("System");
  delay(500);
  lcd.begin(16, 2);
  lcd.print("Smart Irrigation ");
  lcd.setCursor(0,1);
  lcd.print(" SYSTEM");
  digitalWrite(relay_Pin, LOW); 
  dht.begin();
   delay(500);
}
void loop() 
{
  readDTH11_Sesnor();
  moisture_level_detected();
  water_motor_start();
}

void readDTH11_Sesnor()
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity_value  = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature_value = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity_value ) || isnan(temperature_value)) {
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(" Humidity: ");
  Serial.print(humidity_value);
  Serial.print(" %");
  Serial.print("\n");
  Serial.print("  Temperature: ");
  Serial.print(temperature_value);
  Serial.print(" C");
  Serial.print("\n");
  lcd.clear();
  lcd.print("Humidity %: ");
  lcd.setCursor(0,1);
  lcd.print(humidity_value );
  delay(300); 
  lcd.clear();
  lcd.print("Temperature degCel");
  lcd.setCursor(0,1);
  lcd.print(temperature_value);
  //Serial.print("\n");
  delay(200); 
}

void moisture_level_detected()
{

  moisture_sensor_value = analogRead(moisture_sensor); 
  Serial.print("Moisture Level : ");
  Serial.println(moisture_sensor_value);
  Serial.print("\n");
  lcd.clear();
  lcd.print("Moisture Level :");
  lcd.setCursor(0,1);
  lcd.print(moisture_sensor_value);
  delay(900);
}

void water_motor_start()
{

 rain_Sesnor_value = digitalRead(rain_Sesnor); 
 delay(1000);
 if(rain_Sesnor_value == LOW)
 {
    if(moisture_sensor_value > 700 )
    {
      digitalWrite(relay_Pin, HIGH); 
      lcd.clear();
      lcd.print("Low water level");
      lcd.setCursor(0,1);
      lcd.print("Motor ON");
//      Serial.println("Low water level");
//      delay(1000);
//      Serial.println("Motor ON");
//      delay(2000);
      Serial.println("Rain Detected");
      delay(1000);
      Serial.println("Motor OFF");
      delay(2000);
    }
    else
    {
      digitalWrite(relay_Pin, LOW); 
      lcd.clear();
      lcd.print("Water Level Ok");
      lcd.setCursor(0,1);
      lcd.print("Motor OFF");
      Serial.println("Water Level ok!");
      delay(1000);
      Serial.println("Motor OFF");
      delay(2000);
    }
 }
 else
 {
      digitalWrite(relay_Pin, LOW); 
      lcd.clear();
      lcd.print("Rain Detected");
      lcd.setCursor(0,1);
      lcd.print("Motor OFF");
//      Serial.println("Rain Detected");
//      delay(1000);
//      Serial.println("Motor OFF");
//      delay(2000);
      Serial.println("Low water level");
      delay(1000);
      Serial.println("Motor ON");
      delay(2000);
 }
}
