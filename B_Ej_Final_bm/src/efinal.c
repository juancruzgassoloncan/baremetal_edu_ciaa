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
 *	GLJC		Gassó Loncan, Juan Cruz
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "efinal.h"       /* <= own header */
#include "tecla.h"
#include "led.h"
#include "adc.h"
#include "dac.h"
#include "usart.h"
#include "timer.h"
#include "chip.h"
/*==================[macros and definitions]=================================*/
#define T_10HZ  100
#define T_100HZ  10
#define T_1KHZ   1
#define ADC_0  0
#define	BAUD_115200  115200
#define MAX_AMP  1023

#define MOD_1  1
#define MOD_2  2
#define MOD_3  3
#define MOD_4  4
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint16_t amp = 0;
uint16_t step = 0;
uint8_t flagISR = FALSE;
uint16_t valor_ad = 0;
uint8_t modo = MOD_4;

char cadena_1[] = " Aumento la ganancia\n\r";
char cadena_2[] = " Disminuyo la ganancia\n\r";
char cadena_3[] = " MUTE\n\r";
char cadena_4[] = " ...\n\r";
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void myISR(){
	if (readFlagTimerRIT() == TRUE){
		flagISR = TRUE;

		ADC_StartConvertion_UP();
		while(ADC_CheckStatus(ADC_CH1,ADC_DR_DONE_STAT) != SET){}
		ADC_ReadValue(ADC_CH1,&valor_ad);
		toggleLed(LED_1);

		switch (modo) {
			case MOD_1:
				amp = valor_ad * 2;
				if (amp > MAX_AMP){
					amp = MAX_AMP;
				}
				break;
			case MOD_2:
				amp = valor_ad / 2;
				break;
			case MOD_3:
				amp = 0;
				break;
			case MOD_4:
				amp = valor_ad;
				break;
			default:
				amp = valor_ad;
				break;
		}

		updateDACbuffer(amp);


		clearFlagTimerRIT();
	}
}

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
	initADC(ADC_0,ADC_CH1);
	initDAC();
	initTeclas();
	initTimerRIT();
	initUSART_USB(BAUD_115200);

	setPeriodTimerRIT(T_1KHZ);
	interup_on();
	enableTimerRIT();

			while (1){
				if (scanTeclas_EDUCIAA() == TRUE){
					if (leeTecla(TEC_1,FALSE,TRUE) == TRUE ){

						UARTUSB_sendString(cadena_1);
						modo = MOD_1;

					}
					if (leeTecla(TEC_2,FALSE,TRUE) == TRUE ){

						UARTUSB_sendString(cadena_2);
						modo = MOD_2;
					}
					if (leeTecla(TEC_3,FALSE,TRUE) == TRUE ){

						UARTUSB_sendString(cadena_3);
						modo = MOD_3;
					}
					if (leeTecla(TEC_4,FALSE,TRUE) == TRUE ){

						UARTUSB_sendString(cadena_4);
						modo = MOD_4;
					}
				}

			}
			return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
