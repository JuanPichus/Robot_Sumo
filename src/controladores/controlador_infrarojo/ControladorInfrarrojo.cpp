/**
 * @file ControladorInfrarrojo.cpp
 * @brief Implementacion de la clase ControladorInfrarrojo
 */

#include "ControladorInfrarrojo.h"
#include "Bluetooth.h"

// Definir MODO_DEBUG para activar mensajes seriales
// #define MODO_DEBUG //*

//Definir MODO_BT para activar mensajes bluetooth
// #define MODO_BT //*

ControladorInfrarrojo::ControladorInfrarrojo(uint8_t pin, const char* nombre)
    : pin_sensor(pin),
      distancia_maxima_deteccion(15.0),
      nombre_sensor(nombre) {
}

void ControladorInfrarrojo::inicializar() {
    pinMode(pin_sensor, INPUT_PULLUP);

    #ifdef MODO_DEBUG
    Serial.print(F("[OK] Sensor IR "));
    Serial.print(nombre_sensor);
    Serial.println(F(" inicializado"));
    #endif
}

bool ControladorInfrarrojo::detectarObjeto() {
    bool objeto_detectado = obtenerEstadoRaw();

    #ifdef MODO_DEBUG
    if (objeto_detectado) {
        Serial.print(F("[IR] "));
        Serial.print(nombre_sensor);
        Serial.println(F(": Objeto detectado"));
    }
    #endif

    #ifdef MODO_BT
    if (objeto_detectado) {
        BT.print(F("[IR] "));
        BT.print(nombre_sensor);
        BT.println(F(": Objeto detectado"));
    }
    #endif

    return objeto_detectado;
}

void ControladorInfrarrojo::establecerDistanciaMaxima(float distancia_maxima) {
    distancia_maxima_deteccion = distancia_maxima;

    #ifdef MODO_DEBUG
    Serial.print(F("[IR] "));
    Serial.print(nombre_sensor);
    Serial.print(F(": Dist max = "));
    Serial.print(distancia_maxima);
    Serial.println(F(" cm"));
    #endif
}

bool ControladorInfrarrojo::obtenerEstadoRaw() {
    // Los sensores IR normalmente son activos en LOW
    return digitalRead(pin_sensor) == LOW;
}