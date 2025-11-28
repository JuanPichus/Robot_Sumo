/**
 * @file ControladorInfrarrojo.h
 * @brief Clase para controlar el giroscopio MPU6050
 */

#ifndef CONTROLADOR_GIROSCOPIO_H
#define CONTROLADOR_GIROSCOPIO_H

#include <Arduino.h>
#include <Wire.h> //mpu
#include <Adafruit_MPU6050.h> //mpu
#include <Adafruit_Sensor.h> //mpu
#include "pines.h"

/**
 * @class ControladorGiroscopio
 * @brief Controla el giroscopio MPU6050
 */
class ControladorGiroscopio {
    private: 
        Adafruit_MPU6050 mpu;

    public: 
        /**
         * @brief Constructor de la clase ControladorGiroscopio
         * @param mpu Objeto Adafruit_MPU6050 para el giroscopio
         */
        ControladorGiroscopio(Adafruit_MPU6050 mpu);

        /**
         * @brief Inicializa el giroscopio
         * @return true si la inicializacion fue exitosa, false en caso contrario
         */
        void inicializar();  
        
        /**
         * @brief Verifica si el dispositivo esta inclinado mas alla de un umbral
         * @param grados Umbral de inclinacion en grados
         * @return true si esta inclinado, false en caso contrario
         */
        bool estaInclinado(float grados);
};

#endif