#ifndef MMA7660_h
#define MMA7660_h

#include <Arduino.h>

#define MMA7660_CTRL_ID 0x4C
#define XOUT_REG 0x00
#define YOUT_REG 0x01
#define ZOUT_REG 0x02
#define TILT_REG 0x03
#define SRST_REG 0x04  //Sampling rate status
#define SPCNT_REG 0x05 //Sleep count
#define INTSU_REG 0x06 //Interrupt setup
#define MODE_REG 0x07
#define SR_REG 0x08    //Auto-wake/sleep and portrait/landscape filter
#define PDET_REG 0x09  //Tap detection
#define PD_REG 0x0A    //Tap debounce count
#define X_AXIS 0x00
#define Y_AXIS 0x01
#define Z_AXIS 0x02
#define X_SHAKE 0x80
#define Y_SHAKE 0x40
#define Z_SHAKE 0x20

// library interface description
class MMA7660
{
  // user-accessible "public" interface
	public:
		MMA7660();
		void init();
		void setPowerMode(int mode);
		void setSamples(int samples);
		void enableTap();
		void enableShake(uint8_t axis);
		uint8_t readTilt();
		int readAxis(uint8_t axis);
		uint8_t read(uint8_t REG_ADDRESS);

	private:
		void write(uint8_t REG_ADDRESS, uint8_t DATA);
};

#endif