#define F_CPU 1000000UL

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define SDA_HIGH    PORTB |= 0b00000010
#define SDA_LOW     PORTB &= 0b11111101

#define SCL_HIGH    PORTB |= 0b00000001
#define SCL_LOW     PORTB &= 0b11111110

#define PULLUP_ON   DDRB &=0b11111101
#define PULLUP_OFF	DDRB |=0b00000011

#define READ_SDA_VALUE  (PORTB & (1 << 1)) >> 1

#include "i2cbus-transmitter.h"


#include "lcd-display.h"

int lcd_display_address_40h = 0b01000000;

int main() {

  i2cbus_init();

  while(1) {

    i2cbus_send_start_condition();
    if(i2cbus_address_7_write(lcd_display_address_40h, 0) == 1) {

      // send some data

    }
    i2cbus_send_stop_condition();

    //------- RESET--------
		//SDA_HIGH_SCL_HIGH;
		_delay_ms(2000);
  }

  return 0;
}
