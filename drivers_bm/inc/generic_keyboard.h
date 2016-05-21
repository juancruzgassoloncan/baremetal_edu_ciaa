/* Copyright 2016, Gassó Loncan, Juan Cruz
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GENERIC_KEYBOARD_H
#define GENERIC_KEYBOARD_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	GLJC        Gassó Loncan, Juan Cruz
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2


/*Declaración de Puertos*/
 #define PORT_1      1
 #define PORT_4 	 4
 #define PORT_7      7

 #define PIN_0      0
 #define PIN_1      1
 #define PIN_2      2
 #define PIN_3      3
 #define PIN_4      4
 #define PIN_5      5
 #define PIN_6      6
/*...*/

/*Declaración de GPIO*/
 #define GPIO1      1
 #define GPIO2 		2
 #define GPIO3      3


/*Ir agregando*/

/*Declaración de los Puertos que confromaran las columnas del teclado matricial*/
// #define T_COL_0
// #define T_COL_1
// #define T_COL_2
/*Ir agregando*/

/*Dimenciones de teclados */
#define N_FILAS			4
#define N_COLUMNAS		3
/*==================[typedef]================================================*/
typedef struct{
    uint8_t port;
    uint8_t port_pin;
    uint8_t gpio;
    uint8_t gpio_pin;
}Tecla_Mx;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void initGenericKeyboard(uint8_t external_keyboard);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef TEMPLATE_H */
