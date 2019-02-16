// nano-serial-l298n-lcd.ino
// by Francois Belleau

//i2c include
#include <Wire.h>

//lcd include
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//servo include
#include <Servo.h>

Servo servo5, servo6;


char buffer[80];
char carLu;
boolean debug = true;
String direction;
int vitesse; 

// Definitions Arduino pins connected to input H Bridge
//int moteurA1 = 4;
//int moteurA2 = 5;
int moteurA1 = 7;
int moteurA2 = 8;
int moteurApwm = 9; // Needs to be a PWM pin to be able to control moteur speed

//int moteurB1 = 6;
//int moteurB2 = 7;
int moteurB1 = 11;
int moteurB2 = 12;
int moteurBpwm = 10; // Needs to be a PWM pin to be able to control moteur speed

void debugPrintln (String message) {
      if (debug) {
        lcd.clear();
        lcd.print(message);
        Serial.println(message);
      }
}
  
void setup() {
 //debug = false;
// lcd setup
  lcd.init();
  lcd.backlight();
  
//serial_setup
  //Serial.begin(115200);
  Serial.begin(9600);
  while (!Serial);

//servo setup

servo5.attach(5);
servo6.attach(6);

servo5.write(60);
servo6.write(110);
delay(500);

servo5.write(80);
servo6.write(80);
delay(500);

servo5.write(70);
servo6.write(90);
delay(1000);

 
 if (debug) {
  Serial.println("mode debug on");
 } else {
  Serial.println("mode debug off");
 }
 debugPrintln("Arduino boot");
 delay(2000);
 debugPrintln("Allo toi!");

//motor setup
 pinMode(moteurA1, OUTPUT);
 pinMode(moteurA2, OUTPUT);
 pinMode(moteurApwm,OUTPUT);
 pinMode(moteurB1, OUTPUT);
 pinMode(moteurB2, OUTPUT);
 pinMode(moteurBpwm,OUTPUT);

  vitesse = 255;
  vitesseA();
  vitesseB();
}

void loop() {
  if (Serial.available() > 0) {
    carLu = Serial.read();
    //Serial.print("car:");
    //Serial.println(carLu);
    interpreteur(carLu);
    delay(300);
  }
}

void regarderGauche() {
servo6.write(70);
delay(300);
}

void regarderDroite() {
servo6.write(130);
delay(300);
}

void regarderStop() {
servo5.write(70);
servo6.write(90);
delay(300);
}

void regarderAvancer() {
servo5.write(50);
servo6.write(90);
delay(300);
}

void regarderReculer() {
servo5.write(90);
servo6.write(90);
delay(300);
}


void vitesseA () {
 analogWrite(moteurApwm, vitesse);
}

void arretA () {
 digitalWrite(moteurA1, HIGH);
 digitalWrite(moteurA2, HIGH);
}

void avantA () {
 digitalWrite(moteurA1, LOW);
 digitalWrite(moteurA2, HIGH);
}

void arriereA () {
 digitalWrite(moteurA1, HIGH);
 digitalWrite(moteurA2, LOW);
}

void vitesseB () {
 analogWrite(moteurBpwm, vitesse);
}

void arretB () {
 digitalWrite(moteurB1, HIGH);
 digitalWrite(moteurB2, HIGH);
}

void avantB () {
 digitalWrite(moteurB1, LOW);
 digitalWrite(moteurB2, HIGH);
}

void arriereB () {
 digitalWrite(moteurB1, HIGH);
 digitalWrite(moteurB2, LOW);
}

void avancer() {
  direction = "avancer";
  debugPrintln(direction);
  avantA();
  avantB();
  regarderAvancer();
}

void reculer() {
  direction = "reculer";
  debugPrintln(direction);
  arriereA();
  arriereB();
  regarderReculer();
}

void droite() {
  direction = "droite";
  debugPrintln(direction);
  avantA();
  arriereB();
  regarderDroite();
}

void gauche() {
  direction = "gauche";
  debugPrintln(direction);
  arriereA();
  avantB();
  regarderGauche();
}

void arreter() {
  direction = "arreter";
  debugPrintln(direction);
  arretA();
  arretB();
  regarderStop();
}

void setVitesse(int v) {
  String message;
  
  if (v == 1) vitesse = 64;
  if (v == 2) vitesse = 128;
  if (v == 3) vitesse = 192;
  if (v == 4) vitesse = 255;

  vitesseA();
  vitesseB();
  
  //message = "vitesse "+ vitesse;
  sprintf(buffer, "vitesse %i", vitesse);
  //debugPrintln("vitesse "+ buffer);
  debugPrintln(buffer);
}


void interpreteur(char message) {
    switch (message) {
    case 97 :  //a
      avancer();
      break;
    case 114 : //r
      reculer();
      break;
    case 103 :  //g
      gauche();
      break;
    case 100 :  //d
      droite();
      break;
    case 115 :  //s
      arreter();
      break;
    case 49 :  //1
      setVitesse(1);
      break;
    case 50 :  //2
      setVitesse(2);
      break;
    case 51 :  //3
      setVitesse(3);
      break;
    case 52 :  //4
      setVitesse(4);
      break;
    default :  ;
    }
  }
