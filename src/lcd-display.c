#include "lcd-display.h"


bool lcd_display_write(int data_4bit, int register_select) {

	// position data for transfer
	//		ligthning,	      write,	 register_select,	  data-bits
	int data = (display_lighting << 7) | (0 << 5) | (register_select << 4) | (data_4bit & 0x0F);

	bool result = true;

	if(lcd_display_send_byte(data | (1 << 6)) == false) {
		 result = false;
	}
	if(lcd_display_send_byte(data) == false) {
		 result = false;
	}

	return result;
}

bool lcd_display_init() {
	display_lighting = 0;

	// wait at least 15ms
	DELAY_MS(15);

	// interface set to 8-Bit
	if(lcd_display_write(0b0011, 0) == false) return false;

	// wait at least 4,1ms
	DELAY_MS(5);

	// interface set to 8-Bit
	if(lcd_display_write(0b0011, 0) == false) return false;

	// wait at least 110us
	DELAY_MS(1);

	// interface set to 8-Bit
	if(lcd_display_write(0b0011, 0) == false) return false;

	// interface set to 4-Bit
	if(lcd_display_write(0b0010, 0) == false) return false;

	// 2 doublesaced with 5x8 matrix
	if(lcd_display_write(0b0010, 0) == false) return false;
	if(lcd_display_write(0b1000, 0) == false) return false;

	// display off
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b1000, 0) == false) return false;

	// delete display
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b0001, 0) == false) return false;

	// cursor to the right, no display shift
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b0010, 0) == false) return false;

	// display on
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b1111, 0) == false) return false;

	return true;
}

bool lcd_display_send_character(char character, int row, int column) {

	// set DDRAM
	if(lcd_display_write((row * 4) + 4, 0) == false) return false;
	if(lcd_display_write(column, 0) == false) return false;

	// set CG RAM
	if(lcd_display_write(((int)character >> 4), 1) == false) return false;
	if(lcd_display_write(((int)character & 0x0F), 1) == false) return false;

	return true;
}

/**
 * helper
*/

/**
 * @function lcd_display_write_row
 * @param text: max. 16 chracters
 * @param row: 1 -> first row, 2 -> second row
*/
bool lcd_display_write_row(char text[], int row) {
	int index;
	for (index = 0; text[index] != '\0'; index++) {
		if(lcd_display_send_character(text[index], row, index) == false) return false;
	}

	return true;
}

bool lcd_display_write_first_row(char text[]) {
	return lcd_display_write_row(text, 1);
}

bool lcd_display_write_second_row(char text[]) {
  	return lcd_display_write_row(text, 2);
}


bool lcd_display_cursor_home() {
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b0010, 0) == false) return false;
	return true;
}

bool lcd_display_cursor_shift(int display_cursor, int right_left) {
	if(lcd_display_write(0b0001, 0) == false) return false;
	if(lcd_display_write((0b0000 | (display_cursor << 3) | (right_left << 2) ), 0) == false) return false;
	return true;
}

bool lcd_display_clear() {
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write(0b0001, 0) == false) return false;
	return true;
}

bool lcd_display_cursor_settings(int display_on_off, int cursor_on_off, int cursor_blink_on_off) {
	if(lcd_display_write(0b0000, 0) == false) return false;
	if(lcd_display_write((0b1000) | (display_on_off << 2) | (cursor_on_off << 1) | (cursor_blink_on_off), 0) == false) return false;
	return true;
}
