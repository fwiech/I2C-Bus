#ifndef I2C_BUS_H
#define I2C_BUS_H

#ifndef SDA_HIGH_SCL_HIGH
	#define SDA_HIGH_SCL_HIGH	SDA_HIGH; SCL_HIGH
#endif

#ifndef SDA_HIGH_SCL_LOW
	#define SDA_HIGH_SCL_LOW	SDA_HIGH; SCL_LOW
#endif

#ifndef SDA_LOW_SCL_HIGH
	#define SDA_LOW_SCL_HIGH	SDA_LOW; SCL_HIGH
#endif

#ifndef SDA_LOW_SCL_LOW
	#define SDA_LOW_SCL_LOW		SDA_LOW; SCL_LOW
#endif

#ifndef DELAY
	#ifndef _UTIL_DELAY_H_
		#include <util/delay.h>
	#endif
	#ifndef DELAY_TIME
		#define DELAY_TIME 200
	#endif
	#define DELAY _delay_us(DELAY_TIME)
#endif

void i2cbus_init() {
  PULLUP_OFF;
}

void i2cbus_send_start_condition() {
	SDA_LOW_SCL_HIGH;
	DELAY;
	SDA_LOW_SCL_LOW;
	DELAY;
}

void i2cbus_send_stop_condition() {
	SDA_LOW_SCL_LOW;
	DELAY;
	SDA_LOW_SCL_HIGH;
	DELAY;
	SDA_HIGH_SCL_HIGH;
}

void i2c_bus_create_beat(int bit) {
	if(bit == 1) {
		SDA_HIGH_SCL_LOW;
		DELAY;
		SDA_HIGH_SCL_HIGH;
		DELAY;
		DELAY;
		SDA_HIGH_SCL_LOW;
		DELAY;
	} else {
		SDA_LOW_SCL_LOW;
		DELAY;
		SDA_LOW_SCL_HIGH;
		DELAY;
		DELAY;
		SDA_LOW_SCL_LOW;
		DELAY;
	}
}

int i2cbus_receive_ack() {
	int ack = 0;

	PULLUP_ON;
	DELAY;
	SCL_HIGH;
	DELAY;
	if(READ_SDA_VALUE == 0) {
		ack = 1;
	}
	DELAY;
	SCL_LOW;
	DELAY;
	PULLUP_OFF;

	return ack;
}

int i2cbus_data_write(int data) {
	int index;
	for(index = 7; index >= 0; index--) {
        int thebit = (data & (1 << index)) >> index;
		i2c_bus_create_beat(thebit);
	}
	return i2cbus_receive_ack();
}

int i2cbus_address_7_write(unsigned int address, int read_write) {
	address = address | (read_write << 0);
	return i2cbus_data_write(address);
}

#endif
