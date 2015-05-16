#ifndef Motors_h
#define Motors_h

#include <../PololuWheelEncoders/PololuWheelEncoders.h>

#ifdef __cplusplus

const double PI = 3.14159265359;

/////////////////////////////////////////////////
/*
                  Constantes
*/
/////////////////////////////////////////////////
//80 mm entre ruedas
const int wheelDistance = 80;
//21mm radio rueda
const int radius = 21;
//24 cuentas rueda
const int counts = 24;
//6 mm por cuenta
const int mmPerCount = 6;

const int ES = 10;

/////////////////////////////////////////////////



class Motors
{
  public:

    Motors() {}

    void run();
    void run(int distancia);
    void turnLeft(int angle);
    void turnRight(int angle);
    void reset();
    int calculeCountsTurn(double angulo);
    int calculeCountsRun(double dist);
    bool pause(int m);

    void setSpeed(int s, double sm);
    void setCorrection(int c);

    void initMotors(unsigned char ENA, unsigned char IN1, unsigned char IN2, unsigned char ENB, unsigned char IN3, unsigned char IN4);
    void initEncoders(unsigned char OUTA1, unsigned char OUTB1, unsigned char OUTA2, unsigned char OUTB2);

  private:

    //Corrección de rozamiento por la rueda de atrás
    int correction = 23;

    unsigned char _ENA;
    unsigned char _IN1;
    unsigned char _IN2;
    unsigned char _ENB;
    unsigned char _IN3;
    unsigned char _IN4;

    int countsM1 = 0;
    int countsM2 = 0;

    int speed = 90;
    double speedMultiplier = 2;

    PololuWheelEncoders encoders;
};

extern "C" {
#endif // __cplusplus

void motors_run(int distanciaCounts);
void motors_turn_left(int angleCounts);
void motors_turn_right(int angleCounts);
void motors_reset();
int motors_calcule_counts_turn(double angle);
int motors_calcule_counts_run(double distance);
bool motors_pause(int m);

void init_motors(unsigned char ENA, unsigned char IN1, unsigned char IN2, unsigned char ENB, unsigned char IN3, unsigned char IN4);
void init_encoders(unsigned char OUTA1, unsigned char OUTB1, unsigned char OUTA2, unsigned char OUTB2);

#ifdef __cplusplus
}
#endif

#endif
