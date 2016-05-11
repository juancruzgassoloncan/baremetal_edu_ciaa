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
#include "timer.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

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
 /*Inicialización del timer de interrupciones repetidas*/
 void initTimerRIT(void)
    {
 	Chip_RIT_Init(LPC_RITIMER);
 	NVIC_ClearPendingIRQ(RITIMER_IRQn);
 	Chip_RIT_Disable(LPC_RITIMER);
    };

 void interup_on(){
	 NVIC_EnableIRQ(RITIMER_IRQn);
 }

 /*Seteo de periodo de interrupción en mili segundos*/
 void setPeriodTimerRIT(uint32_t periodo)
    {
    Chip_RIT_SetTimerInterval(LPC_RITIMER,periodo);
    }

 /*Habilitación de la interrupciones del Timer RIT*/
 void enableTimerRIT(void){
//	 NVIC_EnableIRQ(RITIMER_IRQn);
   Chip_RIT_Enable(LPC_RITIMER);
 };

 /*Limpieza del flag de interrupciones*/
 void clearFlagTimerRIT(void){
     Chip_RIT_ClearInt(LPC_RITIMER);
 };

uint8_t readFlagTimerRIT(void){
	return Chip_RIT_GetIntStatus(LPC_RITIMER);
}

void disableTimerRIT(void){
	Chip_RIT_Disable(LPC_RITIMER);
}

void DinitTimerRIT(void){
	Chip_RIT_DeInit(LPC_RITIMER);
}

void interup_off(void){
	NVIC_DisableIRQ(RITIMER_IRQn);
}

void setPeriodTimerRIT_100k(uint32_t time_interval)
{
	uint32_t cmp_value;

	/* Determine aapproximate compare value based on clock rate and passed interval */
	cmp_value = (Chip_Clock_GetRate(CLK_MX_RITIMER) / 100000) * time_interval;

	/* Set timer compare value */
	Chip_RIT_SetCOMPVAL(LPC_RITIMER, cmp_value);

	/* Set timer enable clear bit to clear timer to 0 whenever
	   counter value equals the contents of RICOMPVAL */
	Chip_RIT_EnableCTRL(LPC_RITIMER, RIT_CTRL_ENCLR);
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
