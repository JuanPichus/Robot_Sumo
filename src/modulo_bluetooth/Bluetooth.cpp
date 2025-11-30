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
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.print(mensaje);
}

void BT_print(const String& mensaje) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.print(mensaje);
}

void BT_print(int valor) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.print(valor);
}

void BT_print(float valor) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.print(valor);
}

// === Funciones println (con salto de línea) ===

void BT_println(const char* mensaje) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.println(mensaje);
}

void BT_println(const String& mensaje) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.println(mensaje);
}

void BT_println(int valor) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.println(valor);
}

void BT_println(float valor) {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.println(valor);
}

void BT_println() {
    if (BT.availableForWrite() == 0) {
        // Esperar hasta que el buffer esté listo para escribir
        while (BT.availableForWrite() == 0);
    }
    BT.println();
}
