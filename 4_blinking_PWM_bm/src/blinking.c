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
#include "blinking.h"       /* <= own header */
#include "led.h"
#include "timer.h"
#include "chip.h"
#include "tecla.h"
#include "pwm_rgb.h"
#include "stdlib.h"
/*==================[macros and definitions]=================================*/
#define RG_MODE		1
#define PWM_MODE	2
/*==================[internal data declaration]==============================*/
uint8_t mode=1;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint8_t flagISR = FALSE;

Color led_RGB = {0,0,0};
Color *pled_RGB = &led_RGB;

uint8_t r,g,b;
uint16_t contador_interrupciones=0;
uint32_t periodo;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void myISR(){
	if (readFlagTimerRIT() == TRUE){
		flagISR = TRUE;
		clearFlagTimerRIT();
	}
	else{
		asm("nop");
	}
}
void changeMode(void){
	DinitTimerRIT();
	if(mode==RG_MODE){
		contador_interrupciones=0;
		apagarLeds();
		mode=PWM_MODE;
		initTimerRIT();
		setPeriodTimerRIT_100k(1);
	}
	else{
		apagarLeds();
		mode=RG_MODE;
		initTimerRIT();
		setPeriodTimerRIT_100k(25000);

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
		initTeclas();
		initTimerRIT();
		setPeriodTimerRIT(250);
		interup_on();
//		changeMode();

		led_RGB=randColorRGB();
		setColorPWM(pled_RGB);
		enableTimerRIT();
		while (TRUE){

			if (scanTeclas()==TRUE){
				disableTimerRIT();
				if (leeTecla(TEC_1,FALSE,TRUE)==TRUE){
					changeMode();
					}
				enableTimerRIT();
			}

			if (flagISR == TRUE){
				contador_interrupciones++;
				if (mode == PWM_MODE){
					if (pwmRGB_counter()==TRUE){
						setColorPWM(pled_RGB);
					}
					if (contador_interrupciones == 0){
						led_RGB=randColorRGB();
					}
				}

				if(mode == RG_MODE){
					if (contador_interrupciones == 1){
						prendeLed(LED_2);
						apagaLed(GREEN);
					}
					else{
						if(contador_interrupciones == 2){
							prendeLed(GREEN);
							apagaLed(LED_2);
						}
						else{
							contador_interrupciones = 0;
						}
					}
				}
			flagISR = FALSE;
			}

		}
		return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
