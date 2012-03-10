#include <Arduino.h>
#include <I2C.h>
#include <MMA7660.h>

MMA7660::MMA7660()
{
	I2c.begin();
}

void MMA7660::init(){
	//set mode to standy to set sample rate
	write(MODE_REG, 0x00);
	write(INTSU_REG, 0x00);
	write(SR_REG, 0x00);  //120 samples and auto-sleep
	write(MODE_REG, 0x01); //set mode to active
}

void MMA7660::setPowerMode(int mode){

}

void MMA7660::setSamples(int samples){

}

void MMA7660::enableTap(){
	write(MODE_REG, 0x00);
	write(INTSU_REG, 0x04); //turn on tap interrupt
	write(SR_REG, 0x00);
	write(PDET_REG, 0x86); //enable Z-AXIS tap and set threshold to 6 taps
	write(PD_REG, 0x14); //set debounce filter to 21 measurements
	write(MODE_REG, 0xC1);
	//read(TILT_REG);
}

void MMA7660::enableShake(uint8_t axis){
	write(MODE_REG, 0x00);
	write(INTSU_REG, axis);
	write(MODE_REG, 0xC1);
}

uint8_t MMA7660::readTilt(){
	return read(TILT_REG);
}

int MMA7660::readAxis(uint8_t axis){
	uint8_t data = 0x40;

	//check if the alert bit is set, if so re-read
	while(data & 0x40){
		data = read(axis);
	}

	//if it's a negative value convert the two's complement
	if(data & 0x20){
		data += 0xC0; //the register returns a 6 bit number, fix for uint8_t
		data = ~data;
		data++;
		return (int)data * -1;
	}
	return (int)data;
}

void MMA7660::write(uint8_t REG_ADDRESS, uint8_t DATA){
	I2c.write((uint8_t)MMA7660_CTRL_ID,(uint8_t)REG_ADDRESS,(uint8_t)DATA);
}

uint8_t MMA7660::read(uint8_t REG_ADDRESS){
	I2c.read((uint8_t)MMA7660_CTRL_ID, (uint8_t)REG_ADDRESS,(uint8_t) 0x01);
	return I2c.receive();
}