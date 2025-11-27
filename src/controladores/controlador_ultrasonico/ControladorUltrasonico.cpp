/**
 * @file ControladorUltrasonico.cpp
 * @brief Implementacion de la clase ControladorUltrasonico
 */

#include "ControladorUltrasonico.h"

// Definir MODO_DEBUG para activar mensajes seriales
 #define MODO_DEBUG

ControladorUltrasonico::ControladorUltrasonico(uint8_t pin_tr, uint8_t pin_ech, const String& nombre)
    : pin_trigger(pin_tr),
      pin_echo(pin_ech),
      distancia_maxima_deteccion(30.0),
      nombre_sensor(nombre) {
}

void ControladorUltrasonico::inicializar() {
    pinMode(pin_trigger, OUTPUT);
    pinMode(pin_echo, INPUT);
    digitalWrite(pin_trigger, LOW);

    #ifdef MODO_DEBUG
    Serial.print("✅ Sensor ultrasonico ");
    Serial.print(nombre_sensor);
    Serial.println(" inicializado");
    #endif

    #ifdef MODO_BT
    BT.print("✅ Sensor ultrasonico ");
    BT.print(nombre_sensor);
    BT.println(" inicializado");
    #endif
}

float ControladorUltrasonico::medirDistancia() {
    // Asegurar que el trigger esta en LOW
    digitalWrite(pin_trigger, LOW);
    delayMicroseconds(2);

    // Generar pulso de 10us
    digitalWrite(pin_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin_trigger, LOW);

    // Medir el tiempo de respuesta
    unsigned long duracion = pulseIn(pin_echo, HIGH, 30000); // Timeout de 30ms

    // Calcular distancia (velocidad del sonido = 343 m/s = 0.0343 cm/us)
    // Dividir entre 2 porque el sonido va y vuelve
    float distancia = duracion * 0.0343 / 2.0;

    return distancia;
}

bool ControladorUltrasonico::detectarObjeto() {
    float distancia = obtenerDistancia();
    bool detectado = (distancia > 5 && distancia <= distancia_maxima_deteccion);

    #ifdef MODO_DEBUG
    if (detectado) {
        Serial.print("📡 ");
        Serial.print(nombre_sensor);
        Serial.print(": Objeto detectado a ");
        Serial.print(distancia);
        Serial.println(" cm");
    }
    #endif

    #ifdef MODO_BT
    if (detectado) {
        BT.print("📡 ");
        BT.print(nombre_sensor);
        BT.print(": Objeto detectado a ");
        BT.print(distancia);
        BT.println(" cm");
    }
    #endif

    return detectado;
}

float ControladorUltrasonico::obtenerDistancia() {
    return medirDistancia();
}

void ControladorUltrasonico::establecerDistanciaMaxima(float distancia_maxima) {
    distancia_maxima_deteccion = distancia_maxima;

    #ifdef MODO_DEBUG
    Serial.print("❕ Sensor Ultrasonico ");
    Serial.print(nombre_sensor);
    Serial.print(": Distancia maxima establecida a ");
    Serial.print(distancia_maxima);
    Serial.println(" cm");
    #endif
}