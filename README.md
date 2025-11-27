Este proyecto tiene el sistema de control para un carro robot automo para sumo.

Incluye clases de controladores para los perifericos (control de motor a DC por puente H, sensor de proximidad infrarojo, sensor ultrasonico hc-sr04, sensor de velocidad y movimiento mpu6050 y modulo bluetooth hc-05).

Incluye una archivo de cabecera "pines.h" para definir los pines de los perifericos que se usan tendro del codigo.

Cuenta con tres modos:

-   Modo Depuracion (debug) para mostrar informacion por el monitor serial.
-   Modo Bluetooth (BT) para mandar y mostrar informacion via Bluetooth
-   Modo Giroscopio (MPU) para activar el modulo MPU y controlarlo
