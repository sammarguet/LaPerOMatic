#include "Cocktails.h"

Cocktails cocktailA(25   ,0    ,0    ,20   ,0    ,55   ,0    ,0    ) ;
Cocktails cocktailB(0    ,0    ,25   ,0    ,20   ,55   ,0    ,0    ) ;
Cocktails cocktailC(0    ,20   ,0    ,0    ,0    ,0    ,80   ,0    ) ;
Cocktails cocktailD(0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ) ;
Cocktails cocktailE(0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ) ;
Cocktails cocktailF(0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ) ;
Cocktails cocktailG(0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ) ;
Cocktails cocktailH(0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ) ;

Cocktails::Cocktails(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8)
{
	m_quantity[0] = d1 ;
	m_quantity[1] = d2 ;
	m_quantity[2] = d3 ;
	m_quantity[3] = d4 ;
	m_quantity[4] = d5 ;
	m_quantity[5] = d6 ;
	m_quantity[6] = d7 ;
	m_quantity[7] = d8 ;
}


Cocktails::~Cocktails(void)
{
}

uint8_t Cocktails::getQuantity(uint8_t id_drink)
{
	return m_quantity[id_drink] ;
}

uint8_t Cocktails::getStrength(uint8_t id_drink)
{
	return m_strength[id_drink] ;
}

void Cocktails::setQuantity(uint8_t id_drink, uint8_t quantity)
{
	m_quantity[id_drink] = quantity ;
}

void Cocktails::setStrength(uint8_t id_drink, uint8_t strength)
{
	m_strength[id_drink] = strength ;
}

String Cocktails::getName()
{
	return m_name ;
}