/* This program measuring the distance using Ultrasonic sensor (HC-SR04)
 * and show it on 4digit 7segment display.
 */

// 2 wires to HC-SR04
#define trigPin 3
#define echoPin 2

// 3 wires to display
#define clockPin 12  //green
#define latchPin 11  //yellow
#define dataPin 10   //orange

int LED_SEG_TAB[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0x01,0xee,0x3e,0x1a,0x7a,0x9e,0x8e,0x01};
                  //0     1    2     3    4    5    6    7    8    9    0    .    a    b    c    d    e    f.
                  

void setup() {
  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Display
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  //Serial.begin(9600);  
}

void loop() {
  // d = distance
  int time, d;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  time = pulseIn(echoPin,HIGH);
  d = (time/2) / 29.1;

  //Serial.println(d);
    
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, LED_SEG_TAB[d-((d/100)*100)-(((d/10)%10)*10)]);  
  shiftOut(dataPin, clockPin, LSBFIRST, LED_SEG_TAB[(d-((d/100)*100))/10]);  
  shiftOut(dataPin, clockPin, LSBFIRST, LED_SEG_TAB[(d/100)]);  
  shiftOut(dataPin, clockPin, LSBFIRST, LED_SEG_TAB[0]);  
  digitalWrite(latchPin, HIGH); 
  
  delay(100);  
}
