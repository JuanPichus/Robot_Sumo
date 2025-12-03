/**
 * @file ControladorServo.cpp
 * @brief Implementacion de la clase ControladorServo
 */

#include "ControladorServo.h"

//Definir MODO_DEBUG para activar mensajes seriales
// #define MODO_DEBUG //*

ControladorServo::ControladorServo(uint8_t pin, Servo servo, const char* nombre = "Servo") {
    this->servo_motor = servo;
    this->pin_servo = pin;
    this->nombre_servo = nombre;
}

void ControladorServo::inicializar() {

    servo_motor.attach(pin_servo);

    #ifdef MODO_DEBUG
    Serial.print(F("[OK] Servo "));
    Serial.print(nombre_servo);
    Serial.println(F(" inicializado"));
    #endif
}

void ControladorServo::moverA(int angulo) {
    servo_motor.write(angulo);
    delay(500);
    


    #ifdef MODO_DEBUG
    Serial.print(F("[SERVO] Moviendo "));
    Serial.print(nombre_servo);
    Serial.print(F(" a "));
    Serial.print(angulo);
    Serial.println(F(" grados"));
    #endif
}

void ControladorServo::atacar() {
    // Mover a 90 grados (posicion de ataque)
    moverA(180);


    // Regresar a 0 grados (posicion inicial)
    moverA(0);

    #ifdef MODO_DEBUG
    Serial.print(F("[SERVO] "));
    Serial.print(nombre_servo);
    Serial.println(F(" ataque realizado"));
    #endif
}