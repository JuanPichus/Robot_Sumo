/**
 * @file ControladorServo.h
 * @brief Clase para controlar un servo motor
 */
#ifndef CONTROLADOR_SERVO_H
#define CONTROLADOR_SERVO_H

#include <Arduino.h>
#include <Servo.h>
#include "pines.h"

/**
 * @class ControladorServo
 * @brief Controla un servo motor
 */
class ControladorServo {
private:
    Servo servo_motor;
    uint8_t pin_servo;
    const char* nombre_servo;

public:
    /**
     * @brief Constructor de la clase ControladorServo
     * @param pin Pin al que esta conectado el servo
     */
    ControladorServo(uint8_t pin, Servo servo, const char* nombre);

    /**
     * @brief Inicializa el servo motor
     */
    void inicializar() ;

    /**
     * @brief Mueve el servo a un angulo especifico
     * @param angulo Angulo al que mover el servo (0-180 grados)
     */
    void moverA(int angulo);

    /**
     * @brief Realiza la accion de atacar con el servo
     */
    void atacar();

};

#endif