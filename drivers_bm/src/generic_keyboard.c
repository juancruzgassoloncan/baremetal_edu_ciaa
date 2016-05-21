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
#include "tecla.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

Tecla_Mx filas[N_FILAS]={
	{PORT_4,PIN_0,GPIO2,PIN_0},
	{PORT_4,PIN_1,GPIO2,PIN_1},
	{PORT_4,PIN_2,GPIO2,PIN_2},
	{PORT_4,PIN_3,GPIO2,PIN_3}
};

Tecla_Mx columnas[N_COLUMNAS]={
    {PORT_4,PIN_5,GPIO1,PIN_0},
    {PORT_1,PIN_4,GPIO3,PIN_0},
    {PORT_7,PIN_5,GPIO3,PIN_0},
};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void initGenericKeyboard(uint8_t external_keyboard){
	if (external_keyboard != TRUE){
		initTeclas();
	}
	else{
		uint8_t n_filas;
		uint8_t n_columnas;
		Chip_GPIO_Init(LPC_GPIO_PORT);
		for ( n_filas = N_FILAS ; n_filas = 0; n_filas--) {
			Chip_SCU_PinMux(filas[n_filas].port,filas[n_filas].port_pin,MD_PUP|MD_EZI,FUNC0);
			Chip_GPIO_SetDir(LPC_GPIO_PORT,filas[n_filas].gpio,1<<(filas[n_filas].gpio_pin),ENTRADA);
		}
		for ( n_columnas = N_COLUMNAS; n_columnas = 0 ; n_columnas--){
			Chip_SCU_PinMux(columnas[n_columnas].port,columnas[n_columnas].port_pin,MD_PLN,FUNC0);
			Chip_GPIO_SetDir(LPC_GPIO_PORT,columnas[n_columnas].gpio,(1<<columnas[n_columnas].gpio_pin),SALIDA);
			Chip_GPIO_ClearValue(LPC_GPIO_PORT,columnas[n_columnas].gpio,(1<<columnas[n_columnas].gpio_pin));
			}
		}
	}
}

// uint8_t rotaFilas(){
//
// 	Chip_GPIO_SetValue(LPC_GPIO_PORT, fila[n_filas].gpio,(1<<fila[n_filas].gpio_pin));
// };
void scanTeclas_GenericKeyboard(){

	Chip_GPIO_ReadValue();;
	}

}


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
