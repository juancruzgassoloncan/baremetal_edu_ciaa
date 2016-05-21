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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "control_leds.h"       /* <= own header */
#include "led.h"
#include "tecla.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/
#define DELAY 1000000
#define CANT_LEDS 4
/*==================[internal data declaration]==============================*/
uint8_t Leds[CANT_LEDS] = {WHITE,LED_1,LED_2,LED_3};
static uint8_t *num_led;
/*==================[internal functions declaration]=========================*/
void delay(uint32_t cuentas);
void parpadea(uint8_t *Led,uint32_t pause);
void aumentaIndice();
void descuentaIndice();
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void delay(uint32_t cuentas)
	{
	uint32_t i;
		for (i=cuentas;i!=0;i--)
		{
			asm("nop");
		};
	};
void parpadea(uint8_t *num_led,uint32_t pause)
	{
		delay(pause);
		toggleLed(*num_led);
	};
void aumentaIndice()
	{
		if (num_led == &Leds[CANT_LEDS-1]){num_led = Leds;}
		else{num_led++;}
	};
void descuentaIndice()
	{
		if (num_led == Leds){num_led = &Leds[CANT_LEDS-1];}
		else{
			num_led--;
			}
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



int main(void)
{
   /* perform the needed initialization here */
	initLeds();
	initTeclas();
	num_led = Leds+2;
	while (1)
		{

			if (scanTeclas_EDUCIAA() == TRUE)
				{//apagarLeds();
					if (leeTecla(TEC_1,TRUE,FALSE) == TRUE)
						{
							descuentaIndice();
							//num_led--;
						}
					if (leeTecla(TEC_4,TRUE,FALSE) == TRUE)
						{
							aumentaIndice(num_led);
							//num_led++;
						}
					apagarLeds();
					parpadea(num_led,DELAY);
					delay(2*DELAY);
				}
			else
				{
//					asm("nop");
				parpadea(num_led,DELAY);
//				num_led++;
				}
		}
	return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
