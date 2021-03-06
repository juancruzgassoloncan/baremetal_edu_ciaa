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
#include "../../7_DienteSierraTeclado_bm/inc/sierraTeclado.h"       /* <= own header */
#include "dac.h"
#include "tecla.h"
#include "led.h"
#include "timer.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/
#define AMP_MAX  3000
#define AMP_MIN  1000
#define T_MAX	100000 /*1s*/
#define T_MIN	3000	/*10us*/
#define PASO_A	50
#define PASO_T	100
#define DELAY	300000
/*==================[internal data declaration]==============================*/
uint8_t flagISR = FALSE;
uint32_t step = 0;
uint32_t periodoIT = 0;
uint32_t periodo_10us = T_MAX/2;
uint16_t amplitud = AMP_MAX/2;
uint32_t cuentas;

/*==================[internal functions declaration]=========================*/

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
uint32_t setSampleCount(uint16_t Vp){
	return (Vp * DAC_RESOLUTION)/V_MAX;
}

uint32_t setPeriodInterrup(uint32_t periodo_10us, uint16_t VP){
	uint32_t cSample = setSampleCount(VP);
	uint32_t periodoInterrup;
	periodoInterrup = periodo_10us/cSample;
	if (periodoInterrup == 0){
		return 1;
	}
	else
	return periodoInterrup;
}

void myISR(){
	if (readFlagTimerRIT() == TRUE){
			flagISR = TRUE;
			step++;
			if (step == cuentas){
					step = 0;
			}
			updateDACbuffer(step);
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
	initDAC();
	initLeds();
	initTeclas();
	initTimerRIT();
	cuentas = setSampleCount(amplitud);
	periodoIT = setPeriodInterrup(periodo_10us,amplitud);
	setPeriodTimerRIT_100k(periodoIT);
	interup_on();
	enableTimerRIT();

			while (1){
				if (scanTeclas_EDUCIAA() == TRUE){
					disableTimerRIT();
					if (leeTecla(TEC_1,FALSE,TRUE) == TRUE ){
						if (amplitud < AMP_MAX){
							prendeLed(LED_3);
							amplitud+=50;
						}else{
							prendeLed(LED_2);
							amplitud = AMP_MAX;
						}

					}
					if (leeTecla(TEC_2,FALSE,TRUE) == TRUE ){
						if (amplitud > AMP_MIN){
							prendeLed(LED_3);
							amplitud-=50;
						}else{
							prendeLed(LED_2);
							amplitud = AMP_MIN;
						}
					}
					if (leeTecla(TEC_3,FALSE,TRUE) == TRUE ){
						if (periodo_10us < T_MAX){
							prendeLed(LED_3);
							periodo_10us+=500;
						}else{
							prendeLed(LED_2);
							periodo_10us = T_MAX;
						}

					}
					if (leeTecla(TEC_4,FALSE,TRUE) == TRUE ){
						if (periodo_10us > T_MIN){
							prendeLed(LED_3);
							periodo_10us-=500;
						}else{
							prendeLed(LED_2);
							periodo_10us = T_MIN;
						}

					}
					cuentas = setSampleCount(amplitud);
					periodoIT = setPeriodInterrup(periodo_10us,amplitud);
					setPeriodTimerRIT_100k(periodoIT);
					enableTimerRIT();
					delay(DELAY);
					apagarLeds();
				}
			}
			return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
