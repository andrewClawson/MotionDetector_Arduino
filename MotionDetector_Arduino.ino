int button = D4;
int pir = D2;
int sensor = D5;
int previous = LOW;
int previous2 = LOW;
int ArmedLED = D7;
int buttonstate;
//int sensorstate = 7;
int speaker = D0;
int sensorstate;
int Armed = 0; // 0 = false, 1 = true.

void setup(){
  pinMode(button, INPUT);
  pinMode(pir, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(ArmedLED,OUTPUT);
  //pinMode(sensorstate, OUTPUT);
  pinMode(speaker, OUTPUT);
  digitalWrite(ArmedLED,LOW);
  //Initialize particle cloud variables

  Particle.variable("Armed",&Armed,INT);
  //Initialize particle cloud functions.


  Serial.begin(9600);
}
void loop(){
  buttonstate = digitalRead(button);
  //delay(5000);

  // Button pressed and System is off
  if(buttonstate == HIGH && previous == LOW) {

    digitalWrite(pir,HIGH);
    //digitalWrite(sensorstate, HIGH); <- dont do this (its an instrument that always need power, but the alarm wire needed power)

    previous = HIGH;
    previous2 = HIGH;
    //digitalWrite(speaker, HIGH);
  //}
    delay(5000);
    Armed = 1;
    digitalWrite(ArmedLED,HIGH);

  }
  sensorstate = digitalRead(sensor);

  // Motion detected
  if(sensorstate == LOW && previous2 == HIGH){
   Serial.println("motion detected");
   //delay(2000);

   digitalWrite(ArmedLED,LOW);
   Armed = 0;
   //delay(2000);
   tone(speaker, 1000, 2000);
   delay(2000);
   //noTone(speaker);
   //delay   (3000);
   //Serial.println("motion sensor on");

   digitalWrite(pir, LOW);
   // Call particle function to trigger android response.

   previous = LOW;
   previous2 = LOW;
   delay (2000);
   noTone(speaker);
  }//}
  //Serial.println("hi");
}
//wont read motion while doing the two delays repeatedly reads motion sensor on

// Define particle cloud functions
