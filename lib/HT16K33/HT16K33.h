#pragma once
#include <Arduino.h>
#include <Wire.h>

#define HT16K33_BLINK_CMD 			0x80 // I2C register for BLINK setting
#define HT16K33_TURN_OSCILLATOR 0x21 // I2C value to turn on oscillator
#define HT16K33_BLINK_DISPLAYON 0x01 // I2C value for steady on
#define HT16K33_CMD_BRIGHTNESS  0xE0 // I2C register for BRIGHTNESS setting
#define HT16K33_BLINK_OFF       0	 // I2C value for steady off
#define HT16K33_BLINK_2HZ       1	 // I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ       2	 // I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ    3	 // I2C value for 0.5 Hz blink

/*!
	@brief  Class driver for an 8x16 Led matrix with HT16K33 chip.
*/
class HT16K33{
	public:	
		HT16K33(const uint8_t address, TwoWire *wire = &Wire);
		bool 	 begin();
		void 	 setPixel(uint8_t c, uint8_t a);
		bool 	 getPixel(uint8_t c, uint8_t a);		
		void 	 resetPixel(uint8_t c, uint8_t a);		
		void 	 drawPixel(uint8_t c, uint8_t a, bool state);		
		void 	 clear();
		void 	 setDisplayState(bool state);
		void 	 setBrightness(uint8_t brightness);
		void 	 setBlinkRate(uint8_t rate);
		void 	 writeDisplay();
		
	private:
		bool 	 isConnected(); 
		void 	 reset();
		void 	 writeData(const uint8_t *data, size_t quantity);

		uint16_t _databuffer[8]; // Raw display buffer data
		uint8_t  _address;		 // The I2C device's address
		TwoWire* _wire; 		 // Pointer to the I2C bus interface
}; 