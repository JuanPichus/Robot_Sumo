/**
 * @file ControladorGiroscopio.cpp
 * @brief Implementacion de la clase ControladorGiroscopio
 */

#include "ControladorGiroscopio.h"
#include "Bluetooth.h"

//Definir MODO_DEBUG para activar mensajes seriales
// #define MODO_DEBUG //*

//Definir MODO_BT para activar mensajes bluetooth
// #define MODO_BT //*

ControladorGiroscopio::ControladorGiroscopio(Adafruit_MPU6050 mpu) {
    this->mpu = mpu;
}

void ControladorGiroscopio::inicializar() {
    if (!mpu.begin()) {
        #ifdef MODO_DEBUG
        Serial.println(F("[ERR] MPU no encontrado"));
        #endif
        while(1) {
            delay(10);
        }
    }
    #ifdef MODO_DEBUG
    Serial.println(F("[OK] MPU inicializado"));
    #endif

    //inicializar deteccion de movimiento
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

bool ControladorGiroscopio::estaInclinado(float gradosXY) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    //Calcular la magnitud de la aceleracion en el plano XY
    float anguloXY = atan2(a.acceleration.y, a.acceleration.x) * 180 / PI;
    // float anguloXZ = atan2(a.acceleration.z, a.acceleration.x) * 180 / PI;
    // float anguloYZ = atan2(a.acceleration.z, a.acceleration.y) * 180 / PI;

    #ifdef MODO_DEBUG
    Serial.print(F("[MPU] XY: ")); Serial.print(anguloXY); Serial.println(F(" grados"));
    // Serial.print(F("[MPU] XZ: ")); Serial.print(anguloXZ); Serial.println(F(" grados"));
    // Serial.print(F("[MPU] YZ: ")); Serial.print(anguloYZ); Serial.println(F(" grados"));
    #endif

    return (abs(anguloXY) < gradosXY);
}

