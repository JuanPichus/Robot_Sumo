/**
 * @file ControladorInfrarrojo.cpp
 * @brief Implementacion de la clase ControladorInfrarrojo
 */

#include "ControladorInfrarrojo.h"

// Definir MODO_DEBUG para activar mensajes seriales
#define MODO_DEBUG

ControladorInfrarrojo::ControladorInfrarrojo(uint8_t pin, const String& nombre)
    : pin_sensor(pin),
      distancia_maxima_deteccion(15.0),
      nombre_sensor(nombre) {
}

void ControladorInfrarrojo::inicializar() {
    pinMode(pin_sensor, INPUT_PULLUP);

    #ifdef MODO_DEBUG
    Serial.print("✅ Sensor IR ");
    Serial.print(nombre_sensor);
    Serial.println(" inicializado");
    #endif

    #ifdef MODO_BT
    BT.print("✅ Sensor IR ");
    BT.print(nombre_sensor);
    BT.println(" inicializado");
    #endif
}

bool ControladorInfrarrojo::detectarObjeto() {
    bool objeto_detectado = obtenerEstadoRaw();

    #ifdef MODO_DEBUG
    if (objeto_detectado) {
        Serial.print("📡");
        Serial.print(nombre_sensor);
        Serial.println(": Objeto detectado");
    }
    #endif

    #ifdef MODO_BT
    if (objeto_detectado) {
        BT.print("📡");
        BT.print(nombre_sensor);
        BT.println(": Objeto detectado");
    }
    #endif

    return objeto_detectado;
}

void ControladorInfrarrojo::establecerDistanciaMaxima(float distancia_maxima) {
    distancia_maxima_deteccion = distancia_maxima;

    #ifdef MODO_DEBUG
    Serial.print("📏");
    Serial.print(nombre_sensor);
    Serial.print(": Distancia maxima establecida a ");
    Serial.print(distancia_maxima);
    Serial.println(" cm");
    #endif
}

bool ControladorInfrarrojo::obtenerEstadoRaw() {
    // Los sensores IR normalmente son activos en LOW
    return digitalRead(pin_sensor) == LOW;
}