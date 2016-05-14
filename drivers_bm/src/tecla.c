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

/** \brief Blinking Bare Metal driver tecla
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
#include "tecla.h"

/*==================[macros and definitions]=================================*/
#define UM_PORT1	 1

/*Definición de los GPIO usados para las TECLAS*/
#define GPIO0	 0
#define GPIO1	 1

/*Definiciones de las mascaras para los pines del LED_RGB*/
#define PIN_TEC_1_MASK (4<<0)
#define PIN_TEC_2_MASK (8<<0)
#define PIN_TEC_3_MASK (9<<0)
#define PIN_TEC_4_MASK (9<<0)

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


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void delay_SW(uint32_t cuentas);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void delay_SW(uint32_t cuentas){
	uint32_t i;
	for (i=cuentas;i!=0;i--){
		asm("nop");
	};
};
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

void initTeclas(void){
	Chip_GPIO_Init(LPC_GPIO_PORT);
	/*===Configuración del SCU===*/

	/*===Pulsadores Edu_CIAA===*/

	/* mapea P1 0 en GPIO 0[4], SW1 */
	Chip_SCU_PinMux(UM_PORT1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 1 en GPIO 0[8], SW2 */
	Chip_SCU_PinMux(UM_PORT1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 2 en GPIO 0[9], SW3 */
	Chip_SCU_PinMux(UM_PORT1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 6 en GPIO 1[9], SW4 */
	Chip_SCU_PinMux(UM_PORT1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0);

	/*===Seteo de dirección de los puertos===*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO0,PIN_TEC_1_MASK|PIN_TEC_2_MASK|PIN_TEC_3_MASK,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO1,PIN_TEC_4_MASK,ENTRADA);
};

uint8_t scanTeclas_EDUCIAA(void){
	if ((Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,PIN_TEC_1)&&
		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,PIN_TEC_2)&&
		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,PIN_TEC_3)&&
		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO1,PIN_TEC_4)) == FALSE){return TRUE;
	}
	else{
		return FALSE;
	}
};

uint8_t leeTecla(uint8_t tecla, uint8_t Antirrebote, uint8_t Liberacion)
	{
	uint8_t pin;
	uint8_t gpio;
	switch (tecla)
		{
		case TEC_1:
			pin = PIN_TEC_1;
			gpio = GPIO0;
			break;
		case TEC_2:
			pin = PIN_TEC_2;
			gpio = GPIO0;
			break;
		case TEC_3:
			pin = PIN_TEC_3;
			gpio = GPIO0;
			break;
		case TEC_4:
			pin = PIN_TEC_4;
			gpio = GPIO1;
			break;
		default:
			return FALSE; //TODO: Debería haber una excepción en tiempo de compilación
		}

	if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,gpio,pin) == FALSE )
		{
		if (Antirrebote == TRUE)
			{
			delay_SW(50000);
			if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,gpio,pin) == FALSE)
				{
				if (Liberacion == TRUE)
					{/*Espero se libere la tecla*/
					while (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,gpio,pin) == FALSE)
						{
						asm("nop");
						}
					return TRUE;
					}
				else /*sin esperar que se libere*/
					{
					return TRUE;
					}
				}
			else /*Si falla el control de rebote*/
				{
				return FALSE;
				}
			}
		else
			{/*Sin Antirrebote*/
			if (Liberacion == TRUE)
				{/*Espero se libere la tecla*/
				while (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,gpio,pin) == FALSE)
					{
					asm("nop");
					}
				return TRUE;
				}
			else /*sin esperar que se libere*/
				{
				return TRUE;
				}
			}
		}
	else /*No detecto cambio de estado en la tecla*/
		{
		return FALSE;
		}
	};


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
