#ifndef I2C_BUS_H
#define I2C_BUS_H

/*
	github repo: <https://github.com/florianwiech/I2C-Bus>

	library created by
		> Florian Wiech		<https://github.com/florianwiech>
		> Thomas Niestroj	<https://github.com/Manorka>

	Requirements:
	To use this library you have to define the following constants:

	> SDA_HIGH		 // set SDA line to high
	> SDA_LOW		   // set SDA line to low

	> SCL_HIGH		 // set SCL line to high
	> SCL_LOW		   // set SCL line to low

	> PULLUP_ON		 // set SDA line to input
	> PULLUP_OFF	 // set both SDA & SCL to output (important to set both!)

	> DELAY			   // name of the delay function:
	               // the DELAY constant is optional, if you want to use the <util/delay> library.
*/

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

void i2cbus_init();
void i2cbus_send_start_condition();
void i2cbus_send_stop_condition();
void i2c_bus_create_beat(int);
int i2cbus_receive_ack();
int i2cbus_data_write(int);
int i2cbus_address_7_write(unsigned int, int);


#endif
