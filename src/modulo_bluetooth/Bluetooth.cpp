/**
 * @file Bluetooth.cpp
 * @brief Implementación del módulo global de Bluetooth
 */

#include "Bluetooth.h"

// Definir MODO_DEBUG para activar mensajes seriales
//  #define MODO_DEBUG //*

// Instancia global del módulo Bluetooths
SoftwareSerial BT(PIN_RX_BT, PIN_TX_BT);

void BT_inicializar(unsigned long baudRate) {
    BT.begin(baudRate);
    #ifdef MODO_DEBUG
    Serial.println("[OK] Bluetooth inicializado");
    #endif
}

// === Funciones print (sin salto de línea) ===

void BT_print(const char* mensaje) {

    BT.print(mensaje);
}

void BT_print(const String& mensaje) {

    BT.print(mensaje);
}

void BT_print(int valor) {

    BT.print(valor);
}

void BT_print(float valor) {

    BT.print(valor);
}

// === Funciones println (con salto de línea) ===

void BT_println(const char* mensaje) {

    BT.println(mensaje);
}

void BT_println(const String& mensaje) {

    BT.println(mensaje);
}

void BT_println(int valor) {

    BT.println(valor);
}

void BT_println(float valor) {

    BT.println(valor);
}

void BT_println() {

    BT.println();
}
