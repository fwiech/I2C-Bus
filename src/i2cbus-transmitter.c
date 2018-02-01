#include "i2cbus-transmitter.h"

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

bool i2cbus_data_write(int data) {
	int index;
	for(index = 7; index >= 0; index--) {
        int thebit = (data & (1 << index)) >> index;
		i2c_bus_create_beat(thebit);
	}
	return i2cbus_receive_ack();
}

bool i2cbus_address_7_write(unsigned int address, int read_write) {
	address = address | (read_write << 0);
	return i2cbus_data_write(address);
}

/**
 * ACK
*/
bool i2cbus_receive_ack() {
	bool ack = false;

	PULLUP_ON;
	DELAY;
	SCL_HIGH;
	DELAY;

	ack = READ_SDA_VALUE;

	DELAY;
	SCL_LOW;
	DELAY;
	PULLUP_OFF;

	return ack;
}

/**
 * HELPER
*/
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
