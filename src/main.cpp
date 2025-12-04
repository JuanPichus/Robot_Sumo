/**
 * @file main.cpp
 * @brief Programa principal del carrito de sumo
 */

#include <Arduino.h>

#include "ControladorMotores.h"
#include "ControladorUltrasonico.h"
#include "ControladorInfrarrojo.h"
#include "ControladorGiroscopio.h"
#include "ControladorServo.h"
#include "Bluetooth.h"

// Definir MODO_DEBUG para activar mensajes seriales
// #define MODO_DEBUG //*

// Definir MODO_BT para activar mensajes bluetooth
// #define MODO_BT //*

// Definir MODO_MPU para activar el giroscopio
// #define MODO_MPU //*

//Definir MODO_SERVO para activar el servo
// #define MODO_SERVO //*

// Constantes de configuracion
const uint8_t VELOCIDAD_PWM_DER = 255;
const uint8_t VELOCIDAD_PWM_IZQ = 255;
const uint8_t VELOCIDAD_GIRO = 255;
const unsigned long TIEMPO_ESPERA = 50; // ms

// Instancias de controladores
ControladorMotores controlador_motores;
ControladorUltrasonico ultrasonico_izquierdo(PIN_US_IZQ_TRIG, PIN_US_IZQ_ECHO, "US_Izquierdo");
ControladorUltrasonico ultrasonico_derecho(PIN_US_DER_TRIG, PIN_US_DER_ECHO, "US_Derecho");
ControladorUltrasonico ultrasonico_lateral_izquierdo(PIN_US_LATERAL_IZQ_TRIG, PIN_US_LATERAL_IZQ_ECHO, "US_Lateral_Izquierdo");
ControladorUltrasonico ultrasonico_lateral_derecho(PIN_US_LATERAL_DER_TRIG, PIN_US_LATERAL_DER_ECHO, "US_Lateral_Derecho");
ControladorInfrarrojo infrarrojo_suelo_derecha(PIN_IR_SUELO_DER, "Suelo_Derecha");
ControladorInfrarrojo infrarrojo_suelo_izquierda(PIN_IR_SUELO_IZQ, "Suelo_Izquierda");


#ifdef MODO_MPU
Adafruit_MPU6050 mpu;
ControladorGiroscopio giroscopio(mpu);
#endif

#ifdef MODO_SERVO
Servo servo_motor;
ControladorServo controlador_servo(PIN_SERVO_ATAQUE, servo_motor, "Servo_Ataque");
#endif

void setup() {
    #ifdef MODO_DEBUG
    Serial.begin(9600);
    while(!Serial); // Esperar a que Serial este listo
    delay(100);
    Serial.println(F("--- INICIALIZANDO ROBOT SUMO ---"));
    #endif

    // Inicializar controladores
    controlador_motores.inicializar();
    ultrasonico_izquierdo.inicializar();
    ultrasonico_derecho.inicializar();
    ultrasonico_lateral_izquierdo.inicializar();
    ultrasonico_lateral_derecho.inicializar();
    infrarrojo_suelo_derecha.inicializar();
    infrarrojo_suelo_izquierda.inicializar();

    #ifdef MODO_MPU
    giroscopio.inicializar();
    #endif

    #ifdef MODO_SERVO
    controlador_servo.inicializar();
    controlador_servo.moverA(30); // Posicion inicial
    #endif

    #ifdef MODO_BT
    BT_inicializar(9600);
    BT_println(F("--- INICIANDO ROBOT SUMO ---"));
    #endif

    #ifdef MODO_DEBUG
    Serial.println(F("--- INICIALIZACION COMPLETA ---"));
    #endif

    // Pequena pausa para estabilizacion
    delay(500);
    //no inicia hasta que le actives los dos sensores laterales
    while(ultrasonico_lateral_derecho.detectarObjeto() == false || ultrasonico_lateral_izquierdo.detectarObjeto() == false);
}

void loop() {
    // Leer sensores
    bool objeto_frente_der = ultrasonico_derecho.detectarObjeto();
    bool objeto_frente_izq = ultrasonico_izquierdo.detectarObjeto();
    bool objeto_lateral_der = ultrasonico_lateral_derecho.detectarObjeto();
    bool objeto_lateral_izq = ultrasonico_lateral_izquierdo.detectarObjeto();
    bool suelo_derecha = infrarrojo_suelo_derecha.detectarObjeto();
    bool suelo_izquierda = infrarrojo_suelo_izquierda.detectarObjeto(); 

    //* Logica de comportamiento del carrito de sumo

    if (!suelo_derecha) {
        // Cerca del borde - retroceder y girar
        #ifdef MODO_DEBUG
        Serial.println(F("[!] Cerca del borde derecho"));
        #endif

        controlador_motores.retroceder(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(1000);
        controlador_motores.girarIzquierda(VELOCIDAD_PWM_DER);
        delay(1000);
    }
    else if (!suelo_izquierda) {
        // Cerca del borde - retroceder y girar
        #ifdef MODO_DEBUG
        Serial.println(F("[!] Cerca del borde izquierdo"));
        #endif
        controlador_motores.retroceder(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(1000);
        controlador_motores.girarDerecha(VELOCIDAD_PWM_IZQ);
        delay(1000);
    }
    #ifdef MODO_MPU
    else if (giroscopio.estaInclinado(-7)) {
        #ifdef MODO_DEBUG
        Serial.println(F("[!] Carrito inclinado"));
        #endif
        controlador_motores.retroceder(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(700);
        #ifdef MODO_DEBUG
        Serial.println(F("[!!!] Retrocediendo para envestir"));
        #endif
        controlador_motores.avanzar(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(400);
    }
    #endif
    else if (objeto_frente_der || objeto_frente_izq) {
        // Objeto al frente - atacar
        #ifdef MODO_DEBUG
        Serial.println(F("[!!!] Objeto al frente - atacando"));
        #endif
        controlador_motores.avanzar(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);

        #ifdef MODO_SERVO
        Serial.println(F("Atacando con servo"));
        controlador_servo.atacar();
        #endif
    }
    else if (objeto_lateral_izq) {
        // Objeto a la izquiersda - girar izquierda
        #ifdef MODO_DEBUG
        Serial.println(F("[!] Objeto a la izquierda"));
        #endif
        controlador_motores.girarIzquierda(VELOCIDAD_GIRO);
    }
    else if (objeto_lateral_der) {
        // Objeto a la derecha - girar derecha
        #ifdef MODO_DEBUG
        Serial.println(F("[!] Objeto a la derecha"));
        #endif
        controlador_motores.girarDerecha(VELOCIDAD_GIRO);
    }
    else {
        // Buscar oponente - patron de busqueda
        #ifdef MODO_DEBUG
        Serial.println(F("[?] Buscando oponente..."));
        #endif
        controlador_motores.avanzar(VELOCIDAD_PWM_DER / 2, VELOCIDAD_PWM_IZQ / 2); //busqueda lineal
        // controlador_motores.girarIzquierda(VELOCIDAD_GIRO / 2); //busqueda en circulo 
        delay(100);
    }
    
    delay(TIEMPO_ESPERA);
}