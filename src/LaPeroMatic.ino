/*
 Name:		LaPeroMatic.ino
 Created:	25/10/2016 20:18:43
 Author:	Samuel Marguet
*/

#include "LaPeroMatic.h"
#include "Barman.h"

uint8_t currentState ;  // This is the state you are currently executing

void pressedButton1()
{
	if(!Suzette.getisOccupied())
		currentState = 1 ;
}

void pressedButton2()
{
	if(!Suzette.getisOccupied())
		currentState = 2 ;
}

void pressedButton3()
{
	if(!Suzette.getisOccupied())
		currentState = 3 ; 
}

void pressedButton4()
{
	if(!Suzette.getisOccupied())
		currentState = 4 ;
}

void pressedButton5()
{
	if(!Suzette.getisOccupied())
		currentState = 5 ;
}

void pressedButton6()
{
	if(!Suzette.getisOccupied())
		currentState = 6 ;
}

void pressedButton7()
{
	if(!Suzette.getisOccupied())
		currentState = 7 ;
}

void pressedButton8()
{
	if(!Suzette.getisOccupied())
		currentState = 8 ;
}

void pressedHideButton1()
{
	if(!Suzette.getisOccupied())
		currentState = 9 ;
}

void pressedHideButton2()
{
	if(!Suzette.getisOccupied())
		currentState = 10 ;
}

void pressedHideButton3()
{
	if(!Suzette.getisOccupied())
		currentState = 11 ;
}

void pressedHideButton4()
{
	if(!Suzette.getisOccupied())
		currentState = 12 ;
}

void pressedHideButton5()
{
	if(!Suzette.getisOccupied())
		currentState = 13 ;
}

void pressedHideButton6()
{
	if(!Suzette.getisOccupied())
		currentState = 14 ;
}

void pressedHideButton7()
{
	if(!Suzette.getisOccupied())
		currentState = 15 ;
}

void pressedHideButton8()
{
	if(!Suzette.getisOccupied())
		currentState = 16 ;
}

/*
Startup function
*/
void setup() {
  // Serial link
	Serial.begin(9600);
	Serial.println(CATCH_PHRASE);
	// Set GPIO Push Button as input
	pinMode(BP1, INPUT);
	pinMode(BP2, INPUT);
	pinMode(BP3, INPUT);
	pinMode(BP4, INPUT);
	pinMode(BP5, INPUT);
	pinMode(BP6, INPUT);
	pinMode(BP7, INPUT);
	pinMode(BP8, INPUT);
	pinMode(BPH1, INPUT);
	pinMode(BPH2, INPUT);
	pinMode(BPH3, INPUT);
	pinMode(BPH4, INPUT);
	pinMode(BPH5, INPUT);
	pinMode(BPH6, INPUT);
	pinMode(BPH7, INPUT);
	pinMode(BPH8, INPUT);
  	// Set Interrupt for each Button
	attachInterrupt(BP1, pressedButton1, RISING);
	attachInterrupt(BP2, pressedButton2, RISING);
	attachInterrupt(BP3, pressedButton3, RISING);
	//attachInterrupt(BP4, pressedButton4, RISING);
	//attachInterrupt(BP5, pressedButton5, RISING);
	//attachInterrupt(BP6, pressedButton6, RISING);
	//attachInterrupt(BP7, pressedButton7, RISING);
	attachInterrupt(BP8, pressedButton8, RISING);
  
	attachInterrupt(BPH1,	pressedHideButton1,	FALLING);
	attachInterrupt(BPH2,	pressedHideButton2,	FALLING);
	attachInterrupt(BPH3,	pressedHideButton3,	FALLING);
	//attachInterrupt(BPH4, pressedHideButton4, FALLING);
	//attachInterrupt(BPH5, pressedHideButton5, FALLING);
	//attachInterrupt(BPH6, pressedHideButton6, FALLING);
	//attachInterrupt(BPH7, pressedHideButton7, FALLING);
	//attachInterrupt(BPH8, pressedHideButton8, FALLING);
  
	Suzette.setisOccupied(false) ;
	currentState = 0 ;
}

void setManAuto()
{
	Suzette.setManAuto() ;
}

void printTotalGlasses()
{
	Suzette.printTotalGlasses() ;
}

void GiveDrinks(const Cocktails cocktail)
{

}



void loop() {

	if( !Suzette.getisOccupied() )
	{
		Suzette.setisOccupied(true) ;               // Block other ISR
		switch(currentState){
		case 1 :
			GiveDrinks(cocktailA) ;
			currentState = 0 ;
			break ;
        case 2 :
			GiveDrinks(cocktailB) ;
			currentState = 0 ;
			break ;
        case 3 :
			GiveDrinks(cocktailC) ;
			currentState = 0 ;
			break ;
        case 4 :
			GiveDrinks(cocktailD) ;
			currentState = 0 ;
			break ;
        case 5 :
			GiveDrinks(cocktailE) ;
			currentState = 0 ;
			break ;
        case 6 :
			GiveDrinks(cocktailF) ;
			currentState = 0 ;
			break ;
        case 7 :
			GiveDrinks(cocktailG) ;
			currentState = 0 ;
			break ;
        case 8 :
			//GiveDrinks(cocktailH) ;
			Suzette.setbiggerGlass() ;
			currentState = 0 ;
			break ;
        case 9:
			setManAuto() ;
			currentState = 0 ;
			break ;
        case 10:
			printTotalGlasses() ;
			currentState = 0 ;
			break ;
        default :
			currentState = 0 ;
			break ;
		}
		Suzette.setisOccupied(false) ;              // Block other ISR
	}
}

