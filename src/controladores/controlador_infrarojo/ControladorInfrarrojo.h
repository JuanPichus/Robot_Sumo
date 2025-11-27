/**
 * @file ControladorInfrarrojo.h
 * @brief Clase para controlar los sensores infrarrojos de proximidad
 */

#ifndef CONTROLADOR_INFRARROJO_H
#define CONTROLADOR_INFRARROJO_H

#include <Arduino.h>
#include "pines.h"

/**
 * @class ControladorInfrarrojo
 * @brief Controla los sensores infrarrojos del carrito
 */
class ControladorInfrarrojo {
private:
    uint8_t pin_sensor;
    float distancia_maxima_deteccion; // en cm
    String nombre_sensor;

public:
    /**
     * @brief Constructor de la clase ControladorInfrarrojo
     * @param pin Pin del sensor infrarrojo
     * @param nombre Nombre identificador del sensor
     */
    ControladorInfrarrojo(uint8_t pin, const String& nombre);

    /**
     * @brief Inicializa el sensor infrarrojo
     */
    void inicializar();

    /**
     * @brief Detecta si hay un objeto dentro del rango
     * @return true si detecta un objeto, false en caso contrario
     */
    bool detectarObjeto();

    /**
     * @brief Establece la distancia maxima de deteccion
     * @param distancia_maxima Distancia maxima en centimetros
     */
    void establecerDistanciaMaxima(float distancia_maxima);

    /**
     * @brief Obtiene el estado raw del sensor
     * @return true si detecta objeto (LOW activo), false en caso contrario
     */
    bool obtenerEstadoRaw();
};

#endif