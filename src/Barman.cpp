#include "Barman.h"

Barman::Barman(void)
{
	m_isManual		= false ;
	m_isOccupied	= true ;
	m_sizeGlass		= TIME_PONT ;
	m_totalGlasses	= 0 ;

	// Set GPIO Pump as output
	pinMode(PM1, OUTPUT);
	pinMode(PM2, OUTPUT);
	pinMode(PM3, OUTPUT);
	pinMode(PM4, OUTPUT);
	pinMode(PM5, OUTPUT);
	pinMode(PM6, OUTPUT);
	pinMode(PM7, OUTPUT);
	pinMode(PM8, OUTPUT);
  
	// Set GPIO pump as Off
	digitalWrite(PM1, HIGH);
	digitalWrite(PM2, HIGH);
	digitalWrite(PM3, HIGH);
	digitalWrite(PM4, HIGH);
	digitalWrite(PM5, HIGH);
	digitalWrite(PM6, HIGH);
	digitalWrite(PM7, HIGH);
	digitalWrite(PM8, HIGH);

  	lcd.setStarterScreen(m_nameGlass[m_sizeGlass]) ;
}

Barman::~Barman(void)
{
}

void Barman::setManAuto(void)
{
	if(!getisOccupied())
	{
		m_isOccupied = true ;
		m_isManual = !m_isManual ;
		lcd.clear() ;
		lcd.setCursor(0, 0);
		if(m_isManual)
			lcd.print(MANUAL);
		else
			lcd.print(AUTO);
		m_isOccupied = false ;
	}
}

void Barman::printTotalGlasses(void)
{
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(m_totalGlasses);
  lcd.print(" verres servis");
}

void Barman::work(void)
{
	if(m_isManual)
	{
		digitalWrite(PM1, !digitalRead(BP1)) ;
		digitalWrite(PM2, !digitalRead(BP2)) ;
		digitalWrite(PM3, !digitalRead(BP3)) ;
		digitalWrite(PM4, !digitalRead(BP4)) ;
		digitalWrite(PM5, !digitalRead(BP5)) ;
		digitalWrite(PM6, !digitalRead(BP6)) ;
		digitalWrite(PM7, !digitalRead(BP7)) ;
		digitalWrite(PM8, !digitalRead(BP8)) ;
	}
}

void Barman::giveDrink(Cocktails &cocktail)
{
	uint8_t state = 0 ;
	uint32_t time_previous ;
	m_totalGlasses ++ ;
	lcd.setStartService( cocktail.getName() ) ;
	uint32_t time_start = millis() ;
	for(state = 0 ; state < 8 ; state ++)
	{
		if(cocktail.getQuantity(state)!=0)
		{
			digitalWrite(m_pmp[state], LOW);
			time_previous = millis() ;
			while((millis() - time_previous) < cocktail.getQuantity(state)*m_timeGlass[m_sizeGlass]/100)
			{
				lcd.setCursor(0, 1);
				lcd.print(100*(millis() - time_start)/m_timeGlass[m_sizeGlass]);
				lcd.print(" %");
			}
			digitalWrite(m_pmp[state], HIGH) ;     
		}
	}
	lcd.setEndOfService() ;
	lcd.setStarterScreen(m_nameGlass[m_sizeGlass]) ;
}

bool Barman::getisOccupied(void)
{
	return m_isOccupied ;
}

void Barman::setisOccupied(bool isOccupied)
{
	m_isOccupied = isOccupied ;
}

void Barman::setbiggerGlass(void)
{
	m_isOccupied = true ;
	m_sizeGlass++;
	if(m_sizeGlass > 5)
	{
		m_sizeGlass = 0;
    }
	m_isOccupied = false ;
}

Barman Suzette ;