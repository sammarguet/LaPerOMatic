#pragma once

#include"Arduino.h"
#include <LiquidCrystal.h>
#include "LaPeroMatic.h"

class LCD : public LiquidCrystal
{
public:
	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) ;
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) ;
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) ;
	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

	~LCD(void);

	void setStarterScreen(const String &nameGlass) ;
	void setStartService(String nameCocktail) ;
	void setEndOfService() ;
	void setNewGlass(const String &nameGlass) ;
};

extern LCD lcd ;