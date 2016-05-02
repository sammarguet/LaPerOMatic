#include <LiquidCrystal.h>

// Define Push Button
#define BP1 23
#define BP2 25
#define BP3 27
#define BP4 29
#define BP5 31
#define BP6 33
#define BP7 35
#define BP8 37

#define BPH1 51
#define BPH2 47
#define BPH3 43
#define BPH4 39
#define BPH5 53
#define BPH6 49
#define BPH7 45
#define BPH8 41

// Define Pump

#define PM1 22
#define PM2 26
#define PM3 24
#define PM4 28
#define PM5 30
#define PM6 32
#define PM7 34
#define PM8 36

//Define LCD Screen
#define LCD_RS 44
#define LCD_EN 46
#define LCD_D4 42
#define LCD_D5 48
#define LCD_D6 50
#define LCD_D7 52

#define CATCH_PHRASE  "Salut a toi !"

//Define Time for each kind of glass in Milliseconds
#define TIME_SHOT     0
#define TIME_PONT     1
#define TIME_GOB      2
#define TIME_HALF     3
#define TIME_PINT     4
#define TIME_BOTTLE   5

/* ********************************************************************************
  For each pump, you will find a drink :
  1 : Pontarlier-Anis
  2 : Liqueur de Sapin
  3 : Rhum
  4 : 
  5 : Jus d'Ananas
  6 : Eau
  7 : NC
  8 : NC
            1   2   3   4   5   6   7   8               
********************************************************************************* */

//external void playRandom_A_and_N();

/* 6 different cocktails are programmable by the user 999 for random */
const int COCKTAILA[8]  {0    ,0    ,20   ,0    ,0    ,0    ,80   ,0    } ; // Anis
const int COCKTAILB[8]  {10   ,0    ,15   ,0    ,0    ,0    ,75   ,0    } ; // Anis Menthe
const int COCKTAILC[8]  {20   ,0    ,0    ,0    ,0    ,0    ,80   ,0    } ; // Menthe
const int COCKTAILD[8]  {0    ,30   ,0    ,0    ,0    ,0    ,70   ,0    } ; // Grenadine
const int COCKTAILE[8]  {10   ,0    ,0    ,0    ,0    ,20   ,70   ,0    } ; // Anis Grenadine
const int COCKTAILF[8]  {0    ,0    ,0    ,0    ,0    ,40   ,60   ,0    } ; // Rose
const int COCKTAILG[8]  {0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    } ; // Vide
const int COCKTAILH[8]  {0    ,0    ,0    ,0    ,20   ,0    ,80   ,0    } ; // Kiwi-banane
const int POMPES[8]   {PM1  ,PM2  ,PM3  ,PM4  ,PM5  ,PM6  ,PM7  ,PM8  } ; // POMPES
const int TIME_GLASS[6] {2500, 6700, 8000, 18500, 36000, 70000};
const String NAME_GLASS[6] {"un shot", "un verre a Pont", "un gobelet", "un demi", "une pinte", "une bouteille"};

bool occupied = true ;          // This boolean will block ISR when you're currently making a cocktail
bool manual = false ;           // This boolean mean Manual or automatic mode
unsigned int glass ;            // This is the size of the glass you are gonna drink
unsigned int drink_state = 0 ;  // This is the state you are currently executing
unsigned long time_now ;        // Time
unsigned long time_previous ;   // Time
  unsigned long time_spent ;    // Time
unsigned int glass_empty = 0 ;    // Number of glasses given
volatile int test = LOW ;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
/*
Startup function
*/
void setup() {
  // Serial link
  Serial.begin(9600);
  Serial.println(CATCH_PHRASE);
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print(CATCH_PHRASE);
  lcd.setCursor(0, 1);
  lcd.print("Un verre ?");

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
  
  // Set Interrupt for each Button
  attachInterrupt(BP1, GiveCocktailA, RISING);
  attachInterrupt(BP2, GiveCocktailB, RISING);
  attachInterrupt(BP3, GiveCocktailC, RISING);
  attachInterrupt(BP4, GiveCocktailD, RISING);
  attachInterrupt(BP5, GiveCocktailE, RISING);
  attachInterrupt(BP6, GiveCocktailF, RISING);
  //attachInterrupt(BP7, GiveCocktailG, RISING);
  attachInterrupt(BP8, GiveCocktailH, RISING);
  
  attachInterrupt(BP7, BiggerGlass, FALLING);
  
  attachInterrupt(BPH1, SetManual,  FALLING);
  attachInterrupt(BPH2, SetAuto,    FALLING);
  attachInterrupt(BPH3, PrintGlass, FALLING);
/*  attachInterrupt(BPH4, SmallerGlass, FALLING);
  attachInterrupt(BPH5, SmallerGlass, FALLING);
  attachInterrupt(BPH6, SmallerGlass, FALLING);
  attachInterrupt(BPH7, SmallerGlass, FALLING);
  attachInterrupt(BPH8, SmallerGlass, FALLING);*/
  
  
  glass = TIME_GOB ;   // Set Glass of Pont as default glass
  occupied = false ;    // Unlock system
  drink_state = 0 ;
}

void GiveCocktailA()
{
  if(!occupied)
    drink_state = 1 ;
}

void GiveCocktailB()
{
  if(!occupied)
    drink_state = 2 ;
}

void GiveCocktailC()
{
  if(!occupied)
    drink_state = 3 ; 
}

void GiveCocktailD()
{
  if(!occupied)
    drink_state = 4 ;
}

void GiveCocktailE()
{
  if(!occupied)
    drink_state = 5 ;
}

void GiveCocktailF()
{
  if(!occupied)
    drink_state = 6 ;
}

void GiveCocktailG()
{
  if(!occupied)
    drink_state = 7 ;
}

void GiveCocktailH()
{
  if(!occupied)
    drink_state = 8 ;
}

void GiveDrinks(const int *value)
{
  Serial.println(glass);
  lcd.begin(16, 2);
  lcd.clear() ;
  lcd.setCursor(0, 0) ;
  lcd.print("En Service") ;
  glass_empty ++ ;
  int state = 0 ;                 // Drink to serve
  int time_start = 0 ;
  time_start = millis() ;
  for(state = 0 ; state < 8 ; state ++)
  {
    Serial.print("State = ");
    Serial.print(value[state]);
    Serial.println(state);
    if(value[state]!=0)
    {
      digitalWrite(POMPES[state], LOW);
      time_previous = millis() ;
      while((millis() - time_previous) < value[state]*TIME_GLASS[glass]/100)
      {
        lcd.setCursor(0, 1);
        lcd.print(100*(millis() - time_start)/TIME_GLASS[glass]);
        lcd.print(" %");
      }
      digitalWrite(POMPES[state], HIGH) ;     
    }
  }
  drink_state = 0 ;
  Serial.println("End of Cocktail");
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print("Verre servi");
  lcd.print("100 %");
  delay(1000) ;
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(CATCH_PHRASE);
  lcd.setCursor(0, 1);
  lcd.print(NAME_GLASS[glass] + "?");
}

/*
  This function will give you a bigger glass, winner !
*/

void ChangeGlass(const bool bigger)
{
  occupied = true ;
  lcd.clear() ;
  lcd.setCursor(0, 0) ;
  lcd.print("Nouveau verre :") ;
  delay(500) ;
  if(bigger) {
    glass++;
    if(glass > 5) {
      glass = 0;
    }
  }
  lcd.setCursor(0, 1) ;
  lcd.print(NAME_GLASS[glass]) ;
  drink_state = 0 ;
  occupied = false ;
}

void BiggerGlass()
{
  if(!occupied)
    drink_state = 9 ;
}

/*
  This function will give you a smaller glass, pussy !
*/
/*void SmallerGlass()
{
  drink_state = 8 ;
}*/


void PrintGlass()
{
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(glass_empty);
  lcd.print(" verres servis");
}

void SetManual()
{
  manual = true ;
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print("Manuel");
}

void SetAuto()
{
  if(occupied==false)
    occupied = true ;
    manual = false ;
    lcd.clear() ;
    lcd.setCursor(0, 0);
    lcd.print("Auto");
    //delay(1000) ;
    occupied = false ;
}

/*
  This function will occurs in background
*/
void loop() {
  if(manual)
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
  else
    if(!occupied)
    {
      occupied = true ;               // Block other ISR
      /*__________TO DO______________*/
      // TODO playRandom_A_and_N();
      switch(drink_state){
        case 1 :
          GiveDrinks(COCKTAILA) ;
          break ;
        case 2 :
          GiveDrinks(COCKTAILB) ;
          break ;
        case 3 :
          GiveDrinks(COCKTAILC) ;
          break ;
        case 4 :
          GiveDrinks(COCKTAILD) ;
          break ;
        case 5 :
          GiveDrinks(COCKTAILE) ;
          break ;
        case 6 :
          GiveDrinks(COCKTAILF) ;
          break ;
        case 7 :
          GiveDrinks(COCKTAILG) ;
          break ;
        case 8 :
          GiveDrinks(COCKTAILH) ;
          break ;
        case 9:
          ChangeGlass(true);
        default :
          drink_state = 0 ;
          break ;
      }
      occupied = false ;               // Block other ISR
    }
}
