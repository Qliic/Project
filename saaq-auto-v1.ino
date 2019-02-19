// saaq-auto-v1.ino
// par Francois Belleau pour le projet http://Qliic.org

#define PIN_COM1    A2
#define PIN_COM2    A3
#define PIN_COM3    2
#define PIN_COM4    3

#define PIN_POT1    A0
#define PIN_POT2    A1

#define PIN_TRIG  A6
#define PIN_ECHO  A7

#define PIN_RGB1  4
#define PIN_RGB2  5

#define PIN_MOT1  6
#define PIN_MOT2  7
#define PIN_MOT3  8
#define PIN_MOT4  11

#define PIN_SERVO1  9
#define PIN_SERVO2  10

#define PIN_PIEZO   12
#define PIN_LED     13

#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784

#include <Servo.h>
Servo Servo1, Servo2;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(39,16,2);

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel1 = Adafruit_NeoPixel(1, PIN_RGB1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel2 = Adafruit_NeoPixel(1, PIN_RGB2, NEO_GRB + NEO_KHZ800);

int carLu;
String lettre, couleurLu;

String buffer1, buffer2;

//int hue[] =   {023,022,021,020,019,018,017,016,015,014,013,012,011,010,009,008,007,006,005,004,003,002,001,000};
String couleurNom[] = {"Rouge","Orange","Jaune","Vert","Turquoise","Bleu","Violet"};
String couleurLettre = "ROJVTLM";

String noteNom0[] = {"DO","RE","MI","FA","SOL","LA","SI","do","re","mi","fa","sol","la","si"};
String noteLettre[] = {"A","B","C","D","E","F","G","a","b","c","d","e","f","g","g"};
int noteFrequence[] = {NOTE_A3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5};

int red[] =   {000,000,255,255,255,255,255,200,150,100,000,000,000,000,000,000,000,000,000,100,150,200,255,255,255,255};
int green[] = {000,000,000,100,150,200,255,255,255,255,255,255,255,255,255,200,150,100,000,000,000,000,000,000,000,000};
int blue[] =  {000,000,000,000,000,000,000,000,000,000,000,100,150,200,255,255,255,255,255,255,255,255,255,200,150,100};

int analogLu, analog1, analog2;
int digital1, digital2, digital3, digital4;

int distanceLu, couleur, n0, compteur;
int servo1, servo2, servoPos1, servoPos2;
long SR04_duration; 

int luminosite = 8;

char* asciiCode = "                                 ! #$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~";
String note;

boolean led13 = false;

void setup() {
  pixel1.begin();
  pixel2.begin();

  Serial.begin(9600);
  Serial.println("Allo toi ! On Qliic ensemble ? (v3.0)");

  LCD.init();
  LCD.backlight();
    
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_COM1, INPUT_PULLUP);
  pinMode(PIN_COM2, INPUT_PULLUP);
  pinMode(PIN_COM3, INPUT_PULLUP);
  pinMode(PIN_COM4, INPUT_PULLUP);

  pinMode(PIN_POT1, INPUT);
  pinMode(PIN_POT2, INPUT);

  pinMode(PIN_MOT1, OUTPUT);
  pinMode(PIN_MOT2, OUTPUT);
  pinMode(PIN_MOT3, OUTPUT);
  pinMode(PIN_MOT4, OUTPUT);

  pinMode(PIN_LED, OUTPUT);

  buffer1 = "0123456789123456";
  buffer1 = "Allo toi ! On   ";
  buffer2 = "Qliic ensemble ?";  
  //Serial.println(buffer1);
  //Serial.println(buffer2);
  LCD.setCursor(0,0);
  LCD.print(buffer1);
  LCD.setCursor(0,1);
  LCD.print(buffer2);

    couleur=2;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(500);
    couleur=10;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(500);
    couleur=18;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(500);
    couleur=0;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
}

int SR04_Distance() {
  int SR04_distance;
  
  // Clears the trigPin
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  SR04_duration = pulseIn(PIN_ECHO, HIGH, 7000);
  SR04_duration = SR04_duration > 1500 ? 0 : SR04_duration;
  //Serial.println(SR04_duration);

  // Calculating the distance
  SR04_distance = SR04_duration * 0.034/2;
  //Serial.println(SR04_distance);
  
  return SR04_distance;
}

void interpreteur() {
  int delay_tone = 200;

  if (lettre == "n") {
    couleur = 0;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(delay_tone);
  }
  if (lettre == "r") {
    couleur = 2;  
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(delay_tone);
  }
  if (lettre == "v") {
    couleur = 10;
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
    delay(delay_tone);
  }
  if (lettre == "1") {
    digitalWrite(PIN_MOT1, 1);
    delay(delay_tone);
    digitalWrite(PIN_MOT1, 0);
  }

  if (lettre == "2") {
    digitalWrite(PIN_MOT2, 1);
    delay(delay_tone);
    digitalWrite(PIN_MOT2, 0);
  }

  if (lettre == "3") {
    digitalWrite(PIN_MOT3, 1);
    delay(delay_tone);
    digitalWrite(PIN_MOT3, 0);
  }

  if (lettre == "4") {
    digitalWrite(PIN_MOT4, 1);
    delay(delay_tone);
    digitalWrite(PIN_MOT4, 0);
  }

}

void loop() {
  
  //Serial.println(distanceLu);

  carLu = Serial.available() ? Serial.read() : 0;

  digital1 = ! digitalRead(PIN_COM1);
  digital2 = ! digitalRead(PIN_COM2);
  digital3 = ! digitalRead(PIN_COM3);
  digital4 = ! digitalRead(PIN_COM4);

  digitalWrite(PIN_MOT1, digital1);
  digitalWrite(PIN_MOT2, digital2);
  digitalWrite(PIN_MOT3, digital3);
  digitalWrite(PIN_MOT4, digital4);

  analog1 = map(analogRead(PIN_POT1),0,1023,0,255);
  analog2 = map(analogRead(PIN_POT2),0,1023,0,255);
  analogWrite(PIN_SERVO1, analog1);
  analogWrite(PIN_SERVO2, analog2);

  Servo1.write(map(analogRead(PIN_POT1),0,1023,0,180));
  Servo2.write(map(analogRead(PIN_POT2),0,1023,0,180));

  //note = noteLettre[map(analogLu,0,1023,0,14)];
  //couleurLu = couleurLettre[map(analogLu,0,1023,0,8)];

  couleur = map(analog1,0,99,0,25);

  lettre = "";
  if (carLu != 0) {
    lettre = asciiCode[carLu];

    Serial.println("cr recu:" + lettre);
    Serial.print(buffer1);
    Serial.print(" ");
    Serial.println(buffer2);
  
    interpreteur();
  }

  buffer1 = "1:" + String(digital1) + " 2:" + String(digital2) + " P1:" + String(analog1) + " " + lettre + "  ";
  buffer2 = "3:" + String(digital3) + " 4:" + String(digital4) + " P2:" + String(analog2) + "   ";
  
  LCD.setCursor(0,0);
  LCD.print(buffer1);
  LCD.setCursor(0,1);
  LCD.print(buffer2);

  delay(200);
  
  //delay(250);  
}
