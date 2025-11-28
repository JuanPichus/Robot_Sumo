/**
 * @file Bluetooth.h
 * @brief Módulo global de Bluetooth para comunicación inalámbrica
 * 
 * Este módulo proporciona funciones globales para enviar mensajes
 * por Bluetooth. Solo envía mensajes si MODO_BT está definido.
 * 
 * Uso en cualquier archivo:
 *   #include "Bluetooth.h"
 *   BT_println("Mensaje de prueba");
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "pines.h"

// Declaración externa del objeto Bluetooth (definido en Bluetooth.cpp)
extern SoftwareSerial BT;

/**
 * @brief Inicializa el módulo Bluetooth
 * @param baudRate Velocidad de comunicación (default: 9600)
 */
void BT_inicializar(unsigned long baudRate = 9600);

/**
 * @brief Envía un mensaje por Bluetooth (sin salto de línea)
 * @param mensaje Mensaje a enviar
 */
void BT_print(const char* mensaje);
void BT_print(const String& mensaje);
void BT_print(int valor);
void BT_print(float valor);

/**
 * @brief Envía un mensaje por Bluetooth (con salto de línea)
 * @param mensaje Mensaje a enviar
 */
void BT_println(const char* mensaje);
void BT_println(const String& mensaje);
void BT_println(int valor);
void BT_println(float valor);
void BT_println(); // Solo salto de línea

#endif
