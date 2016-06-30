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
#include "../inc/ad2huart.h"       /* <= own header */
#include "led.h"
#include "timer.h"
#include "adc.h"
#include "chip.h"
#include "usart.h"


/*==================[macros and definitions]=================================*/
#define MIN_VALUE  50
#define MAX_VALUE  900
/*==================[internal data declaration]==============================*/
uint8_t flagISR = FALSE;
uint16_t dato_ad = 0;
uint32_t periodo = 1000;
uint32_t baud = 115200;
uint8_t largo;
char string[5];
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void clearString(char *string){
	int largo = 0;
	while (string[largo]!='\0'){
		string[largo] = '\0';
		largo++;
	}
}

void int2char(uint16_t numero,char* cadena){
	uint8_t digito = 0;
	uint8_t cont = 0;
	char caracter;

	while (numero >= 1){
		digito = numero % 10;
		cadena[cont] = digito + '0';
		numero -= digito;
		numero /= 10;
		cont++;
	}

	int i = 0;
	int top = cont;
	char temp;

	for (i = 0; i < top / 2; ++i) {
		temp = cadena[i];
		cadena[i] = cadena[top - i - 1];
		cadena[top - i - 1] = temp;
	}

}


void myISR(){
	if (readFlagTimerRIT() == TRUE){
			flagISR = TRUE;
//			string[5] = "     ";
			int2char(dato_ad,string);
			UARTUSB_sendString(string);
			clearString(string);
			UARTUSB_Tx_sendByte(' ');

			clearFlagTimerRIT();
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



int main(void)
{
   /* perform the needed initialization here */
	initLeds();
	initUSART_USB(115200);
	initTimerRIT();
	initADC(0,1);
	setPeriodTimerRIT(periodo);
	interup_on();
	enableTimerRIT();

	while (1){

		ADC_StartConvertion_UP();
		while(ADC_CheckStatus(ADC_CH1,ADC_DR_DONE_STAT) != SET){}
		ADC_ReadValue(ADC_CH1,&dato_ad);
		if (flagISR == TRUE){
			if (dato_ad <= MIN_VALUE){
				apagarLeds();
				prendeLed(LED_3); //LED Verde
			}else{
				if (dato_ad >= MAX_VALUE){
					apagarLeds();
					prendeLed(LED_2);// LED Rojo
					}else{
						apagarLeds();
						prendeLed(LED_1);// LED Amarrillo
						}
				}

//			int2char(dato_ad,string);
//			UARTUSB_sendString(string);
//			UARTUSB_Tx_sendByte(' ');
			flagISR = FALSE;
			}

	}
	return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
