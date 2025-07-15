/**
 *************************************************************************************************************
 **                                                                                                          
 **                              	Swichtiming                                    
 **                              V1.0   12072009
 **			           Switchtiming-Library									
 **                         c 2009 by Peter Lampe												  
 **                                                                                                       
 *************************************************************************************************************/
 
#include <avr/io.h>									//Standard Ein-/Ausgabebibliothek
//#include "Switchtiming.h"
//________________________________________________________________________________________________________________
//wartet die angegebene Zeit in Millisekunden


void wait_ms (unsigned int ms)						

{
unsigned int counter;								//Laufvariable, um 1ms zu erzeugen
//return;											//nur zum Debuggen �berspringen
 while(ms)											//1ms Zeitschleife, wird bei 0ms �berbr�ckt
    {
		
		
		counter=8000000UL / 10000;						//Berechnung der Schleifenvariable f�r 1ms
            while(counter)
            {
                asm volatile("nop");				//zur Verzögerung NOP-Befehl in Assembler einf�gen
                counter--;							//Schleifenzähler dekrementieren
            }
        ms--;										//ms-Schleife dekrementiern
    }
}
//________________________________________________________________________________________________________________
//wartet 7 Takte

void wait_clk7 (void)						

{
return;
}

//________________________________________________________________________________________________________________
//wartet 10 Takte

void wait_clk10 (void)						

{
asm volatile("nop");
asm volatile("nop");
asm volatile("nop");
}


//________________________________________________________________________________________________________________
//Fragt Taste auf L-Signal ab. Bei gedrückter Taste wird die Entprellzeit abgewartet und 1 zurückgegeben
//Ist Taste nicht gedrückt, dann sofort Rücksprung mit 0 als Rückgabe

unsigned char press_butten (unsigned char *p, unsigned char position, unsigned int entprellzeit)						

{
if (!(*p & (1<<position)))			//wenn Taste gedr�ckt
	{
	wait_ms(entprellzeit);
	return 1;
	}
else return 0;
}

//________________________________________________________________________________________________________________
//wartet solange, bis Taste wieder losgelassen wird und entprellt das Loslassen

void hold_butten (unsigned char *p, unsigned char position, unsigned int entprellzeit)						

{
while (!(*p & (1<<position)))								//Loslassen abwarten
		wait_ms(entprellzeit);
}


    
