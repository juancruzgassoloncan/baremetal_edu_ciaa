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

#ifndef TECLA_H
#define TECLA_H
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

#define UM_PORT1	 1

/*Definición de los GPIO usados para las TECLAS*/
#define GPIO0	 0
#define GPIO1	 1

/*Definiciones de las mascaras para los pines del LED_RGB*/
#define PIN_TEC_1_MASK (1<<4)
#define PIN_TEC_2_MASK (1<<8)
#define PIN_TEC_3_MASK (1<<9)
#define PIN_TEC_4_MASK (1<<9)

/*Definición de los pines de los TECLAs*/
#define PIN_TEC_1 	4
#define PIN_TEC_2 	8
#define PIN_TEC_3 	9
#define PIN_TEC_4 	9

/*Definiciones para la configuración del uso de los puertos GPIO*/
#define ENTRADA 	0
#define SALIDA 		1

/*Definición de las teclas de la EDU_CIAA*/
#define TEC_1	1
#define TEC_2	2
#define TEC_3	3
#define TEC_4	4

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void initTeclas(void);

uint8_t leeTecla(uint8_t tecla, uint8_t Antirrebote, uint8_t Liberacion);

uint8_t scanTeclas_EDUCIAA(void);



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef TECLA_H */
