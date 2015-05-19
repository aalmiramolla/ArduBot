#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include <Servo.h>
#include <Ultrasonic.h>

#include "../Config/configuracion.h"

Servo sDerecho;
Servo sIzquierdo;
Servo sBrazo;

Ultrasonic ultrasonic(PIN_BRAZO_IR_TRIG,PIN_BRAZO_IR_ECHO); // (Trig PIN, Echo PIN);

void girarDerecha(unsigned int tiempo);
void girarIzquierda(unsigned int tiempo);
void avanzar(unsigned int tiempo);
void avanzarATope();
void parar();
void Speak();
void retroceder(unsigned int tiempo);
void subirBrazo();
void bajarBrazo();
void accionEspacio();
void aumentarVelocidad();
void disminuirVelocidad();
void aparcar();
bool timeCompleted();
//---------------------------------------------FUNCTION PROTOTYPE---------------------//
void measureDistance();  // 

unsigned long beginTimer = 0;
unsigned long endTimer = 0;
unsigned long waitTime = 1000;


int distance; // An interger variable that will contain the distance measured from the returning pulse.
unsigned long pulseduration=0; // A long varible that will contain the number of milisecond of the returning pulse.
unsigned int i = 0; 
int distanceMAX = 0;
int distanciaAparcar = 0;
bool encontradoPosible = false;
int umbralDeError = 0;

int velocidad = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(13,OUTPUT);
  Serial.println("Empezamos");
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  sBrazo.attach(SERVO_BRAZO);
  subirBrazo();
  delay(500);
  pinMode(13,OUTPUT);
  digitalWrite(13,OUTPUT);
//  measureDistance();
//  distanceMAX = distance;
  //Serial.println(distanceMAX);
  delay(2000);
  
  avanzarATope();
}

void loop() {
  measureDistance();
  Serial.println(distance);
  //Serial.println(encontradoPosible);
  if(distance > 30){
    Serial.println("IF");
    if(beginTimer == 0) {
       Serial.println("Empiezo a contar");
      beginTimer = millis();
    }
    }
    else {
        Serial.println("ELSE Begin");
        Serial.println(beginTimer);
        Serial.println("ELSE END");
      Serial.println(endTimer);
        if(beginTimer != 0)
            endTimer = millis();
    if(timeCompleted())
    {
      Serial.println("Aparco");
      Serial.println(beginTimer);
      Serial.println(endTimer);
      parar();
      delay(1000);
      aparcar();
    } else 
        avanzarATope();
    }
}

bool timeCompleted()
{
   if(waitTime < (endTimer - beginTimer))
      return true;
   return false; 
}

void measureDistance() 
{
  distance = ultrasonic.Ranging(CM); // THE LONG VALUE WILL BE AUTOMATICALLY CONVERTED INTO INTEGER
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

void girarIzquierda(unsigned int tiempo)
{
  Serial.println("Giro Izquierda");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds( SERVO_DERECHO_ADELANTE);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(tiempo);
  parar();
}

void girarDerecha(unsigned int tiempo)
{
  Serial.println("Giro Derecha");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds(SERVO_DERECHO_ATRAS);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ADELANTE);
  delay(tiempo);
  parar();
 
}

void avanzar(unsigned int tiempo) {
  int posibleCorte = 0;
  Serial.println("Avanzo");
  digitalWrite(13,HIGH);
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION + velocidad);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION-velocidad);
   delay(tiempo);
   parar();
}

void avanzarATope()
{
  Serial.println("Avanzo a tope");
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION + velocidad);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION-velocidad);
}

void retroceder(unsigned int tiempo) {
    int posibleCorte = 0;
  Serial.println("Retrocedo");
   sDerecho.writeMicroseconds(SERVO_DERECHO_ATRAS_CORRECCION - velocidad);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS + velocidad);
   delay(tiempo);
   /*while(posibleCorte < 4)
   {
     int codigo = Serial.parseInt();
      if(codigo == COM_ESPACIO)
      {
        Serial.println("Accion Espacio");
        parar();
        break;
      }
      else
      {
        delay(500);
      }
    posibleCorte++;
   }*/
   parar();
 }
 
void parar() {
  Serial.println("Paro");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
}

void accionEspacio()
{
  Serial.println("Accion Espacio");
  if(sDerecho.read() == 90)
  {
     avanzar(100);
  }
  else
  {
     parar(); 
  }
}

void disminuirVelocidad()
{
  Serial.println("Disminuyo");
  velocidad = velocidad - 100;
}

void aparcar()
{
  retroceder(400);
  girarIzquierda(COM_TIEMPO_CONTROL);
  retroceder(400);
  girarIzquierda(COM_TIEMPO_CONTROL);
  retroceder(800);
  girarDerecha(COM_TIEMPO_CONTROL);
  girarDerecha(COM_TIEMPO_CONTROL+20);
  Speak();
  delay(5000);
}

void aumentarVelocidad()
{
  Serial.println("Aumento");
  velocidad = velocidad + 100;
  /* int velServoDerecho = sDerecho.read();
  int velServoIzquierdo = sIzquierdo.read();
  
  sDerecho.write(velServoDerecho+1);
  sIzquierdo.write(velServoIzquierdo-1);*/
  
}

void subirBrazo()
{
  Serial.println("Subo");
}

void bajarBrazo()
{
  Serial.println("Bajo");
}
