#include "LCD.h"

LCD lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) ;

LCD::LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) :
		LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7){}
LCD::LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) :
		LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7){}
LCD::LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) :
		LiquidCrystal(rs, rw, enable, d0, d1, d2, d3){}
LCD::LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) :
		LiquidCrystal(rs, enable, d0, d1, d2, d3){}

LCD::~LCD(void)
{
}

void LCD::setStarterScreen(const String &nameGlass)
{
	begin(16, 2);
	setCursor(0, 1);
	clear() ;
	setCursor(0, 0);
	print(CATCH_PHRASE);
	setCursor(0, 1);
	print(nameGlass + "?");
}

void LCD::setStartService(String nameCocktail)
{
	begin(16, 2);
	clear() ;
	setCursor(0, 0) ;
	print(nameCocktail) ;
}

void LCD::setEndOfService()
{
	unsigned long time_previous = millis() ;
	clear() ;
	setCursor(0, 0) ;
	print("Verre servi") ;
	setCursor(0, 1) ;
	print("100 %") ;
	while(millis()-time_previous < 1000){}
}

void LCD::setNewGlass(const String &nameGlass)
{
	unsigned long time_previous = millis() ;
	clear() ;
	setCursor(0, 0) ;
	print("Nouveau verre :") ;
	setCursor(0, 1) ;
	print(nameGlass) ;
	while(millis()-time_previous < 1000){}
	setStarterScreen(nameGlass) ;
}