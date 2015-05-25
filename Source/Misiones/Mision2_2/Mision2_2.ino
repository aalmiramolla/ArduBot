#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include <Servo.h>
#include "../Config/configuracion.h"

Servo sDerecho; // put your main code here, to run repeatedly:
Servo sIzquierdo;
Servo brazo;

void girarIzquierda();
void girar180();
void girar45();
void avanzar(unsigned int tiempoAvance);
void parar();
void Speak();
void subirBrazo();
void bajarBrazo();
void retroceder(unsigned int tiempoRetroceso);
bool timeCompleted();

unsigned long beginTimer = 0;
unsigned long endTimer = 0;
unsigned long waitTime = 4000;

int buttonState = 0;
int once = 0;
int count = 0;

void setup() {
  Serial.begin(19200);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  brazo.attach(SERVO_BRAZO);
  
  delay(500);
  pinMode(13,OUTPUT);
  delay(3000);
  beginTimer = millis();
  digitalWrite(13,HIGH);
}

void loop() {
  // read the state of the pushbutton value:
  if(timeCompleted())
  {
    digitalWrite(13,LOW);
    Serial.println("Apretado");
    Serial.println(count);
    if(count == 1)
    {
       girar45();
       avanzar(2000);
    }
    else if(count == 2)
    {
       girarIzquierda();
       avanzar(2000); 
    }
    else if(count == 3)
    {
       girar180();
       avanzar(2000);
    }
    else if(count == 4)
    {
      parar();
      bajarBrazo();
      subirBrazo();
      bajarBrazo();
      subirBrazo();
    }
     delay(5000);
     beginTimer = millis();
     digitalWrite(13,HIGH);
     count = 0;
   }
  else 
  {
    buttonState = digitalRead(pinES);
    if (buttonState == HIGH) {
      
    }
    else {
      count++;
      digitalWrite(ledPin,LOW);
    }
    delay(200);
    digitalWrite(ledPin,HIGH);
  }
  endTimer = millis();
  /*buttonState = digitalRead(pinES);
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    once = 1;
    digitalWrite(ledPin,LOW);
    avanzar(2000);
  }
  else {
    digitalWrite(ledPin,HIGH);
    parar();
    if(once == 1)
      Speak();
    once = 0;
  }*/
}
bool timeCompleted()
{
   if(waitTime < endTimer - beginTimer)
      return true;
   return false; 
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
  delay(TIEMPO_GIRO90);
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
}

void girar180()
{
  Serial.println("Giro 180 grados");
  sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(TIEMPO_GIRO180);
  parar(); 
}

void girar45()
{
  Serial.println("Giro 45 grados");
  sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(TIEMPO_GIRO45);
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
