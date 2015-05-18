#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include <Servo.h>
#include "../Config/configuracion.h"

Servo sDerecho; // put your main code here, to run repeatedly:
Servo sIzquierdo;
//const int ledPin = 13;
void avanzar(unsigned int tiempoAvance);
void parar();
void Speak();
int buttonState = 0;
int once = 0;
void setup() {
  Serial.begin(19200);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  delay(500);
  pinMode(pinES,INPUT);
  pinMode(13,OUTPUT);
  delay(3000);
}

void loop() {
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(pinES);
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    once = 1;
    digitalWrite(ledPin,LOW);
    avanzar();
  }
  else {
    digitalWrite(ledPin,HIGH);
    parar();
    if(once == 1)
      Speak();
    once = 0;
  }
  /*Serial.println(sDerecho.read());
  delay(1000);
  avanzar(1000);
  Serial.println(sDerecho.read());
  delay(1000);
  retroceder(1000);
  Serial.println(sDerecho.read());
  delay(1000);
  parar();
  delay(5000);*/
  
}

void Speak()
{
  for(int i = 0; i < numTonesSpeaker; i++)
    {
      tone(SPEAKER, tonesSpeaker[i]);
      delay(50);
    }
  noTone(SPEAKER);
}

void avanzar() {
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION);
}
 
void parar() {
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
}

