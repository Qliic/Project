// qliic-waq-v24.ino
// par Francois Belleau pour le projet http://Qliic.org

#define PIN_COM     A0
#define PIN_LIDAR   A1
#define PIN_POT     A3

#define PIN_TRIG  2
#define PIN_ECHO  3

#define PIN_RGB1  7
#define PIN_RGB2  6

#define PIN_SERVO2  10
#define PIN_SERVO1  11

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

int distanceLu, analogLu, analog0, couleur, n0, digital1, digital2, compteur;
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
  Serial.println("Allo toi ! On Qliic ensemble ? (v2.3)");

  LCD.init();
  LCD.backlight();
    
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_POT, INPUT);
  pinMode(PIN_COM, INPUT_PULLUP);
  pinMode(PIN_LIDAR, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);

  Servo1.attach(PIN_SERVO1);
  Servo2.attach(PIN_SERVO2);

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

    Servo1.write(90);
    delay(200);
    Servo2.write(90);
    delay(200);

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
  if (lettre == "1") {
    Servo1.write(0); delay(500);
  } else if (lettre == "2") {
    Servo1.write(45); delay(500);
  } else if (lettre == "3") {
    Servo1.write(90); delay(500);
  } else if (lettre == "4") {
    Servo1.write(135); delay(500);
  } else if (lettre == "5") {
    Servo1.write(180); delay(500);
  } else if (lettre == "6") {
    Servo2.write(0); delay(500);
  } else if (lettre == "7") {
    Servo2.write(45); delay(500);
  } else if (lettre == "8") {
    Servo2.write(90); delay(500);
  } else if (lettre == "9") {
    Servo2.write(135); delay(500);
  } else if (lettre == "0") {
    Servo2.write(180); delay(500);
  } else if (lettre == "s") {
    delay(500);
  }

  int delay_tone = 250;

  if (lettre == "A") {
    tone(PIN_PIEZO, noteFrequence[0],delay_tone); delay(delay_tone);
  } else if (lettre == "B") {
    tone(PIN_PIEZO, noteFrequence[1],delay_tone); delay(delay_tone);
  } else if (lettre == "C") {
    tone(PIN_PIEZO, noteFrequence[2],delay_tone); delay(delay_tone);
  } else if (lettre == "D") {
    tone(PIN_PIEZO, noteFrequence[3],delay_tone); delay(delay_tone);
  } else if (lettre == "E") {
    tone(PIN_PIEZO, noteFrequence[4],delay_tone); delay(delay_tone);
  } else if (lettre == "F") {
    tone(PIN_PIEZO, noteFrequence[5],delay_tone); delay(delay_tone);
  } else if (lettre == "G") {
    tone(PIN_PIEZO, noteFrequence[6],delay_tone); delay(delay_tone);
  } else if (lettre == "a") {
    tone(PIN_PIEZO, noteFrequence[7],delay_tone); delay(delay_tone);
  } else if (lettre == "b") {
    tone(PIN_PIEZO, noteFrequence[8],delay_tone); delay(delay_tone);
  } else if (lettre == "c") {
    tone(PIN_PIEZO, noteFrequence[9],delay_tone); delay(delay_tone);
  } else if (lettre == "d") {
    tone(PIN_PIEZO, noteFrequence[10],delay_tone); delay(delay_tone);
  } else if (lettre == "e") {
    tone(PIN_PIEZO, noteFrequence[11],delay_tone); delay(delay_tone);
  } else if (lettre == "f") {
    tone(PIN_PIEZO, noteFrequence[12],delay_tone); delay(delay_tone);
  } else if (lettre == "g") {
    tone(PIN_PIEZO, noteFrequence[13],delay_tone); delay(delay_tone);
  } else if (lettre == "s") {
    delay(delay_tone);
  }


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
  if (lettre == "l") {
    couleur = 18;
    pixel2.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();
    delay(delay_tone);
  }
  if (lettre == "N") {
    couleur = 0;
    pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();
    delay(delay_tone);
  }
  if (lettre == "R") {
    couleur = 2;  
    pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();
    delay(delay_tone);
  }
  if (lettre == "V") {
    couleur = 10;
    pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();
    delay(delay_tone);
  }
  if (lettre == "L") {
    couleur = 18;
    pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();
    delay(delay_tone);
  }
}

void loop() {
  distanceLu = SR04_Distance();
  if (distanceLu > 5 && distanceLu < 15 && led13) {
    compteur++;

  buffer1 = "   Sors de         ";
  buffer2 = "  ma chambre !     ";  
  Serial.println("Sors de ma chambre !");
  LCD.setCursor(0,0);
  LCD.print(buffer1);
  LCD.setCursor(0,1);
  LCD.print(buffer2);

  couleur = 2;
  pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel1.show();
  pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel2.show();
  tone(PIN_PIEZO, 440,250);
  delay(250);
  couleur = 0;
  pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel1.show();
  pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel2.show();
  noTone(PIN_PIEZO);
  delay(250);
  couleur = 2;
  pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel1.show();
  pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel2.show();
  tone(PIN_PIEZO, 440,250);
  delay(250);
  couleur = 0;
  pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel1.show();
  pixel2.setPixelColor(0, pixel2.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
  pixel2.show();
  noTone(PIN_PIEZO);
  delay(250);
}
  
  //Serial.println(distanceLu);

  carLu = Serial.available() ? Serial.read() : 0;

  analogLu = analogRead(PIN_POT);
  analog0 = map(analogLu,0,1023,0,99);

  note = noteLettre[map(analogLu,0,1023,0,14)];
  couleurLu = couleurLettre[map(analogLu,0,1023,0,8)];

  digital1 = ! digitalRead(PIN_COM);
  digital2 = ! digitalRead(PIN_LIDAR);

  couleur = map(analog0,0,99,0,25);

  if (digital2){
    compteur++;
    //tone(PIN_PIEZO, map(analogLu,0,1023,110,880));
    if (distanceLu != 0) {
      tone(PIN_PIEZO, map(distanceLu,0, 24, 110, 880));
    }
    //tone(PIN_PIEZO, map(analogLu,0,1023,220,880),250);
  } else {
    noTone(PIN_PIEZO);
}  
  
  if (digital1) {
    compteur++;
    tone(PIN_PIEZO, noteFrequence[map(analogLu,0,1023, 0, 13)]);
    led13 = ! led13;
    digitalWrite(PIN_LED, led13);
    delay(100);
  } 

  if (!led13){
    pixel1.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel1.show();
  
    Servo1.write(map(analogLu,0,1023,0,180));
  } else {
    pixel2.setPixelColor(0, pixel1.Color(red[couleur]/luminosite, green[couleur]/luminosite, blue[couleur]/luminosite));
    pixel2.show();

    Servo2.write(map(analogLu,0,1023,0,180));
    //buffer2 = "N:"+note+" C:V S:"+String(servoPos1)+" M:"+ lettre + "    ";
  }

  servoPos1 = map(analogLu,0,1023,0,5);

  buffer1 = "B" + String(digital1) + " L" + String(digital2) + " M"+ lettre + " P" + String(analog0) + " D" + String(distanceLu) + "    ";
  buffer2 = "N:"+note+" C:" + couleurLu + " S:"+String(servoPos1+(5*led13)) +" C:" + String(compteur) + "    ";  
  //Serial.println(buffer1);
  //Serial.println(buffer2);
  LCD.setCursor(0,0);
  LCD.print(buffer1);
  LCD.setCursor(0,1);
  LCD.print(buffer2);

  if (carLu != 0) {
    lettre = asciiCode[carLu];
    interpreteur();
  }
  
}
