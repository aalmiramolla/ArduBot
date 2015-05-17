#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include <Servo.h>
#include "../Config/configuracion.h"

Servo sDerecho; // put your main code here, to run repeatedly:
Servo sIzquierdo;

void hacerCirculo(int radio);
void girarDerecha();
void girarIzquierda();
void girar180();
void avanzar(unsigned int tiempoAvance);
void parar();
void Speak();
void retroceder(unsigned int tiempoRetroceso);

void setup() {
  Serial.begin(9600);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  delay(500);
  pinMode(13,OUTPUT);
  delay(3000);
}

void loop() {

  Serial.println(sDerecho.read());
  delay(1000);
  avanzar(1000);
  Serial.println(sDerecho.read());
  delay(1000);
  retroceder(1000);
  Serial.println(sDerecho.read());
  delay(1000);
  parar();
  delay(5000);
  
}

void hacerCirculo(int radio) {
  Serial.print("Realizo un circulo de: ");
  Serial.println(radio);  
  //int radiomm = radio*10;
  sDerecho.writeMicroseconds(2000);
  sIzquierdo.writeMicroseconds(1320);
  delay(3000);
  parar();
  delay(2000);
  
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

void girarDerecha()
{
  Serial.println("Giro Derecha 90º");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds(SERVO_DERECHO_ATRAS);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ADELANTE);
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
