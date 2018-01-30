#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

/*
	github repo: <https://github.com/florianwiech/I2C-Bus>

	library created by
		> Florian Wiech		<https://github.com/florianwiech>
		> Thomas Niestroj	<https://github.com/Manorka>

	hardware components:
		> Display: Type HD44780, 4-Bit-Mode
      Specification: http://www.sprut.de/electronic/lcd/

	Requirements:
	To use this library you have to define the following constants:

	> SEND_BYTE   // name of the send function:
					      //		@param Integer address (8-Bit)
					      //		@return Integer (1 -> ack, 0 -> transfer fails)

	> DELAY_MS		// name of the delay function:
					      // the DELAY constant is optional, if you want to use the <util/delay> library.
*/


#ifndef DELAY_MS
	#ifndef _UTIL_DELAY_H_
		#include <util/delay.h>
	#endif
	#define DELAY_MS _delay_ms
#endif

// config vars
int display_ligthning = 0;

void lcd_display_write(int, int);

void lcd_display_init();

void lcd_display_send_character(char, int, int);

/**
 * helper
*/

/**
 * @function lcd_display_write_row
 * @param text: max. 16 chracters
 * @param row: 1 -> first row, 2 -> second row
*/
void lcd_display_write_row(char[], int);

void lcd_display_write_first_row(char[]);
void lcd_display_write_second_row(char[]);

void lcd_display_cursor_home();

#endif
