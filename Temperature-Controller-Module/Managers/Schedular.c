/*
 * Schedular.c
 *
 * Created: 05-Jun-21 4:14:58 PM
 *  Author: Refaey
 */ 

#include "Schedular.h"

volatile uint8_t CRT_TEMP_COUNTER = 0;
volatile uint8_t SET_TEMP_COUNTER = 0; /* Remove This Later (Not used) */
volatile uint8_t HASH_KEY_COUNTER = 0;
volatile uint8_t ADC_COUNTER = 0;
volatile uint16_t ERROR_COUNTER = 0;

extern uint8_t SET_Temperature;
extern uint8_t CRT_Temperature;
extern uint8_t state_indx;

void Schedular_vInit()
{
	timer_CTC_init_interrupt();
}

ISR(TIMER0_COMP_vect)
{
	CRT_TEMP_COUNTER++;
	SET_TEMP_COUNTER++;
	HASH_KEY_COUNTER++;
	ADC_COUNTER++;
	
	if (state_indx  == OPERATION_INDEX && (SET_Temperature - CRT_Temperature) > 5)
	{
		ERROR_COUNTER++;
	}
}
