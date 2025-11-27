/**
 * @file ControladorMotores.h
 * @brief Clase para controlar los motores del carrito de sumo
 */

#ifndef CONTROLADOR_MOTORES_H
#define CONTROLADOR_MOTORES_H

#include <Arduino.h>
#include "pines.h"

/**
 * @class ControladorMotores
 * @brief Controla el movimiento de los motores del carrito
 */
class ControladorMotores {
private:
    uint8_t pin_enable_izq;
    uint8_t pin_in1_izq;
    uint8_t pin_in2_izq;
    uint8_t pin_enable_der;
    uint8_t pin_in1_der;
    uint8_t pin_in2_der;
    bool motores_habilitados;

public:
    /**
     * @brief Constructor de la clase ControladorMotores
     */
    ControladorMotores();

    /**
     * @brief Inicializa los pines de los motores
     */
    void inicializar();

    /**
     * @brief Habilita los motores
     */
    void encenderMotores();

    /**
     * @brief Deshabilita los motores
     */
    void apagarMotores();

    /**
     * @brief Hace avanzar el carrito
     * @param velocidad_r Velocidad del motor derecho (0-255)
     * @param velocidad_l Velocidad del motor izquierdo (0-255)
     */
    void avanzar(uint8_t velocidad_r, uint8_t velocidad_l);

    /**
     * @brief Hace retroceder el carrito
     * @param velocidad_r Velocidad del motor derecho (0-255)
     * @param velocidad_l Velocidad del motor izquierdo (0-255)
     */
    void retroceder(uint8_t velocidad_r, uint8_t velocidad_l);

    /**
     * @brief Detiene el carrito
     */
    void detener();

    /**
     * @brief Gira a la izquierda
     * @param velocidad Velocidad de los motores (0-255)
     */
    void girarIzquierda(uint8_t velocidad);

    /**
     * @brief Gira a la derecha
     * @param velocidad Velocidad de los motores (0-255)
     */
    void girarDerecha(uint8_t velocidad);

};

#endif