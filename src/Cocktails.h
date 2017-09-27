#pragma once
#include"Arduino.h"

/* ********************************************************************************
  For each pump, you will find a drink :
  1 : Rhum blanc
  2 : Rhum ambre
  3 : Tequila
  4 : Sirop de sucre
  5 : Sirop d fraise
  6 : Jus d'orange
  7 : Jus d'ananas
  8 : NC
            1   2   3   4   5   6   7   8               
********************************************************************************* */

#define NB_BOTTLE	8

class Cocktails
{
public:
	Cocktails(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8);
	~Cocktails(void);

	uint8_t getQuantity(uint8_t id_drink) ;
	uint8_t getStrength(uint8_t id_drink) ;
	String getName() ;

	void setQuantity(uint8_t id_drink, uint8_t quantity) ;
	void setStrength(uint8_t id_drink, uint8_t strength) ;
private:
	uint8_t m_quantity[NB_BOTTLE] ;
	uint8_t m_strength[NB_BOTTLE] ;
	String	m_name ;
};


extern Cocktails cocktailA ;
extern Cocktails cocktailB ;
extern Cocktails cocktailC ;
extern Cocktails cocktailD ;
extern Cocktails cocktailE ;
extern Cocktails cocktailF ;
extern Cocktails cocktailG ;
extern Cocktails cocktailH ;
