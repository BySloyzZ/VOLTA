#include <Adafruit_NeoPixel.h>
 
#define PIN 44
#define NUMPIXELS 32 // number of neopixels in Ring
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int send_route = 28;
int send_croisement = 38;
int send_gauche = 40;
int send_droit = 26;
int send_plaf = 6;
int send_mot = 3;
int send_mot2 = 53;

bool feux_route = false;
bool feux_croisement = false;
bool sens_mot = true;

int read_route = 12;//12
int read_croisement = 13;//13
int read_gauche = 11;
int read_warning = 10;//10
int read_droit = 9;//9
int read_plaf = 5;

void setup() {
Serial.begin(9600);
pixels.begin();

pinMode(send_route, OUTPUT);
pinMode(send_croisement, OUTPUT);
pinMode(send_gauche, OUTPUT);
pinMode(send_droit, OUTPUT);
pinMode(send_plaf, OUTPUT);
pinMode(send_mot, OUTPUT);
pinMode(send_mot2, OUTPUT);

pinMode(read_route, INPUT);
pinMode(read_croisement, INPUT);
pinMode(read_gauche, INPUT);
pinMode(read_warning, INPUT);
pinMode(read_droit, INPUT);
pinMode(read_plaf, INPUT);
}


void loop() {
 vitesse();

 if (digitalRead(read_route) == 1) {
  route();
  Serial.println("Route");
    while (digitalRead(read_route) == 1) {
      delay(100);
  }
}
if (digitalRead(read_croisement) == 1) {
  croisement();
  Serial.println("Croisement");
    while (digitalRead(read_croisement) == 1) {
      delay(100);
  }
}
if (digitalRead(read_gauche) == 1) {
  gauche();
  Serial.println("Gauche");
    while (digitalRead(read_gauche) == 1) {
      delay(100);
  }
}
if (digitalRead(read_warning) == 1) {
  warning();
  Serial.println("Warning");
    while (digitalRead(read_warning) == 1) {
      delay(100);
  }
}
if (digitalRead(read_droit) == 1) {
  droit();
  Serial.println("Droit");
  while (digitalRead(read_droit) == 1) {
      delay(100);
  }
}
if (digitalRead(read_plaf) == 1) {
  analogWrite(send_plaf, 255);
    while (digitalRead(read_plaf) == 1) {
      delay(100);
  }
for (int i = 255; i>0; i--) {
  Serial.println(i);
  analogWrite(send_plaf, i);  
  delay(10);
}
}

digitalWrite(send_gauche, LOW);
digitalWrite(send_droit, LOW);
}

void route() {
  if (feux_route == false) {
    feux_route = true;
    feux_croisement = false;
  digitalWrite(send_route, HIGH);

  for(int i=0;i<9;i++){
    pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
    pixels.show();
  }
  for(int i=16;i<25;i++){
    pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
    pixels.show();
  }
  } else {
    feux_route = false;
    digitalWrite(send_route, LOW);

  for(int i=0;i<9;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  for(int i=16;i<25;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  }
}
void croisement() {
  if (feux_croisement == false) {
    feux_croisement = true;
    feux_route = false;
    digitalWrite(send_croisement, HIGH);
  for(int i=0;i<9;i++){
    pixels.setPixelColor(i, pixels.Color(50, 50, 50)); 
    pixels.show();
  }
  for(int i=16;i<25;i++){
    pixels.setPixelColor(i, pixels.Color(50, 50, 50)); 
    pixels.show();
  }
  } else {
    feux_croisement = false;
    digitalWrite(send_croisement, LOW);

  for(int i=0;i<9;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  for(int i=16;i<25;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  }
}
void gauche() {
  for (int i; i<3; i++) {

  for(int i=25;i<32;i++){
    pixels.setPixelColor(i, pixels.Color(255, 180, 0)); 
    pixels.show();
  }

  digitalWrite(send_gauche, HIGH);  

  delay(500);
  for(int i=25;i<32;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  digitalWrite(send_gauche, LOW);
  delay(500);
  }
}
void droit() {
  for (int i; i<3; i++) {

  for(int i=9;i<16;i++){
    pixels.setPixelColor(i, pixels.Color(255, 180, 0)); 
    pixels.show();
  }
  digitalWrite(send_droit, HIGH);
  delay(500);

  for(int i=9;i<16;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  digitalWrite(send_droit, LOW);
  delay(500);
  }
}
void warning() {
  for (int i; i<3; i++) {

  for(int i=9;i<16;i++){
    pixels.setPixelColor(i, pixels.Color(255, 180, 0)); 
    pixels.show();
  }
  for(int i=25;i<32;i++){
    pixels.setPixelColor(i, pixels.Color(255, 180, 0)); 
    pixels.show();
  }
  digitalWrite(send_droit, HIGH);
  digitalWrite(send_gauche, HIGH);
  delay(500);

  for(int i=9;i<16;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  for(int i=25;i<32;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    pixels.show();
  }
  digitalWrite(send_droit, LOW);
  digitalWrite(send_gauche, LOW);
  delay(500);
  }
}

void vitesse(){
  Serial.println(digitalRead(49));
  if (digitalRead(49) == 1 && sens_mot == false) {
    sens_mot = true;
    analogWrite(send_mot, 0);
    delay(500);
    digitalWrite(send_mot2, HIGH);
  } 
  if (digitalRead(49) == 0 && sens_mot == true) {
    sens_mot = false;
    analogWrite(send_mot, 0);
    delay(500);
    digitalWrite(send_mot2, LOW);
  }
  
  if (analogRead(A0) - 40 < 5) {
    analogWrite(send_mot, 0);
    digitalWrite(send_mot2, 0);
  } else {
  int valPed = map(analogRead(A0), 40, 132, 0, 255);
  analogWrite(send_mot, valPed);
  delay(10); 
  }
}
