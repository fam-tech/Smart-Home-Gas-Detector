#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int gasPin = A0; // SIMPAN DATA ADC SENSOR MQ2
int val;
int potpin = 0;
//const int pinBuzer = 12;
const int pinFan = 8;
const int Led = 10;
//bool started = false;
// the setup routine runs once when you press reset:
void setup() {
  //pinMode(pinBuzer, OUTPUT); // Jadikan Buzzer sebagai OUTPUT
  pinMode(pinFan, OUTPUT);  // Jadikan kipas sebagai OUTPUT
  pinMode(Led, OUTPUT);   // Jadikan Led sebagai OUTPUT
  myservo.attach(9);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
}
void loop() {
  //sensorMQ2 = analogRead(gasPin); // PROSES ADC 10 BIT 0 - 1023
  lcd.setCursor(0, 0);
  lcd.print("Kadar Gas : ");
  val = map(analogRead(gasPin), 0, 1023, 0 , 100);
  lcd.print(val);
  lcd.print("%  ");
  lcd.setBacklight(HIGH);
  if ( val > 60 ) {
    //lcd.setCursor(00,00);
    //lcd.print("ADA KBCRAN GAS");
    lcd.setCursor(00, 1);
    lcd.print("Ket : Bocor Bsr");
    lcd.setBacklight(HIGH);
    //digitalWrite(pinBuzer, HIGH); // BUZER HIDUP
    //    delay(50);
    //    digitalWrite(pinBuzer, LOW);
    //    delay(2);
    digitalWrite(pinFan, HIGH); // KIPAS HIDUP
    digitalWrite(Led, HIGH);
    delay(50);
    digitalWrite(Led, LOW);
    delay(10);
    Serial.println("GAS BOCOR");
    delay(500);
    myservo.write(90);
    //started = true;
  }
  else if ( val > 26) {
    //lcd.setCursor(00,00);
    //lcd.print("TDK ADA KBCRAN GAS");
    lcd.setCursor(00, 1);
    lcd.print("Ket : Bocor Sdg");
    //digitalWrite(pinBuzer, LOW);// BUZER MATI
    digitalWrite(pinFan, LOW); // KIPAS MATI
    digitalWrite(Led, LOW);
    delay(500);
    myservo.write(10);
    //started = true;
  }
  else if (val >= 0) {
    lcd.setCursor(00, 1);
    lcd.print("Ket : Aman Lur");
    //digitalWrite(pinBuzer, LOW);// BUZER MATI
    digitalWrite(pinFan, LOW); // KIPAS MATI
    digitalWrite(Led, LOW);
    delay(500);
    myservo.write(10);
    //started = true;
  }
  Serial.println(analogRead(gasPin));
  Serial.println(val);
  delay(500);
  lcd.clear();
}
