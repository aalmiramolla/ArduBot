#include "../Config/configuracion.h"

#include <Motors.h>

Motors motors;

void setup()
{  
  Serial.begin(9600); 
 
   // Motores
  motors.initMotors(ENA, IN1, IN2, ENB, IN3, IN4);
  motors.initEncoders(OUT1, OUT2, OUT3, OUT4);
  motors.setSpeed(motorSpeed, speedMultiplier);
    
}

void loop()
{
  motors.run(300);
}
