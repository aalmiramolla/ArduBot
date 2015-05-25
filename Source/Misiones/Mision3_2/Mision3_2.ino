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
int lineaMax = 1;
bool volviendo = false;
void setup() {
  Serial.begin(19200);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  brazo.attach(SERVO_BRAZO);
  delay(500);
  pinMode(13,OUTPUT);
  digitalWrite(13,OUTPUT);
  for(int i = 0; i < 400; i++)
  {
    qtrrc.calibrate();
  }
  for(unsigned int i = 0; i < NUM_SENSORS;++i)
  {
   Serial.print(qtrrc.calibratedMinimumOn[i]);
   Serial.print(' '); 
  }
  Serial.println();
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
  Serial.println();
  digitalWrite(13,LOW);
  
  delay(3000);
  beginTimer = millis();
  digitalWrite(13,LOW);
  avanzar();
}

void loop() {
  
  
  qtrrc.read(sensorValues);
  buttonState = digitalRead(pinES);
  if(buttonState == LOW)
  {
     parar();
     retroceder(1000);
     girarIzquierda();
     avanzar(); 
  }
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  
  if(sensorValues[NUM_SENSORS-1] > VALOR_NEGRO)
   {
     if(!volviendo)
       count++;
     else 
       count--;
       
     if(count == lineaMax)
     {
       Serial.println("VUELVO");
       Serial.println(count);
       Serial.println(lineaMax);
       Serial.println();
       volviendo = true;
       lineaMax++;
       girar180();
       avanzar();
       
     }
     if(count == 0)
     {
       Serial.println("Inicio");
       Serial.println(count);
       Serial.println(lineaMax);
       Serial.println();
       girar180();
       avanzar();
       if(lineaMax == 4)
       {
         Serial.println("ENTRO EN BUCLE");
         while(true)
             parar(); 
       }
       volviendo = false;
       
     }
     /*Hemos encontrado linea negra*/
     Serial.println("Linea Max");
       Serial.println(lineaMax);
       Serial.println("count");
       Serial.println(count);
     digitalWrite(13,HIGH);
     //Speak();
     delay(500);
   }
     
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

void avanzar() {
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION);
   //delay(tiempoAvance);
   //parar();
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
