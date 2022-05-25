
#include <SoftwareSerial.h> //Include the library
SoftwareSerial mySerial(11, 10); // RX, TX

byte received_data[4];
int  switch_pos;
int feux_routes = 0;
int feux_croix = 0;


int value;
float rayon = 0.5286; // (en m)
const float pi = 3.14159;
long temps_de_reference;
bool time = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ready");
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  mySerial.begin(9600);

  mySerial.print("bt0.val="); 
  mySerial.print("0");
  mySerial.write(0xff);  
  mySerial.write(0xff);
  mySerial.write(0xff);

  mySerial.print("bt1.val="); 
  mySerial.print("0");
  mySerial.write(0xff);  
  mySerial.write(0xff);
  mySerial.write(0xff);

  mySerial.print("bt2.val="); 
  mySerial.print("0");
  mySerial.write(0xff);  
  mySerial.write(0xff);
  mySerial.write(0xff);

  mySerial.print("bt3.val="); 
  mySerial.print("0");
  mySerial.write(0xff);  
  mySerial.write(0xff);
  mySerial.write(0xff);
}

void loop() {
  int i;
  while (mySerial.available() > 0) {
      switch_control();
  }
  // 3 = gauche
  // 4 = warning
  // 5 = croisement
  // 6 = route
  // 7 = droit

    Serial.println(digitalRead(4) == 1);
      if (digitalRead(4) == 1) {
        for (int i; i<3; i++){
        mySerial.print("bt0.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        mySerial.print("bt1.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        mySerial.print("bt0.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        mySerial.print("bt1.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        };
      };
  
      if (digitalRead(3) == 1) {
        for (int i; i<3; i++){
        mySerial.print("bt0.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        mySerial.print("bt0.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        };
      };

      if (digitalRead(7) == 1) {
        for (int i; i<3; i++){
        mySerial.print("bt1.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        mySerial.print("bt1.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        delay(500);
        };
      };

      if (digitalRead(6) == 1) {
        while (digitalRead(6) == 1) {
          delay(10);
        }
        if (feux_routes == 0) {
        feux_routes = 1;
        mySerial.print("bt2.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        feux_croix = 0;
        mySerial.print("bt3.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        while (digitalRead(7) == 1) {
          delay(10);
        }
        } else {
        feux_routes = 0;
        mySerial.print("bt2.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        };
        };

        
      if (digitalRead(5) == 1) {
        while (digitalRead(5) == 1) {
          delay(10);
        }
        if (feux_croix == 0) {
        feux_routes = 0;
        mySerial.print("bt2.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        feux_croix = 1;
        mySerial.print("bt3.val="); 
        mySerial.print("1");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        while (digitalRead(6) == 1) {
          delay(10);
        }
        } else {
        feux_croix = 0;
        mySerial.print("bt3.val="); 
        mySerial.print("0");
        mySerial.write(0xff);  
        mySerial.write(0xff);
        mySerial.write(0xff);
        };
        };
}

void switch_control() {
    int size = mySerial.readBytesUntil('\n', received_data, 4);
    // First Byte has the switch position data 
    switch_pos = received_data[0];
}
