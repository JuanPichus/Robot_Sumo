//Pines para motores
#define PIN_MOTOR_IZQ_ENABLE 11 //pin pwm
#define PIN_MOTOR_IZQ_IN1 9
#define PIN_MOTOR_IZQ_IN2 10
#define PIN_MOTOR_DER_ENABLE 6 //pin pwm 
#define PIN_MOTOR_DER_IN1 7
#define PIN_MOTOR_DER_IN2 8

//Pines para detectar enemigo (ultrasonido)
#define PIN_US_IZQ_TRIG A1 //cable morado
#define PIN_US_IZQ_ECHO A0 //cable gris

#define PIN_US_DER_TRIG A6 //cable morado
#define PIN_US_DER_ECHO A7 //cable verde

#define PIN_US_LATERAL_IZQ_TRIG A3 //color morado
#define PIN_US_LATERAL_IZQ_ECHO A2 //color verde

#define PIN_US_LATERAL_DER_TRIG A5 //color blanco
#define PIN_US_LATERAL_DER_ECHO A4 //color negro

//Pines para detectar perímetro (dojo)
#define PIN_IR_SUELO_IZQ 12
#define PIN_IR_SUELO_DER 2

// Pines para MPU6050 (giroscopio y acelerometro) //! ya no se pueden usar porque usamos 4 ultrasonicos que abarcan los 8 puertos analógicos del NANO
// #define MPU_SDA A4
// #define MPU_SCL A5

//Pines servo de ataque
#define PIN_SERVO_ATAQUE 3

//Pines bluetooth (A2=D16, A3=D17)
#define PIN_RX_BT A2  // Conectar al TX del módulo BT
#define PIN_TX_BT A3  // Conectar al RX del módulo BT
