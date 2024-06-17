#include "Display.h"
#include "delay.h"
#include <stdio.h>
#include "../User.h"

volatile int showForNSecondsCalledFlag = false;
void (*returnScreen)(void) = Display::showINITScreen;
long nScreenMilliseconds = 0;
volatile long millisWhenShowForNSecondsCalled = 0;

Display::Display()
{
	ssd1306_init();
	ssd1306_setorientation(1); 
	ssd1306_setfont(Dialog_plain_12);
}

void Display::displayInit()
{
	
	ssd1306_init();
	ssd1306_setorientation(1); 
	ssd1306_setfont(Dialog_plain_12);
}

void Display::clearScreen()
{
	ssd1306_clearscreen();
	ssd1306_update();
}

void Display::showINITScreen()
{
	ssd1306_clearscreen();
	ssd1306_putstring(0,0, "Awaiting connection");
	ssd1306_putstring(0,16, "with admin...");
	ssd1306_update();
}

void Display::showQRCODEScreen()
{
	ssd1306_clearscreen();
	
	static const unsigned char qr2[] = {
	0xfc, 0xfc, 0xfc, 0x1c, 0x1c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x1c, 0x1c, 
	0xfc, 0xfc, 0x7c, 0x7c, 0x9c, 0x9c, 0xfc, 0xfc, 0x7c, 0x7c, 0xfc, 0xfc, 0x9c, 0x9c, 0x7c, 0xfc, 
	0xfc, 0xdc, 0x9c, 0x7c, 0x7c, 0x1c, 0x1c, 0xfc, 0xfc, 0x1c, 0x1c, 0xfc, 0xfc, 0x1c, 0x1c, 0x9c, 
	0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x1c, 0x1c, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0xff, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xfc, 0xf8, 
	0x01, 0x01, 0xcf, 0xdf, 0xf8, 0xf8, 0x31, 0x31, 0x09, 0x0d, 0x0e, 0x07, 0x07, 0xe1, 0xf1, 0xce, 
	0xce, 0x0c, 0x08, 0x37, 0x37, 0xf6, 0xf7, 0xff, 0xff, 0x00, 0x00, 0xff, 0xf9, 0xc1, 0xc1, 0xc1, 
	0xc1, 0xc1, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 
	0x1c, 0x0c, 0x3c, 0x3c, 0x0c, 0x0c, 0xcc, 0xcc, 0xcf, 0xcf, 0x3c, 0x3c, 0x03, 0x03, 0x30, 0x30, 
	0xff, 0xff, 0x00, 0x00, 0xff, 0xfe, 0xfc, 0xc2, 0xc3, 0x3c, 0x3c, 0xff, 0xff, 0xc0, 0xc0, 0x33, 
	0x33, 0x30, 0x30, 0xcf, 0xcf, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0xfc, 0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xe3, 0xff, 0xff, 0x0c, 0x0c, 0xfc, 0xbb, 0x33, 
	0xfc, 0xfc, 0xec, 0xcc, 0xc0, 0x40, 0x30, 0x30, 0xc0, 0xc0, 0xff, 0xff, 0x0c, 0x0c, 0x3c, 0x3c, 
	0xcf, 0xcf, 0xcc, 0xfc, 0xfc, 0xfc, 0xfc, 0xc0, 0xc0, 0xcf, 0xcf, 0x3c, 0x3c, 0x0f, 0x8f, 0xfc, 
	0xfc, 0x30, 0x10, 0x0f, 0x0f, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0xc0, 0xc0, 0x3f, 0xbf, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0x7f, 0x67, 0x67, 0x98, 0x18, 0x07, 0x1b, 0x99, 0xe7, 0xe7, 0x66, 0x66, 
	0x60, 0x60, 0x00, 0x00, 0x60, 0x60, 0x01, 0x03, 0x67, 0x6f, 0xfe, 0xfe, 0x06, 0x04, 0xe0, 0x90, 
	0x98, 0x9f, 0x9f, 0xff, 0xff, 0x78, 0x78, 0xff, 0xff, 0x61, 0x61, 0xe1, 0xe1, 0x19, 0x39, 0x79, 
	0x00, 0x00, 0x07, 0x07, 0xc7, 0xe7, 0xe0, 0xe0, 0xe7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0x78, 
	0x78, 0x78, 0x78, 0x7f, 0x7f, 0x78, 0x77, 0x67, 0x67, 0x67, 0x66, 0x66, 0xe6, 0xe6, 0x60, 0x60, 
	0x9e, 0x9e, 0x98, 0x98, 0x78, 0x38, 0x01, 0x01, 0x60, 0x60, 0x99, 0x87, 0x87, 0x07, 0x07, 0x07, 
	0x07, 0xf8, 0xf8, 0x1f, 0x1f, 0x00, 0x00, 0xe7, 0xe7, 0x66, 0x66, 0xe0, 0xe0, 0x00, 0xe0, 0xe0, 
	0xdf, 0x9f, 0x87, 0x87, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x02, 
	0x02, 0x06, 0x06, 0x06, 0xfe, 0xfe, 0x00, 0x00, 0xff, 0xff, 0xcc, 0xc8, 0x09, 0x09, 0xf3, 0xf3, 
	0xc8, 0xdc, 0x3e, 0x3e, 0xce, 0x8f, 0x0f, 0x0f, 0xcf, 0xf0, 0xf0, 0xc8, 0xc8, 0x38, 0x39, 0xc2, 
	0xc2, 0x30, 0x20, 0xc7, 0x87, 0x06, 0x07, 0xc3, 0xe1, 0xf0, 0x70, 0x31, 0x03, 0x07, 0xcf, 0xcf, 
	0x30, 0x30, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x30, 0x30, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x30, 0x30, 0x3f, 0x3f, 0x3f, 0x3f, 0x30, 0x30, 0x33, 0x33, 0x3f, 0x3f, 0x3c, 0x3c, 
	0x33, 0x31, 0x30, 0x38, 0x3c, 0x3f, 0x3f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3c, 0x3c, 0x33, 
	0x33, 0x33, 0x31, 0x30, 0x39, 0x3f, 0x3e, 0x3c, 0x30, 0x30, 0x3f, 0x3f, 0x33, 0x33, 0x3f, 0x3f
	};
	
	ssd1306_clearscreen();
	ssd1306_drawbitmap(34, qr2, 60);
	ssd1306_update();
}

void Display::showSEARCHScreen()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "Find waypoint");
	
	ssd1306_putstring(0, 13, "number ");
	ssd1306_putchar((char)User::userSingleton->currentWayPointNumber + '1');
	ssd1306_putchar('.');
	
	ssd1306_putstring(0, 29, "Press D to show");
	
	ssd1306_putstring(0, 42, "directions.");
	ssd1306_update();
}

void Display::showLeftArrow()
{	
	ssd1306_clearscreen();
	
	static const unsigned char ldir[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 
	0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0x38, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 
	0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc7, 0xc3, 0xc1, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 
	0x9f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
	0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	ssd1306_drawbitmap(42, ldir, 40);
	//ssd1306_putstring(64, 32, "<-");
	ssd1306_update();
}

void Display::showRightArrow()
{
	ssd1306_clearscreen();
	
	static const unsigned char rdir[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x08, 0x18, 0x38, 0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc1, 0xc3, 0xc7, 
	0xdf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
	0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 
	0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

	
	ssd1306_drawbitmap(42, rdir, 40);
	//ssd1306_putstring(64, 32, "->");
	ssd1306_update();
}

void Display::showUpArrow()
{	
	ssd1306_clearscreen();
	
	static const unsigned char udir[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 
	0x7f, 0x7f, 0x1f, 0x1f, 0x07, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x03, 
	0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
	0x07, 0x0f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	ssd1306_drawbitmap(42, udir, 40);
	ssd1306_update();
}
	
void Display::showDownArrow()
{	
	ssd1306_clearscreen();
	
	static const unsigned char ddir[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xe0, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xf8, 0xf8, 0xe0, 0xc0, 0xc0, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 
	0x7f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
	0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
	0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	ssd1306_drawbitmap(42, ddir, 40);
	ssd1306_update();
}

void Display::showS_HOT_COLDVeryColdStatus()
{	
	ssd1306_clearscreen();
	
	static const unsigned char vCold[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0x38, 
	0x18, 0x0c, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0e, 0x0c, 0x1c, 0x38, 0x70, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0xc0, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x40, 
	0xe0, 0x40, 0x00, 0x00, 0x18, 0xb0, 0x84, 0x84, 0x85, 0x86, 0x3c, 0x64, 0x83, 0x41, 0x20, 0x32, 
	0x0e, 0x0c, 0x00, 0x03, 0x91, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x8b, 0x88, 0x40, 0x30, 0x70, 0x4c, 
	0x04, 0x03, 0xc1, 0x46, 0x3d, 0x61, 0x81, 0x21, 0x21, 0x07, 0x18, 0x00, 0x00, 0x02, 0x07, 0x02, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x23, 0xa1, 0xc0, 
	0x40, 0x00, 0x90, 0x14, 0xec, 0x90, 0x90, 0x00, 0x40, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 0x18, 0x04, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 
	0x0c, 0x18, 0x70, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x00, 0x06, 0x0c, 0x02, 0x12, 0x01, 0x29, 0x10, 0x02, 0x0c, 0x02, 0x06, 
	0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf9, 0xce, 0x3e, 0xfe, 0xfe, 
	0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
	0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x9e, 0xe0, 0x7f, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x03, 0x06, 0x0d, 0x0b, 0x13, 0x17, 0x37, 0x2f, 0x2f, 0x6f, 0x4f, 0x5f, 0x5f, 
	0x5f, 0x5f, 0x5f, 0x4f, 0x6f, 0x2f, 0x27, 0x37, 0x13, 0x1b, 0x09, 0x04, 0x06, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	ssd1306_drawbitmap(29, vCold, 70);
	ssd1306_update();
}

void Display::showS_HOT_COLDColdStatus()
{
	ssd1306_clearscreen();
	
	static const unsigned char cold[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x60, 0x70, 0x30, 
	0x30, 0x30, 0x30, 0x30, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0xf0, 0x00, 
	0x40, 0x40, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x41, 0x14, 0x22, 0x23, 0x00, 0x14, 0x08, 
	0xff, 0x08, 0x14, 0x02, 0x21, 0x02, 0x15, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0xb0, 
	0xc8, 0xf4, 0xf6, 0xfb, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
	0xf8, 0xf8, 0xfb, 0xf2, 0xf4, 0xec, 0xd8, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xf7, 
	0x9e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0xe3, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x06, 0x0d, 0x0b, 0x13, 0x17, 0x2f, 0x2f, 0x6f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 
	0x5f, 0x5f, 0x5f, 0x6f, 0x2f, 0x2f, 0x37, 0x13, 0x1b, 0x0d, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
	
	ssd1306_drawbitmap(39, cold, 50);
	ssd1306_update();
}

void Display::showS_HOT_COLDWarmStatus()
{
	ssd1306_clearscreen();
	
	static const unsigned char warm[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 
	0x60, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0xfe, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe0, 0xe0, 
	0xc0, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xfe, 0xff, 0xbf, 0x1f, 
	0x07, 0x0f, 0x1f, 0xff, 0xff, 0xff, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 
	0x30, 0xd8, 0xec, 0xf4, 0xfa, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfb, 0xfa, 0xf4, 0xec, 0xc8, 0xb0, 0x60, 0xc0, 0x00, 
	0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0x7f, 0xc4, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0xc0, 
	0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x04, 0x09, 0x1b, 0x17, 0x17, 0x27, 0x2f, 0x2f, 0x2f, 0x4f, 
	0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x6f, 0x2f, 0x2f, 0x2f, 0x27, 0x17, 0x13, 0x1b, 0x09, 0x04, 0x06, 
	0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	ssd1306_drawbitmap(39, warm, 50);
	ssd1306_update();
}

void Display::showS_HOT_COLDHotStatus()
{
	ssd1306_clearscreen();
	
	static const unsigned char hot[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x38, 0x18, 0x0c, 0x0c, 0x0c, 
	0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x38, 0x70, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0xfe, 0xfe, 0xfe, 
	0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xfe, 0xff, 0xff, 0x7f, 0x7f, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xe0, 
	0x80, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x0f, 0x3f, 0x7f, 0x7f, 0xc7, 0x81, 0x00, 0x00, 0x81, 0xc7, 0xff, 0x7f, 
	0x3f, 0x1f, 0x0f, 0x00, 0x00, 0x10, 0x3b, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xd8, 
	0xec, 0xfa, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0xf9, 0xf2, 0xe4, 0x98, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xe4, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x06, 0x0d, 0x0b, 0x13, 0x17, 0x2f, 0x2f, 0x2f, 0x2f, 0x5f, 0x5f, 0x4f, 
	0x2f, 0x2f, 0x2f, 0x27, 0x17, 0x13, 0x09, 0x0d, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
		
	ssd1306_drawbitmap(39, hot, 50);
	ssd1306_update();
}

void Display::showS_HOT_COLDNotCloseAnymore()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "You've strayed too");
	
	ssd1306_putstring(0, 13, "far from the");
	
	ssd1306_putstring(0, 26, "waypoint!");
	
	ssd1306_putstring(0, 39, "Please search for");
	
	ssd1306_putstring(0, 52, "it again.");
	ssd1306_update();
}

void Display::showS_WAYPOINT_SimonSaysPuzzlePrompt()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "You've reached");
	
	ssd1306_putstring(0, 13, "the waypoint.");
	
	ssd1306_putstring(0, 26, "Memorize the");
	
	ssd1306_putstring(0, 39, "next sequence.");
	
	ssd1306_update();
}

void Display::showS_WAYPOINT_SimonSaysControlsTutorial()
{
	ssd1306_clearscreen();
	
	static const unsigned char controls[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x40, 0xc0, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 
	0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x60, 0xe0, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x07, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x07, 0x0f, 0x0d, 0x0c, 0x0d, 0x07, 
	0x02, 0x0f, 0x0f, 0x0d, 0x01, 0x0f, 0x0f, 0x00, 0x00, 0x07, 0x0f, 0x0d, 0x0c, 0x0c, 0x00, 0x08, 
	0x0f, 0x0f, 0x0d, 0x09, 0x01, 0x00, 0x07, 0x0f, 0x0d, 0x0d, 0x0f, 0x07, 0x00, 0x08, 0x0c, 0x0f, 
	0x0f, 0x0c, 0x08, 0x00, 0x0d, 0x0f, 0x0f, 0x0f, 0x0f, 0x05, 0x00, 0x00, 0x00, 0x0d, 0x09, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x38, 0x1c, 0x0e, 0x0f, 0xff, 0xff, 0x0f, 0x0e, 0x1c, 
	0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 
	0x7e, 0xfe, 0xff, 0x9b, 0x99, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x99, 0xdf, 0xff, 0xfe, 
	0x7c, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x70, 0xe0, 0xc0, 
	0xc0, 0xff, 0xff, 0xc0, 0xc0, 0xe0, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x03, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf2, 0xfe, 0xbe, 0x3e, 0xfc, 0xf0, 
	0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xc6, 0xfe, 0xfe, 0x92, 0x9e, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 0xc6, 0xc2, 0x82, 0xc6, 0xce, 0x44, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0xfe, 0xfe, 0xc2, 0x82, 0xc6, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  	};
	
	ssd1306_drawbitmap(16, controls, 96);
	ssd1306_update();
}

void Display::showAwaitingUserInput()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "Please repeat");
	
	ssd1306_putstring(0, 13, "the sequence.");
	ssd1306_update();
}

void Display::showNextRound(int round) {
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0 , "Round ");
	ssd1306_putchar  (((char)round+'0'));
	ssd1306_putstring(9*6, 0, "complete!"); 
	ssd1306_putstring(0, 30, "Get Ready for");
	ssd1306_putstring(0, 45, "round ");
	ssd1306_putchar  (((char)round+'1'));
	ssd1306_putchar  ('.');
	
	ssd1306_update();
}

void Display::showPuzzleLost()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(30, 20, "GAME LOST");
	ssd1306_update();
}

void Display::showPuzzleWon()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(30, 20, "GAME WON!");
	ssd1306_update();
}

void Display::showScreenForNSeconds(long n, void (*screenToBeShown)(void), void(*screenToReturnTo) (void))
{
	returnScreen = screenToReturnTo;
	screenToBeShown();

	showForNSecondsCalledFlag = true;
	
	millisWhenShowForNSecondsCalled = milliSecond;
	nScreenMilliseconds = n*1000;	
}

void Display::showLoading()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "Loading...");
	ssd1306_update();
}

void Display::showAwaitingReconnection()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "GPS connection");
	
	ssd1306_putstring(0, 13, "lost.");
	
	ssd1306_putstring(0, 26, "Please search");
	
	ssd1306_putstring(0, 39, "for a better");
	
	ssd1306_putstring(0, 52, "spot.");
	ssd1306_update();
}

void Display::showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "Game has ended.");
	
	ssd1306_putstring(0, 13, "You have reached");
	
	ssd1306_putstring(0, 26, "all waypoints.");
	ssd1306_putstring(0, 39, "Please return box to");
	ssd1306_putstring(0, 52, "companion app.");
	
	ssd1306_update();
}

void Display::showTurnOff() {
	ssd1306_clearscreen();
	ssd1306_putstring(0, 0, "Data has been");
	ssd1306_putstring(0, 13, "transfered.");
	ssd1306_putstring(0, 26, "box can safely");
	ssd1306_putstring(0, 39, "turned off.");
	ssd1306_update();
}

void Display::showS_ERROR_NO_SOURCE()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "ERROR:");
	
	ssd1306_putstring(0, 13, "Unknown error.");
	ssd1306_update();
}

void Display::showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "ERROR:");
	
	ssd1306_putstring(0, 13, "Failed to send");
	
	ssd1306_putstring(0, 26, "game data.");
	ssd1306_update();
}

void Display::showS_ERROR_ERROR_DURING_GAME()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "ERROR:");
	
	ssd1306_putstring(0, 13, "An error");
	
	ssd1306_putstring(0, 26, "occured during");
	
	ssd1306_putstring(0, 39, "game.");
	ssd1306_update();
}

void Display::showS_ERROR_ERROR_INIT()
{
	ssd1306_clearscreen();
	
	ssd1306_putstring(0, 0, "ERROR:");
	
	ssd1306_putstring(0, 13, "Error during");
	
	ssd1306_putstring(0, 26, "initialization.");
	ssd1306_update();
}

void Display::testDistance(double distance, long n, void(*screenToReturnTo) (void)) 
{
	returnScreen = screenToReturnTo;
	showForNSecondsCalledFlag = true;
	
	ssd1306_clearscreen();
	char dist[35];
	sprintf(dist, "%.1lf meter", distance);
	
	ssd1306_putstring(0, 0, (const char*)dist);
	ssd1306_update();
	
	millisWhenShowForNSecondsCalled = milliSecond;
	nScreenMilliseconds = n*1000;	
	
}
