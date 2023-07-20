#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6,7);
const int gas_Sensor = 8;
const int flame_Sensor = 9;
const int motor_pin = 10;
const int buzzer_Pin = 11;
bool fire_Status = LOW;
bool flame_Status = LOW;

void setup() {
  Serial.begin(9600);  
  pinMode(buzzer_Pin, OUTPUT);
   pinMode(motor_pin, OUTPUT);
  pinMode(gas_Sensor, INPUT);
   pinMode(flame_Sensor, INPUT);

  lcd.begin(16, 2);
  lcd.print("Fire DETECTION");
  lcd.setCursor(0,2);
  lcd.print(" SYSTEM");
  delay(500); 
}
void loop() {
  fire_Status = digitalRead(gas_Sensor);
  flame_Status = digitalRead(flame_Sensor);
  delay(100);
  if((fire_Status == HIGH) and (flame_Status == HIGH))
  {
    lcd.clear();
    lcd.print("Fire Detected");
    lcd.setCursor(3,2);
    lcd.print("Sending msg");
    delay(1000);  
    digitalWrite(buzzer_Pin, HIGH);   
    delay(100);
    digitalWrite(motor_pin, HIGH); 
    delay(100);
    while(1)
    {
      SendMessage();
    }
  }
  else
  {

    lcd.clear();
    lcd.print("Fire not ");  
    lcd.setCursor(3,2);
    lcd.print("detected");
    delay(500);          
    digitalWrite(buzzer_Pin, LOW);   
    digitalWrite(motor_pin, LOW); 
    delay(100);    
  }
}




void SendMessage()
{
  Serial.println("AT+CMGF=1");    
  delay(1000);  
  Serial.println("AT+CMGS=\"+919399721840\"\r"); 
  delay(1000);
  Serial.println("Fire Detected inside home");
  delay(100);
  Serial.println((char)26);
  delay(1000);
}
