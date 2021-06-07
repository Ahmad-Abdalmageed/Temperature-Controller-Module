/*
 * DSP_Manager.c
 *
 * Created: 03-Jun-21 1:51:34 PM
 *  Author: Refaey
 */ 

#include "DSP_Manager.h"

extern uint8_t SET_Temperature;
extern uint8_t CRT_Temperature;

extern uint8_t state_indx;

void WelcomeScreen()
{
	/* Setup LCD PORT and PINs Configurations */
	LCD_vInit();
	
	/* Number of loops for welcome screen animation */
	uint8_t animation_loops = 3;
	
	uint8_t steps = 16;
	LCD_movecursor(1, steps);
	LCD_vSend_string("WELCOME");
	
	/* The welcome Screen shall display the word �WELCOME� on the Character LCD */
	for (animation_loops = 3; animation_loops > 0; animation_loops--)
	{
		/* The welcome word shall move from right to left until the end of the screen */
		for (steps = 16; steps > 1; steps--)
		{
			LCD_vShiftDisplay(1);
			/* TODO: Convert this delay to a periodic timer function */
			_delay_ms(1);
		}
		
		/* The welcome word shall move from left to right until the other end of the screen */
		for (steps = 1; steps < 16; steps++)
		{
			LCD_vShiftDisplay(0);
			_delay_ms(1);
		}
	}
}

void IdleScreen()
{
	LCD_clearscreen();
	LCD_vSend_string("SET:");
	
	LCD_movecursor(1, 11);
	LCD_vSend_string("CRT:");
	
	/* Update Temperatures Values */
	Display_SET_Temperature(SET_Temperature);
	Display_CRT_Temperature(CRT_Temperature);

	/* Update System State */
	LCD_movecursor(2, 1);
	LCD_vSend_string("STATE:");

	Display_STATE("STANDBY");
}

void Display_SET_Temperature(uint8_t value)
{	
	char temp_value[2];
	
	/* If Set temperature is less than 10, its value shall be written on the form 0X */
	if (value < 10)
	{
		/* Converts Units to character */
		temp_value[0] = '0';
		temp_value[1] = value + '0';
	}
	else
	{
		sprintf(temp_value, "%d", value);
	}
	
	/* Location of XX in LCD (SET:XX) */
	LCD_movecursor(1, 5);
	LCD_vSend_string(temp_value);
	
}

void Display_CRT_Temperature(uint8_t value)
{
	if (state_indx == ERROR_INDEX || state_indx == STANDBY_INDEX)
	{
		Display_CRT_Temperature_ERROR();
	}
	else
	{
		char temp_value[2];
		
		/* If Current temperature is less than 10, its value shall be written on the form 0X */
		if (value < 10)
		{
			/* Converts Units to character */
			temp_value[0] = '0';
			temp_value[1] = value + '0';
		}
		else
		{
			sprintf(temp_value, "%d", value);
		}
		
		/* Location of YY in LCD (CRT:YY) */
		LCD_movecursor(1, 15);
		LCD_vSend_string(temp_value);
	}
}

void Display_CRT_Temperature_ERROR()
{
	/* Location of YY in LCD (CRT:YY) */
	LCD_movecursor(1, 15);
	LCD_vSend_char(0xFF);
	LCD_vSend_char(0xFF);
}

void Display_STATE(char *state)
{
	/* System state section shall be written on the form STATE: SSSSS. 
	 * Where SSSSS is equal to the system state.
	 */

	/* Location of System State in LCD (STATE:SSSSS) */
	LCD_movecursor(2, 7);
	LCD_vSend_string(state);
	LCD_vSend_string("     ");
}