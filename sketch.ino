#include <Wire.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define MPU6050_ADDRESS 0x68 // MPU6050 I2C address
		
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// 'yorha_esp', 53x60px
const uint8_t yorha_esp [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 
	0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x06, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x16, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x16, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x0c, 0x16, 0x03, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x56, 0x03, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x56, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0xac, 0x77, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x98, 0x77, 0x06, 0x00, 
	0x00, 0x00, 0x00, 0x66, 0xa7, 0x39, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc6, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x67, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x98, 0x67, 0x06, 0x00, 0x00, 0x00, 0x00, 0x38, 
	0x36, 0x06, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x28, 0x73, 0x05, 
	0x00, 0x00, 0x00, 0xe0, 0x59, 0x96, 0xc6, 0x01, 0x00, 0x00, 0xe0, 0xb0, 0x4d, 0xc2, 0x01, 0x00, 
	0x00, 0xc0, 0x66, 0xad, 0xb9, 0x01, 0x00, 0x00, 0xc0, 0xf7, 0xed, 0xbb, 0x02, 0x00, 0x00, 0xd0, 
	0x36, 0x3e, 0xdb, 0x00, 0x00, 0x00, 0xdc, 0x36, 0x1e, 0xdf, 0x08, 0x00, 0x00, 0xee, 0x27, 0x0c, 
	0xfb, 0x03, 0x00, 0x00, 0xe3, 0xcf, 0xdc, 0xfc, 0x07, 0x00, 0x80, 0x11, 0xff, 0xff, 0x37, 0x1e, 
	0x00, 0x40, 0x00, 0xfe, 0xfd, 0x17, 0x70, 0x00, 0x20, 0x00, 0xf6, 0xff, 0x17, 0x80, 0x01, 0x00, 
	0x00, 0xf7, 0xf3, 0x27, 0x00, 0x00, 0x00, 0x00, 0x03, 0x16, 0x4c, 0x00, 0x00, 0x00, 0x80, 0x03, 
	0x14, 0x4c, 0x00, 0x00, 0x00, 0x80, 0x09, 0x06, 0x1c, 0x00, 0x00, 0x00, 0x80, 0x05, 0x06, 0x98, 
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x06, 0xb0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x60, 0x00, 0x00, 
	0x00, 0x40, 0x00, 0x06, 0x40, 0x01, 0x00, 0x00, 0x20, 0x00, 0x06, 0x80, 0x01, 0x00, 0x00, 0x60, 
	0x00, 0x04, 0x80, 0x01, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 
	0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

void printCenter(const char* buf, int x, int y)
{
  uint16_t w;
  w = display.getStrWidth(buf); //calc width of new string
  display.setCursor((x - w / 2) + 64, y);

  // Give text a backdrop to not mingle with image
  display.setDrawColor(0);
  display.drawBox(0, y - 8, 128, 8);

  // Draw text
  display.setDrawColor(1);
  display.print(buf);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  display.begin();
  display.clearBuffer();

  display.setBitmapMode(false /* solid */);
  display.setDrawColor(1);
  display.drawXBM( 64-26, 2, 53, 60, yorha_esp);
  display.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  printCenter("YoRHa", 0, 54);
  display.sendBuffer();
}

void loop() {
  //u8g2.clearBuffer();					// clear the internal memory
  //u8g2.sendBuffer();	
  delay(1000); // this speeds up the simulation
}
