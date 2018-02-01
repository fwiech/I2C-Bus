#ifndef I2C_BUS_H
#define I2C_BUS_H

#include <stdbool.h>

/*
	github repo: <https://github.com/florianwiech/I2C-Bus>

	library created by
		> Florian Wiech		<https://github.com/florianwiech>
		> Thomas Niestroj	<https://github.com/Manorka>

	official specification:
	> NXP <https://www.nxp.com/docs/en/user-guide/UM10204.pdf>

	Requirements:
	To use this library you have to implement the following functions:

	> setSDA_HIGH()		// set SDA line to high
	> setSDA_LOW()		// set SDA line to low

	> setSCL_HIGH()		// set SCL line to high
	> setSCL_LOW()		// set SCL line to low

	> setPULLUP(true)	// set SDA line to input
	> setPULLUP(false)	// set both SDA & SCL to output (important to set both!)

	> getSDAValue()		// returns current value on SDA line

	> void i2cbus_delay_us(int)	// call a delay function
					//	@param Integer delaytime in ms
*/

void setSDA_HIGH();
void setSDA_LOW();
void setSCL_HIGH();
void setSCL_LOW();
void setPULLUP(bool);
bool getSDAValue();
void i2cbus_delay_us(int);

#define SDA_HIGH    setSDA_HIGH()
#define SDA_LOW     setSDA_LOW()

#define SCL_HIGH    setSCL_HIGH()
#define SCL_LOW     setSCL_LOW()

#define PULLUP_ON   setPULLUP(true)
#define PULLUP_OFF	setPULLUP(false)

#define READ_SDA_VALUE  getSDAValue()


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
	#ifndef DELAY_TIME
		#define DELAY_TIME 200
	#endif
	#define DELAY i2cbus_delay_us(DELAY_TIME)
#endif

void i2cbus_init();
void i2cbus_send_start_condition();
void i2cbus_send_stop_condition();
void i2c_bus_create_beat(int);
bool i2cbus_receive_ack();
bool i2cbus_data_write(int);
bool i2cbus_address_7_write(unsigned int, int);


#endif
