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
#include "adc.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
LPC_ADC_T *ADC_B;
ADC_CLOCK_SETUP_T ADCSetup;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void initADC(uint32_t n_ADC, uint8_t ch_ADC){
    Chip_SCU_ADC_Channel_Config(n_ADC, ch_ADC);
    switch (n_ADC){
    	case 0:
    		ADC_B = LPC_ADC0;
//    		Chip_ADC_Init(LPC_ADC0,ADC_CLOCK_SETUP_T);
    		break;
    	case 1:
    		ADC_B = LPC_ADC1;
//    		Chip_ADC_DeInit(LPC_ADC1,ADC_CLOCK_SETUP_T);
    		break;
    	default:
    		ADC_B = LPC_ADC0;
    }
    Chip_ADC_Init(ADC_B,&ADCSetup);
    Chip_ADC_EnableChannel(ADC_B,ch_ADC,ENABLE);
};

void ADC_StartConvertion_UP(){
	Chip_ADC_SetStartMode(ADC_B, ADC_START_NOW,ADC_TRIGGERMODE_RISING);
}
void ADC_StartConvertion_DW(){
	Chip_ADC_SetStartMode(ADC_B, ADC_START_NOW,ADC_TRIGGERMODE_FALLING);
}

uint8_t ADC_CheckStatus(uint8_t ch_ADC,uint8_t StatusType){
	return Chip_ADC_ReadStatus(ADC_B, ch_ADC, StatusType);
}

uint8_t ADC_ReadValue(uint8_t ch_ADC, uint16_t *value){
	return Chip_ADC_ReadValue(ADC_B,ch_ADC,value);
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



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
