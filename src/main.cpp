/**
 * @file main.cpp
 * @brief Programa principal del carrito de sumo
 */

#include <Arduino.h>
#include <SoftwareSerial.h> //bluetooth

#include "ControladorMotores.h"
#include "ControladorUltrasonico.h"
#include "ControladorInfrarrojo.h"
#include "ControladorGiroscopio.h"

// Definir MODO_DEBUG para activar mensajes seriales
#define MODO_DEBUG
// #define MODO_BT
#define MODO_MPU

// Constantes de configuracion
const uint8_t VELOCIDAD_PWM_DER = 250;
const uint8_t VELOCIDAD_PWM_IZQ = 250;
const uint8_t VELOCIDAD_GIRO = 250;
const unsigned long TIEMPO_ESPERA = 50; // ms

const float POTENCIA_MD = 0.9; //porcentaje de potencia de motor derecho
const float POTENCIA_MI = 0.9; //porcentaje de potencia de motor izquierdo

// Instancias de controladores
ControladorMotores controlador_motores;
ControladorUltrasonico ultrasonico_izquierdo(PIN_ULTRASONIC_IZQ_TRIG, PIN_ULTRASONIC_IZQ_ECHO, "Izquierdo");
ControladorUltrasonico ultrasonico_derecho(PIN_ULTRASONIC_DER_TRIG, PIN_ULTRASONIC_DER_ECHO, "Derecho");
ControladorInfrarrojo infrarrojo_izquierdo(PIN_IR_IZQ, "Izquierdo");
ControladorInfrarrojo infrarrojo_derecho(PIN_IR_DER, "Derecho");
ControladorInfrarrojo infrarrojo_central(PIN_IR_CEN, "Centro");
ControladorInfrarrojo infrarrojo_suelo_delante(PIN_IR_SUELO_DELANTERO, "Suelo Delantero");
ControladorInfrarrojo infrarrojo_suelo_atras(PIN_IR_SUELO_TRASERO, "Suelo Trasero");

#ifdef MODO_MPU
Adafruit_MPU6050 mpu;
ControladorGiroscopio giroscopio(mpu);
#endif

// SoftwareSerial BT(PIN_RX_BT, PIN_TX_BT); // RX | TX

uint8_t potencia(uint8_t velocidad, float potencia){
    return (uint8_t)((float)velocidad * potencia);
}

void setup() {
    #ifdef MODO_DEBUG
    Serial.begin(9600);
    Serial.println("Iniciando sistema del carrito de sumo...");
    #endif

    // Inicializar controladores
    controlador_motores.inicializar();
    ultrasonico_izquierdo.inicializar();
    ultrasonico_derecho.inicializar();
    infrarrojo_izquierdo.inicializar();
    infrarrojo_derecho.inicializar();
    infrarrojo_central.inicializar();
    infrarrojo_suelo_delante.inicializar();
    infrarrojo_suelo_atras.inicializar();

    #ifdef MODO_MPU
    giroscopio.inicializar();
    #endif

    #ifdef MODO_DEBUG
    Serial.println("✅ Sistema inicializado correctamente ✅");
    #endif

    // Pequena pausa para estabilizacion
    delay(500);
    //no inicia hasta que le actives los dos sensores laterales
    while(infrarrojo_izquierdo.detectarObjeto() == false || infrarrojo_derecho.detectarObjeto() == false);
}

void loop() {
    // Leer sensores
    bool objeto_frente_izq = ultrasonico_izquierdo.detectarObjeto();
    bool objeto_frente_der = ultrasonico_derecho.detectarObjeto();
    bool objeto_frente = infrarrojo_central.detectarObjeto();
    bool objeto_lateral_izq = infrarrojo_izquierdo.detectarObjeto();
    bool objeto_lateral_der = infrarrojo_derecho.detectarObjeto();
    bool suelo_atras = infrarrojo_suelo_atras.detectarObjeto();
    // bool suelo_delante = infrarrojo_suelo_delante.detectarObjeto();

    // Logica de comportamiento del carrito de sumo
    if (!suelo_atras) {
        // Cerca del borde - retroceder y girar
        #ifdef MODO_DEBUG
        Serial.println("Cerca del borde - Retrocediendo y girando");
        #endif
        controlador_motores.retroceder(potencia(VELOCIDAD_PWM_DER, POTENCIA_MD), potencia(VELOCIDAD_PWM_IZQ, POTENCIA_MI));
        delay(500);
        controlador_motores.girarDerecha(VELOCIDAD_PWM_DER);
        delay(750);
    }
    else if (objeto_frente_izq || objeto_frente_der || objeto_frente) {
        // Objeto al frente - atacar
        #ifdef MODO_DEBUG
        Serial.println("⚔️ Objeto detectado al frente ⚔️");
        #endif
        controlador_motores.avanzar(potencia(VELOCIDAD_PWM_DER, POTENCIA_MD), potencia(VELOCIDAD_PWM_IZQ, POTENCIA_MI));
    }
    else if (objeto_lateral_izq) {
        // Objeto a la izquierda - girar derecha
        #ifdef MODO_DEBUG
        Serial.println("⚠️ Objeto detectado a la izquierda ⚠️");
        #endif
        controlador_motores.girarIzquierda(VELOCIDAD_GIRO);
        //controlador_motores.retroceder(VELOCIDAD_NORMAL / 4);
    }
    else if (objeto_lateral_der) {
        // Objeto a la derecha - girar izquierda
        #ifdef MODO_DEBUG
        Serial.println("⚠️ Objeto detectado a la derecha ⚠️");
        #endif
        controlador_motores.girarDerecha(VELOCIDAD_GIRO);
        //controlador_motores.retroceder(VELOCIDAD_NORMAL / 4);
    }
    else {
        // Buscar oponente - patron de busqueda
        #ifdef MODO_DEBUG
        Serial.println("👀 Buscando oponente...");
        #endif
        controlador_motores.avanzar(potencia(VELOCIDAD_PWM_DER, POTENCIA_MD) / 4, potencia(VELOCIDAD_PWM_IZQ, POTENCIA_MI) / 4);    
    }
    #ifdef MODO_MPU
    if (giroscopio.estaInclinado(4)) {
        #ifdef MODO_DEBUG
        Serial.println("⚠️ El carrito está inclinado ⚠️");
        #endif
        controlador_motores.retroceder(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(200);
        #ifdef MODO_DEBUG
        Serial.println("⚔️ Retrocediendo para envestir ⚔️");
        #endif
        controlador_motores.avanzar(VELOCIDAD_PWM_DER, VELOCIDAD_PWM_IZQ);
        delay(200);
    }
    #endif

    delay(TIEMPO_ESPERA);
}