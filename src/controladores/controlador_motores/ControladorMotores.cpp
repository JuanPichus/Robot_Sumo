/**
 * @file ControladorMotores.cpp
 * @brief Implementacion de la clase ControladorMotores
 */

#include "ControladorMotores.h"

// Definir MODO_DEBUG para activar mensajes seriales
 #define MODO_DEBUG

ControladorMotores::ControladorMotores() 
    : pin_enable_izq(PIN_MOTOR_IZQ_ENABLE),
      pin_in1_izq(PIN_MOTOR_IZQ_IN1),
      pin_in2_izq(PIN_MOTOR_IZQ_IN2),
      pin_enable_der(PIN_MOTOR_DER_ENABLE),
      pin_in1_der(PIN_MOTOR_DER_IN1),
      pin_in2_der(PIN_MOTOR_DER_IN2),
      motores_habilitados(false) {
}

void ControladorMotores::inicializar() {
    pinMode(pin_enable_izq, OUTPUT);
    pinMode(pin_in1_izq, OUTPUT);
    pinMode(pin_in2_izq, OUTPUT);
    pinMode(pin_enable_der, OUTPUT);
    pinMode(pin_in1_der, OUTPUT);
    pinMode(pin_in2_der, OUTPUT);
    
    detener();
    encenderMotores();

    #ifdef MODO_DEBUG
    Serial.println("✅ Motores inicializados");
    #endif

    #ifdef MODO_BT
    BT.println("✅ Motores inicializados");
    #endif
}

void ControladorMotores::encenderMotores() {
    digitalWrite(pin_enable_izq, HIGH);
    digitalWrite(pin_enable_der, HIGH);
    motores_habilitados = true;

    #ifdef MODO_DEBUG
    Serial.println("🟢 Motores encendidos");
    #endif
}

void ControladorMotores::apagarMotores() {
    digitalWrite(pin_enable_izq, LOW);
    digitalWrite(pin_enable_der, LOW);
    motores_habilitados = false;

    #ifdef MODO_DEBUG
    Serial.println("🔴 Motores apagados");
    #endif
}

void ControladorMotores::avanzar(uint8_t velocidad_r, uint8_t velocidad_l) {
    if (!motores_habilitados) return;

    // Motor izquierdo
    digitalWrite(pin_in1_izq, HIGH);
    digitalWrite(pin_in2_izq, LOW);
    analogWrite(pin_enable_izq, velocidad_l);

    // Motor derecho
    digitalWrite(pin_in1_der, HIGH);
    digitalWrite(pin_in2_der, LOW);
    analogWrite(pin_enable_der, velocidad_r);

    #ifdef MODO_DEBUG
    Serial.print("⏱ VELOCIDAD M1: ");
    Serial.println(velocidad_r);
    Serial.print("⏱ VELOCIDAD M2: ");
    Serial.println(velocidad_l);
    #endif
}

void ControladorMotores::retroceder(uint8_t velocidad_r, uint8_t velocidad_l) {
    if (!motores_habilitados) return;

    // Motor izquierdo
    digitalWrite(pin_in1_izq, LOW);
    digitalWrite(pin_in2_izq, HIGH);
    analogWrite(pin_enable_izq, velocidad_l);

    // Motor derecho
    digitalWrite(pin_in1_der, LOW);
    digitalWrite(pin_in2_der, HIGH);
    analogWrite(pin_enable_der, velocidad_r);

    #ifdef MODO_DEBUG
    Serial.print("🔙 RETROCEDIENDO M1: ");
    Serial.println(velocidad_r);
    Serial.print("🔙 RETROCEDIENDO M2: ");
    Serial.println(velocidad_l);
    #endif
}

void ControladorMotores::detener() {
    // Motor izquierdo
    digitalWrite(pin_in1_izq, LOW);
    digitalWrite(pin_in2_izq, LOW);
    analogWrite(pin_enable_izq, 0);

    // Motor derecho
    digitalWrite(pin_in1_der, LOW);
    digitalWrite(pin_in2_der, LOW);
    analogWrite(pin_enable_der, 0);

    #ifdef MODO_DEBUG
    Serial.println("🛑 Motores detenidos");
    #endif
}

void ControladorMotores::girarIzquierda(uint8_t velocidad) {
    if (!motores_habilitados) return;

    // Motor izquierdo retrocede
    digitalWrite(pin_in1_izq, LOW);
    digitalWrite(pin_in2_izq, HIGH);
    analogWrite(pin_enable_izq, velocidad);

    // Motor derecho avanza
    digitalWrite(pin_in1_der, HIGH);
    digitalWrite(pin_in2_der, LOW);
    analogWrite(pin_enable_der, velocidad);

    #ifdef MODO_DEBUG
    Serial.print("↩️ Girando a la izquierda a velocidad ");
    Serial.println(velocidad);
    #endif

    #ifdef MODO_BT
    BT.print("↩️ Girando a la izquierda a velocidad ");
    BT.println(velocidad);
    #endif
}

void ControladorMotores::girarDerecha(uint8_t velocidad) {
    if (!motores_habilitados) return;

    // Motor izquierdo avanza
    digitalWrite(pin_in1_izq, HIGH);
    digitalWrite(pin_in2_izq, LOW);
    analogWrite(pin_enable_izq, velocidad);

    // Motor derecho retrocede
    digitalWrite(pin_in1_der, LOW);
    digitalWrite(pin_in2_der, HIGH);
    analogWrite(pin_enable_der, velocidad);

    #ifdef MODO_DEBUG
    Serial.print("↪️ Girando a la derecha a velocidad ");
    Serial.println(velocidad);
    #endif

    #ifdef MODO_BT
    BT.print("↪️ Girando a la derecha a velocidad ");
    BT.println(velocidad);
    #endif
}
