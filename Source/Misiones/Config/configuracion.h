/****************************************************************************************************************
*  
*              CONSTANTES
*
*****************************************************************************************************************/
//IR 
const unsigned int NUM_SENSORS = 2;
const unsigned int TIMEOUT = 2500;
const unsigned int EMITTER_PIN = 2;
const unsigned int VALOR_NEGRO = 500;

// Ultra Sonido
const unsigned char ULTRA_SOUND_PIN = 6;


//Servos
const unsigned int SERVO_PARADO = 1500;
const unsigned int SERVO_DERECHO_ADELANTE = 2000;
const unsigned int SERVO_DERECHO_AVANZAR_CORRECCION = 1810;
const unsigned int SERVO_DERECHO_ATRAS_CORRECCION = 1200;
const unsigned int SERVO_DERECHO_ATRAS = 1000;
const unsigned int SERVO_IZQUIERDO_ADELANTE = 1000;
const unsigned int SERVO_IZQUIERDO_AVANZAR_CORRECCION = 1000;

const unsigned int SERVO_IZQUIERDO_ATRAS = 2000;
const unsigned int SERVO_MIN = 1000;
const unsigned int SERVO_MAX = 2000;



const unsigned int SERVO_BRAZO_ARRIBA = 90;
const unsigned int SERVO_BRAZO_ABAJO = 0;

//const unsigned int TIEMPO_GIRO90 = 617;
const unsigned int TIEMPO_GIRO90 = 545;
const unsigned int TIEMPO_GIRO180 = 1050;
const unsigned int TIEMPO_GIRO45 = 290;

const unsigned int COM_TIEMPO_CONTROL = 150;
const unsigned int COM_TIEMPO_CONTROL_AVANZAR = 2000;
const unsigned int TIEMPO_PASO_ADELANTE = 435;

// BRAZO
const unsigned int PIN_SERVO_DERECHO = 9;
const unsigned int PIN_SERVO_IZQUIERDO = 10;
const unsigned int SERVO_BRAZO = 11;
const unsigned int PIN_BRAZO_IR_TRIG = 7;
const unsigned int PIN_BRAZO_IR_ECHO = 5;

//ZUMBADOR
// Zumbador
const int SPEAKER = 12;
const int numTonesSpeaker = 10;

int tonesSpeaker[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

//Final de Carrera
const int pinES = 8;

const int ledPin = 13;

// PROTOCOLO DE COMUNICACIÓN
const int COM_ADELANTE = 10;
const int COM_ATRAS = 11;
const int COM_IZQUIERDA = 12;
const int COM_DERECHA = 13;

const int COM_ESPACIO = 20;

const int COM_SUMA = 30;
const int COM_RESTA = 31;

const int COM_BRAZO_ARRIBA = 40;
const int COM_BRAZO_ABAJO = 41;

//FIN DE PROTOCOLO DE COMUNICACIÓN... POR EL MOMENTO.
