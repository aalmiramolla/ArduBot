#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include <Servo.h>
#include "../Config/configuracion.h"

Servo sDerecho; // put your main code here, to run repeatedly:
Servo sIzquierdo;
Servo brazo;


//IR
QTRSensorsRC qtrrc((unsigned char []) {3,4}, NUM_SENSORS, TIMEOUT,EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void girarIzquierda();
void avanzar(unsigned int tiempoAvance);
void parar();
void girar180();
void Speak();
void subirBrazo();
void bajarBrazo();
void retroceder(unsigned int tiempoRetroceso);

unsigned long beginTimer = 0;
unsigned long endTimer = 0;
unsigned long waitTime = 4000;

int buttonState = 0;
int once = 0;
int count = 0;
int lineaMax = 1;
bool volviendo = false;

int distance; // An interger variable that will contain the distance measured from the returning pulse.
unsigned long pulseduration=0; // A long varible that will contain the number of milisecond of the returning pulse.
unsigned int i = 0; 
int distanceMAX = 0;


//---------------------------------------------FUNCTION PROTOTYPE---------------------//
void measureDistance();  // 

void setup()
{
  Serial.begin(19200);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  brazo.attach(SERVO_BRAZO);
  subirBrazo();
  delay(500);
  pinMode(13,OUTPUT);
  digitalWrite(13,OUTPUT);
  measureDistance();
  distanceMAX = distance;
  delay(3000);
}

void loop()
{
    girarIzquierda();
    measureDistance(); // Function call to get the pulseduration
   if(distance < distanceMAX)
   {
      while(distance > 5)
     {
        avanzar(500);
        measureDistance();
     }
     girar180();
     bajarBrazo();
     delay(50000);
   }
// Display on serial monitor

Serial.println("Distance-  ");
Serial.println(distance);
Serial.println(" cm");
delay(500);
}

void measureDistance() 
{
  // set pin as output so we can send a pulse
  pinMode(ULTRA_SOUND_PIN, OUTPUT); // Do not mistake this line as a code redundancy this is needed to reset the pin as output for next run
  // set output to LOW
  digitalWrite(ULTRA_SOUND_PIN, LOW);
  delayMicroseconds(5);
 
  // now send the 5uS pulse out to activate Ping)))
  digitalWrite(ULTRA_SOUND_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_SOUND_PIN, LOW);
 
  pinMode(ULTRA_SOUND_PIN, INPUT); // Since the digital pins are BI-DIRECTIONAL their input/output characters can be switeced at any time using the software. Switched to input
  // THE TRIGGER PULSE AND THE ECHO ARE HANDELED BY 1 PIN IN THIS KIND OF ULTRA-SONIC SENSOR
 
  // finally, measure the length of the incoming pulse
  pulseduration=pulseIn(ULTRA_SOUND_PIN, HIGH); // the length of pulse in microseconds.
  delay(30);
  pulseduration=pulseduration/2; // The principle of sound and echo time to reach the object = total time / 2
  distance = int(pulseduration/29); // THE LONG VALUE WILL BE AUTOMATICALLY CONVERTED INTO INTEGER
}

void subirBrazo()
{
  Serial.println("Subo Brazo");
  brazo.write(90);
  delay(1000);
}

void bajarBrazo()
{
  Serial.println("Bajo Brazo");
  brazo.write(0);
  delay(1000);
}

void Speak()
{
  for(int i = 0; i < numTonesSpeaker; i++)
    {
      tone(SPEAKER, tonesSpeaker[i]);
      delay(500);
    }
  noTone(SPEAKER);
}

void girarIzquierda()
{
  Serial.println("Giro Izquierda 90º");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds( SERVO_DERECHO_ADELANTE);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(200);
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
}

void girar180()
{
  Serial.println("Giro 180 grados");
  sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(TIEMPO_GIRO180-100);
  parar(); 
}

void avanzar(unsigned int tiempoAvance) {
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION);
   delay(tiempoAvance);
   parar();
}

void retroceder(unsigned int tiempoRetroceso) {
   sDerecho.writeMicroseconds(SERVO_DERECHO_ATRAS_CORRECCION);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
   delay(tiempoRetroceso);
   parar();
 }
void parar() {
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
}

