/**
 * @file ControladorGiroscopio.cpp
 * @brief Implementacion de la clase ControladorGiroscopio
 */

#include "ControladorGiroscopio.h"

//Definir MODO_DEBUG para ctivar mensajes seriales
#define MODO_DEBUG

ControladorGiroscopio::ControladorGiroscopio(Adafruit_MPU6050 mpu) {
    this->mpu = mpu;
}

void ControladorGiroscopio::inicializar() {
    if (!mpu.begin()) {
        #ifdef MODO_DEBUG
        Serial.println("🛑 Giroscopio no encontrado");
        #endif
        while(1) {
            delay(10);
        }
    }
    #ifdef MODO_DEBUG
    Serial.println("✅ Giroscopio encontrado");
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
    float anguloXZ = atan2(a.acceleration.z, a.acceleration.x) * 180 / PI;
    float anguloYZ = atan2(a.acceleration.z, a.acceleration.y) * 180 / PI;

    #ifdef MODO_DEBUG
    Serial.print("📐 Angulo XY: "); Serial.print(anguloXY); Serial.println(" grados");
    Serial.print("📐 Angulo XZ: "); Serial.print(anguloXZ); Serial.println(" grados");
    Serial.print("📐 Angulo YZ: "); Serial.print(anguloYZ); Serial.println(" grados");
    #endif

    if (abs(anguloXY) < gradosXY) {
        return true;
    } else {
        return false;
    }
}

