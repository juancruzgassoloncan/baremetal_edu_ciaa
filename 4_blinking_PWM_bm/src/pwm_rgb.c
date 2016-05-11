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
#include "pwm_rgb.h"
#include "led.h"
#include "stdlib.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
Color RGB,*pRGB;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
uint8_t pwmRGB_counter(void){
	static uint8_t counter;

	if(counter < 255)
		{
		if(pRGB->R != 0){
			prendeLed_RGB(RED);
			pRGB->R--;
		}
		else{
			apagaLed_RGB(RED);
		}
		if(pRGB->G != 0){
			prendeLed_RGB(GREEN);
			pRGB->G--;
				}
		else{
			apagaLed_RGB(GREEN);
			}
		if(pRGB->B != 0){
			prendeLed_RGB(BLUE);
			pRGB->B--;
				}
		else{
			apagaLed_RGB(BLUE);
		}
		counter++;
		}
	else{
		counter=0;

		return TRUE;
	}

	return FALSE;
};

void setColorPWM(Color *color_rgb){
	RGB=*color_rgb;
	pRGB=&RGB;
}

Color randColorRGB(void){
	Color rand_color;
	rand_color.R=(uint8_t)rand();
	rand_color.B=(uint8_t)rand();
	rand_color.G=(uint8_t)rand();
	return rand_color;
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
