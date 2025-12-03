//Pines para motores
#define PIN_MOTOR_IZQ_ENABLE 11 //pin pwm
#define PIN_MOTOR_IZQ_IN1 9
#define PIN_MOTOR_IZQ_IN2 10
#define PIN_MOTOR_DER_ENABLE 6 //pin pwm 
#define PIN_MOTOR_DER_IN1 7
#define PIN_MOTOR_DER_IN2 8

//Pines para detectar enemigo (ultrasonido)
#define PIN_ULTRASONIC_IZQ_TRIG A1
#define PIN_ULTRASONIC_IZQ_ECHO A0

#define PIN_ULTRASONIC_DER_TRIG A6
#define PIN_ULTRASONIC_DER_ECHO A7

//Pines para detectar enemigo (infrarrojo)
#define PIN_IR_IZQ 5
#define PIN_IR_CEN 4
#define PIN_IR_DER 12

//Pines para detectar perímetro (dojo)
#define PIN_IR_SUELO_IZQ 13
#define PIN_IR_SUELO_DER 2

//Pines para MPU6050 (giroscopio y acelerometro)
#define MPU_SDA A4
#define MPU_SCL A5

//Pines servo de ataque
#define PIN_SERVO_ATAQUE 3

//Pines bluetooth (A2=D16, A3=D17)
#define PIN_RX_BT A2  // Conectar al TX del módulo BT
#define PIN_TX_BT A3  // Conectar al RX del módulo BT
