#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// config vars
int display_ligthning = 0;

void lcd_display_write(int data_4bit, int register_select) {

	// position data for transfer
	//			    ligthning,					       write,		  register_select,		     data-bits
	int data = (display_ligthning << 7) | (0 << 5) | (register_select << 4) | (data_4bit & 0x0F);

	SEND_BYTE(data | (1 << 6));
	SEND_BYTE(data);
}

void lcd_display_init() {

	// wait at least 15ms
	DELAY_MS(15);

	// interface set to 8-Bit
	lcd_display_write(0b0011, 0);

	// wait at least 4,1ms
	DELAY_MS(5);

	// interface set to 8-Bit
	lcd_display_write(0b0011, 0);

	// wait at least 110us
	DELAY_MS(1);

	// interface set to 8-Bit
	lcd_display_write(0b0011, 0);

	// interface set to 4-Bit
	lcd_display_write(0b0010, 0);

	// 2 doublesaced with 5x8 matrix
	lcd_display_write(0b0010, 0);
	lcd_display_write(0b1000, 0);

	// display off
	lcd_display_write(0b0000, 0);
	lcd_display_write(0b1000, 0);

	// delete display
	lcd_display_write(0b0000, 0);
	lcd_display_write(0b0001, 0);

	// cursor to the right, no display shift
	lcd_display_write(0b0000, 0);
	lcd_display_write(0b0010, 0);

	// display on
	lcd_display_write(0b0000, 0);
	lcd_display_write(0b1111, 0);

}

void lcd_display_send_character(char character, int row, int column) {

	// set DDRAM
	lcd_display_write((row * 4) + 4, 0);
	lcd_display_write(column, 0);

	// set CG RAM
	lcd_display_write(((int)character >> 4), 1);
	lcd_display_write(((int)character & 0x0F), 1);

}

#endif
