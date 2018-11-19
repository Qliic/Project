# Projet pour le Waq junior en avril 2018
# par Francois Belleau pour le projet qliic.org

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, 8, NEO_GRB + NEO_KHZ800);

void setupPixel() {
  pixels.begin();
}

//i2c include
#include <Wire.h>

//lcd include
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//servo include
#include <Servo.h>

Servo servo9, servo10, servo11;

void setupServo() {
  servo9.attach(9);
  servo10.attach(10);
  servo11.attach(11);

  servo9.write(90);
  servo10.write(90);
  servo11.write(90);

}


//sr04 include
#include <NewPing.h>
NewPing sonar(7,6,50);

boolean debug = true;
int analogValue;
int distanceValue;
int compteur = 0;

void debugPrintln (String ligne1, String ligne2) {
      if (debug) {
        lcd.setCursor(0,0);
        lcd.print(ligne1);
        Serial.println(ligne1);
        lcd.setCursor(0,1);
        lcd.print(ligne2);
        Serial.println(ligne2);
      }
}
  
void blink() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second
}

void setupBlink() {
  pinMode(13, OUTPUT);
}

void setupLCD() {
  lcd.init();
  lcd.backlight();
  
 if (debug) {
    Serial.println("mode debug on");
  } else {
    Serial.println("mode debug off");
  }
}

void setupSerial() {
  //Serial.begin(115200);
  Serial.begin(9600);
  while (!Serial); 
}

void setupAnalog() {}

void servo1Bouger() {
 servo9.write(80);
 delay(50);
 servo9.write(70);
 delay(50);
 servo9.write(60);
 delay(50);
 servo9.write(50);
 delay(50);
 servo9.write(40);
 delay(50);
 servo9.write(30);
 delay(50);
 servo9.write(20);
 delay(50);
 servo9.write(10);
 delay(50);
 servo9.write(0);
 delay(50);
 servo9.write(10);
 delay(50);
 servo9.write(20);
 delay(50);
 servo9.write(30);
 delay(50);
 servo9.write(40);
 delay(50);
 servo9.write(50);
 delay(50);
 servo9.write(60);
 delay(50);
 servo9.write(70);
 delay(50);
 servo9.write(80);
 delay(50);
 servo9.write(90);
 delay(50);
 servo9.write(100);
 delay(50);
 servo9.write(110);
 delay(50);
 servo9.write(120);
 delay(50);
 servo9.write(130);
 delay(50);
 servo9.write(140);
 delay(50);
 servo9.write(150);
 delay(50);
 servo9.write(160);
 delay(50);
 servo9.write(170);
 delay(50);
 servo9.write(180);
 delay(50);
 servo9.write(170);
 delay(50);
 servo9.write(160);
 delay(50);
 servo9.write(150);
 delay(50);
 servo9.write(140);
 delay(50);
 servo9.write(130);
 delay(50);
 servo9.write(120);
 delay(50);
 servo9.write(110);
 delay(50);
 servo9.write(100);
 delay(50);
 servo9.write(90);
 delay(50);
}

void setup() {
  setupServo();
  setupBlink();
  setupLCD();
  setupSerial();
  setupAnalog();
  setupPixel();

 //debugPrintln("Arduino boot", "");
 debugPrintln("Allo toi, on", "Qliic ensemble?");
 delay(2000);
 //debugPrintln("0123456789123456", "0123456789123456");
 //debugPrintln("ECRAN LCD:A4,A5",  "");
 //debugPrintln("LED RGB:8",  "");
 //debugPrintln("SERVOMOTEUR:9,10", "");
 //debugPrintln("POTENTIOMETRE:A0", "");
 //debugPrintln("HC-SR04:A1,A2", "");

 pixels.setPixelColor(0,pixels.Color(64,0,0));
 pixels.show();
 servo9.write(60);
 blink();
 pixels.setPixelColor(0,pixels.Color(0,64,0));
 pixels.show();
 servo9.write(90);
 blink();
 pixels.setPixelColor(0,pixels.Color(0,0,64));
 pixels.show();
 servo9.write(120);
 blink();
 pixels.setPixelColor(0,pixels.Color(0,0,0));
 pixels.show();
 servo9.write(90);
}

void loop() {
  //blink();

  distanceValue = sonar.ping_cm();

  analogValue =  analogRead(A0);

  servo10.write(map(analogValue, 0, 1023, 0, 180));
  servo11.write(map(distanceValue, 0, 50, 0, 180));

//  debugPrintln("                ", "                ");
  lcd.clear();
  debugPrintln("VISITEUR=" + (String) compteur, "CM="+(String) distanceValue+" POT="+(String) analogValue);
  delay(100);   

  if (distanceValue > 10 && analogValue <= 250) {
    compteur ++;
    pixels.setPixelColor(0,pixels.Color(64,0,0));
    pixels.show();
    lcd.clear();
//               "1234567890123456"
    debugPrintln("Sors de", "ma chambre !!!");
    servo1Bouger();
    pixels.setPixelColor(0,pixels.Color(0,0,0));
    pixels.show();
  }

  if (analogValue <= 250) {
    pixels.setPixelColor(0,pixels.Color(0,0,0));
    pixels.show();
  } else if (analogValue > 750) {
    pixels.setPixelColor(0,pixels.Color(64,0,0));
    pixels.show();
  } else if (analogValue > 500) {
    pixels.setPixelColor(0,pixels.Color(0,0,64));
    pixels.show();
  } else if (analogValue > 250) {
    pixels.setPixelColor(0,pixels.Color(0,64,0));
    pixels.show();
  }

} 
