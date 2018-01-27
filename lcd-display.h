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

#endif
