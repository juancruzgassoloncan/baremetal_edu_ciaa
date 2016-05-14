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

/** \brief Blinking Bare Metal driver name
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal TECLA Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *  GLJC        Gassó Loncan, Juan Cruz
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160428 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#include "chip.h" /*LPCopen*/
#include "generic_keyboard.h"
#include "timer.h"

/*==================[macros and definitions]=================================*/

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
/*==================[internal data declaration]==============================*/

Tecla_Mx filas[4]={
	{PORT_4,PIN_0,GPIO2,PIN_0},
	{PORT_4,PIN_1,GPIO2,PIN_1},
	{PORT_4,PIN_2,GPIO2,PIN_2},
	{PORT_4,PIN_3,GPIO2,PIN_3}
};

Tecla_Mx columnas[3]={
    {PORT_4,PIN_5,GPIO1,PIN_0},
    {PORT_1,PIN_4,GPIO3,PIN_0},
    {PORT_7,PIN_5,GPIO3,PIN_0},
};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
//filas[0]= {1,2,3,4};
//    port_pin = 0,
//    gpio = 2,
//    gpio_pin = 0;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
