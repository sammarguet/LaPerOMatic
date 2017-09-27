#pragma once

#include"Cocktails.h"
#include"Arduino.h"
#include"LaPeroMatic.h"

//Define Time for each kind of glass in Milliseconds
#define TIME_SHOT     0
#define TIME_PONT     1
#define TIME_GOB      2
#define TIME_HALF     3
#define TIME_PINT     4
#define TIME_BOTTLE   5

const uint8_t	m_pmp[8] = {PM1  ,PM2  ,PM3  ,PM4  ,PM5  ,PM6  ,PM7  ,PM8  } ; // POMPES ;
const String	m_nameGlass[6] = {"un shot",	"un verre a Pont",	"un gobelet",	"un demi",	"une pinte",	"une bouteille"} ;
const int		m_timeGlass[6] = {2500,		67000,				9000,			18500,		36000,			70000} ;

class Barman
{
public:
	Barman( void ) ;
	~Barman( void ) ;

	void work( void ) ;
	void setManAuto( void ) ;
	void giveDrink( Cocktails &cocktail ) ;
	void printTotalGlasses( void ) ;
	bool getisOccupied( void ) ;
	void setisOccupied( bool isOccupied ) ;
	void setbiggerGlass( void ) ;

private:
	bool		m_isManual ;
	bool		m_isOccupied ;
	uint16_t	m_totalGlasses ;
	uint8_t		m_sizeGlass ;
};

extern Barman Suzette ;