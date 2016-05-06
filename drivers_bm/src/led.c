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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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
#include "led.h"


/*==================[macros and definitions]=================================*/

#define UM_PORT2 2
/*Definición de los GPIO usados para los LEDS*/
#define GPIO5 5
#define GPIO0 0
#define GPIO1 1
/*Definiciones de las mascaras para los pines de los LEDS*/
#define PIN_LED_RED_MASK (1<<14)
#define PIN_LED_YELLOW_MASK (1<<11)
#define PIN_LED_GREEN_MASK (1<<12)
/*Definiciones de las mascaras para los pines del LED_RGB*/
#define PIN_LED_RGB_RED_MASK (1<<0)
#define PIN_LED_RGB_GREEN_MASK (1<<1)
#define PIN_LED_RGB_BLUE_MASK (1<<2)
/*Definición de los pines de los LEDs*/
#define PIN_LED_RED 14
#define PIN_LED_YELLOW 11
#define PIN_LED_GREEN 12
/*Definición de los pines del LED_RGB*/
#define PIN_LED_RGB_RED 0
#define PIN_LED_RGB_GREEN 1
#define PIN_LED_RGB_BLUE 2
/*==================[internal data declaration]==============================*/


const led edu_ciaa_led = {{0,14},{1,11},{1,12}};
const led *p_edu_ciaa_led = &edu_ciaa_led;
const ledRGB edu_ciaa_ledRGB ={5,{5,0},{5,1},{5,2}};
const ledRGB *p_edu_ciaa_ledRGB = &edu_ciaa_ledRGB;

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



/* Función  encargada cambiar el estado a bajo(apagado) de todos los leds*/
uint8_t apagarLeds(void)
{
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, GPIO5,PIN_LED_RGB_RED_MASK|PIN_LED_RGB_GREEN_MASK|PIN_LED_RGB_BLUE_MASK);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, GPIO0,PIN_LED_RED_MASK);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, GPIO1,PIN_LED_YELLOW_MASK|PIN_LED_GREEN_MASK);
    	if (
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO5,PIN_LED_RGB_RED)==FALSE &&
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO5,PIN_LED_RGB_GREEN)==FALSE &&
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO5,PIN_LED_RGB_BLUE)==FALSE &&
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO0,PIN_LED_RED)==FALSE &&
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO1,PIN_LED_YELLOW)==FALSE &&
    		Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,GPIO1,PIN_LED_GREEN)==FALSE
    		)/*TODO: Terminar de realizar la verificación*/
    		{return TRUE;}
    	else {return FALSE;}
};

/* Función  encargada cambiar el estado a alto(encendido) de todos los leds*/
void enciendeLeds(void){
    Chip_GPIO_SetValue(LPC_GPIO_PORT, GPIO0,PIN_LED_RED_MASK);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, GPIO5,PIN_LED_RGB_RED_MASK|PIN_LED_RGB_GREEN_MASK|PIN_LED_RGB_BLUE_MASK);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, GPIO1,PIN_LED_YELLOW_MASK|PIN_LED_RGB_GREEN_MASK);
};

/* Función que inicializa los puertos y realiza el mapeo de los puertos y funciones*/
uint8_t initLeds(void){
	Chip_GPIO_Init(LPC_GPIO_PORT);
	/*===Configuración del SCU===*/

	/*___LED RGB___*/
	/* remapea P2_0  en GPIO5[0], LED0R y habilita el pull up*/
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_RGB_RED,MD_PUP,FUNC4);
	/* remapea P2_1  en GPIO5[1], LED0G y habilita el pull up */
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_RGB_GREEN,MD_PUP,FUNC4);
	/* remapea P2_2  en GPIO5[2], LED0B y habilita el pull up */
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_RGB_BLUE,MD_PUP,FUNC4);

	/*___LEDs Individuales___*/
	/* remapea P2_10 en GPIO0[14], LED1 y habilita el pull up */
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_RED,MD_PUP,FUNC0);
	/* remapea P2_11 en GPIO1[11], LED2 y habilita el pull up */
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_YELLOW,MD_PUP,FUNC0);
	/* remapea P2_12 en GPIO1[12], LED3 y habilita el pull up */
	Chip_SCU_PinMux(UM_PORT2,PIN_LED_GREEN,MD_PUP,FUNC0);

	/*===Seteo de dirección de los puertos===*/
	/*Led RGB -> GPIO5[0,1,2]*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT, GPIO5, PIN_LED_RGB_RED_MASK|PIN_LED_RGB_GREEN_MASK|PIN_LED_RGB_BLUE_MASK,SALIDA);
	/*Led LED1(red) -> GPIO0[14]*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT, GPIO0, PIN_LED_RED_MASK,SALIDA);
	/*Led LED2(yellow) -> GPIO1[11]*/
	/*Led LED3(green) -> GPIO1[12]*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT, GPIO1, PIN_LED_YELLOW_MASK|PIN_LED_GREEN_MASK,SALIDA);


	/*===Inicialización de los puertos apagados===*/
	if (apagarLeds()==TRUE)
		return TRUE;
	else return FALSE;

};

/* Función  encargada de cambiar el estado a alto(encendido) de un led*/

uint8_t prendeLed(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_led->red.numPort,p_edu_ciaa_led->red.numPin);
			break;
		case YELLOW:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_led->yellow.numPort,p_edu_ciaa_led->yellow.numPin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_led->green.numPort,p_edu_ciaa_led->green.numPin);
		    break;
        case WHITE:
            Chip_GPIO_SetPortOutHigh(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->numPort,(1<<0)|(1<<1)|(1<<2));
            break;
		default:
			return FALSE;/*TODO:Realizar verificación con read!*/
	}
	return TRUE;
};

/* Función  encargada de cambiar el estado a bajo(apagado) de un led*/
uint8_t apagaLed(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_led->red.numPort,p_edu_ciaa_led->red.numPin);
			break;
		case YELLOW:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_led->yellow.numPort,p_edu_ciaa_led->yellow.numPin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_led->green.numPort,p_edu_ciaa_led->green.numPin);
		    break;
        case WHITE:
            Chip_GPIO_SetPortOutLow(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->numPort,(1<<0)|(1<<1)|(1<<2));
            break;
		default:
			return FALSE;
	}
	return TRUE;
};

/* Función  encargada de cambiar el estado a alto(encendido) de un led del RGB*/
void prendeLed_RGB(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->red.numPort,p_edu_ciaa_ledRGB->red.numPin);
			break;
		case BLUE:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->blue.numPort,p_edu_ciaa_ledRGB->blue.numPin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->green.numPort,p_edu_ciaa_ledRGB->green.numPin);
		    break;
        case WHITE:
            Chip_GPIO_SetPortOutHigh(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->numPort,(1<<0)|(1<<1)|(1<<2));
            break;
	}

};

/* Función  encargada de cambiar el estado a bajo(apagado) de un led del RGB*/
void apagaLed_RGB(uint8_t color){
	switch (color) {
			case RED:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->red.numPort,p_edu_ciaa_ledRGB->red.numPin);
				break;
			case BLUE:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->blue.numPort,p_edu_ciaa_ledRGB->blue.numPin);
				break;
			case GREEN:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->green.numPort,p_edu_ciaa_ledRGB->green.numPin);
			    break;
            case WHITE:
                Chip_GPIO_SetPortOutLow(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->numPort,(1<<0)|(1<<1)|(1<<2));
                break;
		}
};

/* Función  encargada de cambiar el estado de un led*/
void toggleLed(uint8_t color){
	switch (color){
			case RED:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_led->red.numPort,p_edu_ciaa_led->red.numPin);
				break;
			case YELLOW:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_led->yellow.numPort,p_edu_ciaa_led->yellow.numPin);
				break;
			case GREEN:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_led->green.numPort,p_edu_ciaa_led->green.numPin);
				break;
            case WHITE:
                Chip_GPIO_SetPortToggle(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->numPort,(1<<0)|(1<<1)|(1<<2));
                break;
	}
};

/* Función  encargada de cambiar el estado de un led del RGB*/
void toggleLed_RGB(uint8_t color){
	switch (color) {
			case RED:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->red.numPort,p_edu_ciaa_ledRGB->red.numPin);
				break;
			case BLUE:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->blue.numPort,p_edu_ciaa_ledRGB->blue.numPin);
				break;
			case GREEN:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,p_edu_ciaa_ledRGB->green.numPort,p_edu_ciaa_ledRGB->green.numPin);
			    break;
		}
};

/*TODO: Realizar la verificaciones de las funciones (ej. Return FALSE or TRUE) */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
