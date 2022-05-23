#include <Adafruit_NeoPixel.h>
 
#define PIN 44
#define NUMPIXELS 32 // number of neopixels in Ring
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int send_route = 28;
int send_croisement = 38;
int send_gauche = 40;
int send_droit = 26;

bool feux_route = false;
bool feux_croisement = false;

int read_route = 12;//12
int read_croisement = 13;//13
int read_gauche = 11;
int read_warning = 10;//10
int read_droit = 9;//9

void setup() {
Serial.begin(9600);
pixels.begin();
}


void loop() {
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
