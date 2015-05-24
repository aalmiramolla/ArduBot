#include <Maxbotix.h>
#include <PololuQTRSensors.h>
#include <QTRSensors.h>
#include<Servo.h>
#include "../Config/configuracion.h"

Servo sDerecho;
Servo sIzquierdo;
Servo sBrazo;

void girarDerecha();
void girarIzquierda();
void avanzar(unsigned int tiempo);
void parar();
void Speak();
void retroceder(unsigned int tiempo);
void subirBrazo();
void bajarBrazo();
void accionEspacio();
void aumentarVelocidad();
void disminuirVelocidad();

int velocidad = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(13,OUTPUT);
  Serial.println("Empezamos");
  sDerecho.attach(PIN_SERVO_DERECHO,SERVO_MIN,SERVO_MAX);
  sIzquierdo.attach(PIN_SERVO_IZQUIERDO,SERVO_MIN,SERVO_MAX);
  delay(500);
  delay(3000);;
}

void loop() {
  // put your main code here, to run repeatedly:
  retroceder(400);
  girarIzquierda();
  retroceder(400);
  girarIzquierda();
  retroceder(700);
  girarDerecha();
  girarDerecha();
  Speak();
  delay(5000);
 /* while(Serial.available() > 0)
  {
     int codigo = Serial.parseInt();
      Serial.println("He leido");
      Serial.println(codigo);
       if(codigo == COM_ADELANTE)
       {
         avanzar(100);
       } else if(codigo == COM_ATRAS)
       {
         retroceder(100);
       } else if(codigo == COM_IZQUIERDA)
       {
         girarIzquierda();
       } else if(codigo == COM_DERECHA)
       {
         girarDerecha();
       } else if(codigo == COM_ESPACIO)
       {
         accionEspacio(); 
       } else if(codigo == COM_SUMA)
       {
        aumentarVelocidad();
       } else if(codigo == COM_RESTA)
       {
        disminuirVelocidad();
       } else if(codigo == COM_BRAZO_ARRIBA)
        {
         subirBrazo();
        }else if(codigo == COM_BRAZO_ABAJO)
       {
        bajarBrazo();
       } else {
        Serial.println(" El codigo recibido no es valido.");
       }
  }
*/
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
  Serial.println("Giro Izquierda");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds( SERVO_DERECHO_ADELANTE);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ATRAS);
  delay(COM_TIEMPO_CONTROL);
  parar();
}

void girarDerecha()
{
  Serial.println("Giro Derecha");
  sDerecho.writeMicroseconds(SERVO_PARADO);
  sIzquierdo.writeMicroseconds(SERVO_PARADO);
  delay(30);
  sDerecho.writeMicroseconds(SERVO_DERECHO_ATRAS);
  sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_ADELANTE);
  delay(COM_TIEMPO_CONTROL);
  parar();
 
}

void avanzar(unsigned int tiempo) {
  int posibleCorte = 0;
  Serial.println("Avanzo");
  digitalWrite(13,HIGH);
   sDerecho.writeMicroseconds(SERVO_DERECHO_AVANZAR_CORRECCION + velocidad);
   sIzquierdo.writeMicroseconds(SERVO_IZQUIERDO_AVANZAR_CORRECCION-velocidad);
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
