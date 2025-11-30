/**
 * @file ControladorUltrasonico.h
 * @brief Clase para controlar los sensores ultrasonicos HC-SR04
 */

#ifndef CONTROLADOR_ULTRASONICO_H
#define CONTROLADOR_ULTRASONICO_H

#include <Arduino.h>
#include "pines.h"

/**
 * @class ControladorUltrasonico
 * @brief Controla los sensores ultrasonicos del carrito
 */
class ControladorUltrasonico {
private:
    uint8_t pin_trigger;
    uint8_t pin_echo;
    float distancia_maxima_deteccion; // en cm
    const char* nombre_sensor;

    /**
     * @brief Realiza la medicion de distancia
     * @return Distancia medida en centimetros
     */
    float medirDistancia();

public:
    /**
     * @brief Constructor de la clase ControladorUltrasonico
     * @param pin_tr Pin del trigger
     * @param pin_ech Pin del echo
     * @param nombre Nombre identificador del sensor
     */
    ControladorUltrasonico(uint8_t pin_tr, uint8_t pin_ech, const char* nombre);

    /**
     * @brief Inicializa el sensor ultrasonico
     */
    void inicializar();

    /**
     * @brief Detecta si hay un objeto dentro del rango
     * @return true si detecta un objeto, false en caso contrario
     */
    bool detectarObjeto();

    /**
     * @brief Obtiene la distancia medida
     * @return Distancia en centimetros
     */
    float obtenerDistancia();

    /**
     * @brief Establece la distancia maxima de deteccion
     * @param distancia_maxima Distancia maxima en centimetros
     */
    void establecerDistanciaMaxima(float distancia_maxima);
};

#endif