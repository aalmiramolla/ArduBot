/*
  Motors.cpp - Intento de libreria para mover los motores
  Creado por Javier Cano y Jaume Gasa. 13 de Mayo de 2014
  Under GPL
*/

#include "Motors.h"
#include "Arduino.h" /* Esta libreria? */
#include "PololuWheelEncoders.cpp"

void
Motors::setSpeed(int s, double sm)
{
  speed = s;
  speedMultiplier = sm;
}

void
Motors::setCorrection(int c)
{
  correction = c;
}

void
Motors::initMotors(unsigned char ENA, unsigned char IN1, unsigned char IN2, unsigned char ENB, unsigned char IN3, unsigned char IN4)
{
  pinMode(ENA, OUTPUT);
  _ENA = ENA;
  pinMode(IN1, OUTPUT);
  _IN1 = IN1;
  pinMode(IN2, OUTPUT);
  _IN2 = IN2;
  pinMode(ENB, OUTPUT);
  _ENB = ENB;
  pinMode(IN3, OUTPUT);
  _IN3 = IN3;
  pinMode(IN4, OUTPUT);
  _IN4 = IN4;
  pinMode(ES, INPUT);
}

void
Motors::initEncoders(unsigned char OUTA1, unsigned char OUTB1, unsigned char OUTA2, unsigned char OUTB2)
{
  encoders.init(OUTA1,OUTB1,OUTA2,OUTB2);
}

void
Motors::run()
{
  int crash = LOW;
  crash = digitalRead(ES);
  if(crash == LOW)
  {
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);

    analogWrite(_ENA, speed);

    digitalWrite(_IN3, HIGH);
    digitalWrite(_IN4, LOW);

    analogWrite(_ENB, speed);
  }
  else
  {
    pause(1);
    pause(2);
  }
}

void
Motors::run(int distancia)
{
  int distanciaCounts = calculeCountsRun(distancia);
  int crash = LOW;
  reset();
  boolean m1 = true;
  boolean m2 = true;

  while(m1 || m2)
  {
    crash = digitalRead(ES);
    if(crash == LOW) {
      if(encoders.getCountsM1()>countsM1-distanciaCounts)
      {
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);

        analogWrite(_ENA, speed);

        digitalWrite(_IN3, HIGH);
        digitalWrite(_IN4, LOW);

        analogWrite(_ENB, speed);

      }
      else
      {
        m1 = pause(1);
        m2 = pause(2);
      }
    }
    else
    {
      pause(1);
      pause(2);
    }
  }
}

void
Motors::turnLeft(int angle)
{
  int angleCounts = calculeCountsTurn(angle);
  int crash = LOW;
  reset();
  boolean m1 = true;
  boolean m2 = true;

  while(m1 || m2)
  {
    crash = digitalRead(ES);
    if(crash == LOW) {
      if(encoders.getCountsM2()>countsM2-angleCounts)
      {
        digitalWrite(_IN3, LOW);
        digitalWrite(_IN4, HIGH);

        analogWrite(_ENB, speed*speedMultiplier);
      }
      else
      {
        m2 = pause(2);
      }

      if(encoders.getCountsM1()>countsM1-angleCounts)
      {
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);

        analogWrite(_ENA, speed*speedMultiplier);
      }
      else
      {
        m1 = pause(1);
      }
    }
    else
    {
      pause(1);
      pause(2);
    }
  }
}

void
Motors::turnRight(int angle)
{
  int angleCounts = calculeCountsTurn(angle);
  int crash = LOW;
  reset();
  boolean m1 = true;
  boolean m2 = true;

  while(m1 || m2)
  {
    crash = digitalRead(ES);
    if(crash == LOW) {
      if(encoders.getCountsM2()<countsM2+angleCounts)
      {
        digitalWrite(_IN3, HIGH);
        digitalWrite(_IN4, LOW);

        analogWrite(_ENB, speed*speedMultiplier);
      }
      else
      {
        m2 = pause(2);
      }

      if(encoders.getCountsM1()<countsM1+angleCounts)
      {
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);

        analogWrite(_ENA, speed*speedMultiplier);
      }
      else
      {
        m1 = pause(1);
      }
    }
    else
    {
      pause(1);
      pause(2);
    }
  }
}


void
Motors::reset()
{
  pause(1);
  pause(2);
  countsM1 = encoders.getCountsM1();
  countsM2 = encoders.getCountsM2();
}


bool
Motors::pause(int m) {

  boolean ok = false;
  if(m==1) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, LOW);
    analogWrite(_ENA, 0);
    ok = true;
  }
  else if(m==2) {
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, LOW);
    analogWrite(_ENB, 0);
    ok = true;
  }
  return !ok;
}

int
Motors::calculeCountsTurn(double angle)
{
  return angle * (wheelDistance + correction) * counts / (4 * PI * radius);
}

int
Motors::calculeCountsRun(double distance)
{
  return distance/mmPerCount;
}
