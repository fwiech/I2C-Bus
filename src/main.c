#define F_CPU 1000000UL

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>


#include "i2cbus-transmitter.h"
#include "lcd-display.h"

int lcd_display_address_40h = 0b01000000;

int main() {

  i2cbus_init();

  while(1) {

    i2cbus_send_start_condition();
    if(i2cbus_address_7_write(lcd_display_address_40h, 0) == true) {
  		if(lcd_display_init() == true) {

  			lcd_display_write_first_row("Embedded");
  	    lcd_display_write_second_row("Networking");

  		}
    }
    i2cbus_send_stop_condition();

    //------- RESET--------
		//SDA_HIGH_SCL_HIGH;
		_delay_ms(2000);
  }

  return 0;
}

/**
 * i2cbus helper
*/

void setSDA_HIGH() {
	PORTB |= 0b00000010;
}

void setSDA_LOW() {
	PORTB &= 0b11111101;
}

void setSCL_HIGH() {
	PORTB |= 0b00000001;
}

void setSCL_LOW() {
	PORTB &= 0b11111110;
}

void setPULLUP(bool on) {
	if(on == true) { // on
		DDRB &=0b11111101;
	} else { // off
		DDRB |=0b00000011;
	}
}

bool getSDAValue() {
	return ((PINB >> 1) && (1<<0));
}

void i2cbus_delay_us(int us) {
  _delay_us(us);
}


/**
  * lcd display helper
*/

bool lcd_display_send_byte(int byte) {
	return i2cbus_data_write(byte);
}
