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
  Serial.begin(19200);
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  delay(500);
  pinMode(13,OUTPUT);
  delay(3000);
  Serial.println("Introduzca el radio del circulo que desee.");
}

void loop() {
  
  hacerCirculo(8);
  /*  while(Serial.available() > 0)
    {
        int radioCirculo = Serial.parseInt();
        Serial.print("He leido: ");
        Serial.println(radioCirculo);
        if(radioCirculo >= 5)
        {
         hacerCirculo(radioCirculo); 
         delay(1000);
        }
        else
          Serial.println("El radio del circulo debe ser mayor que 5.");
        delay(100);
    }*/
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

void pulsosServos(int derecho, int izquierdo)
{
 sDerecho.writeMicroseconds(derecho);
 sIzquierdo.writeMicroseconds(izquierdo);
}

void hacerCirculo(int radio) {
  
  Serial.print("Realizo un circulo de: ");
  Serial.println(radio);  
  int derecho = 2000;
  int izquierdo = 0;
  if(radio == 5)
  {
    izquierdo = 1410;
  }
  else if(radio == 6)
  {
    izquierdo = 1400; 
  }
  else if(radio == 7)
  {
    //RECORRE UN RADIO DE 8.5
     izquierdo = 1390;
  }
  else if(radio == 8)
  {
     izquierdo = 1370;
  }
  else if(radio == 9)
  {
     izquierdo = 1360;
  }
  else if(radio == 10)
  {
     izquierdo = 1355;
  }
  else if(radio == 11)
  {
     izquierdo = 1350;
  }
  else if(radio == 12)
  {
     izquierdo = 1340;
  }
  else if(radio == 13)
  {
     izquierdo = 1335;
  }
  else if(radio == 14)
  {
     izquierdo = 1330;
  }
  else if(radio == 15)
  {
     izquierdo = 1320;
  }
  else if(radio == 16)
  {
     izquierdo = 1315;
  }
  else if(radio == 17)
  {
     izquierdo = 1310;
  }
  else if(radio == 18)
  {
     izquierdo = 1305;
  }
  else if(radio == 19)
  {
     izquierdo = 1300;
  }
  else if(radio == 20)
  {
     izquierdo = 1290;
  }
  pulsosServos(derecho, izquierdo);
}


