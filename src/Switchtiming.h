#ifndef Switchtiming_H					//verhindert mehrfachen Aufruf
#define Switchtiming_H
/************************************************************************
Title:    Switchtiming library 
Author:   Peter Lampe
Software: AVR-GCC 4.1
Hardware: alle ATMEG-Prozessoren, getestet auf ATMEGAx8
Inhalt:		diverse Routinen f�r Zeitverz�gerungen, Tastenabfragen und Tastenentprellung

Bemerkungen zum Gebrauch durch Peter Lampe:

dieses File ADC.h muss im Anwenderprogramm mit
#include "Switchtiming.h" eingetragen werden
das dazugeh�rige File Switchtiming.c wird wie folgt im MAKE-File eingetragen:

# List C source files here. (C dependencies are automatically generated.)
SRC = $(TARGET).c  Switchtiming.c

beide Files sollten als lokale Kopie im Projektordner liegen, sodass die Pfadangaben
entfallen und auch individuelle Anpassungen vorgenommen werden k�nnen. 
Zur Anwendung dieser Bibliothek siehe Test_Switchtiming.c

*/


#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif


//function prototypes
/*
_____________________________________________________________________________________________________________
Funktion:		unterbricht die Programmausf�hrung f�r den angegebenen Zeitraum in ms
R�ckgabewert:	keiner
Parameter 1:	Zeit in ms
*/
extern void wait_ms (unsigned int ms);

/*_____________________________________________________________________________________________________________
Funktion:		verz�gert die Programmausf�hrung um 7 Takte.
R�ckgabewert:	keiner
Parameter 1:	keiner
*/
extern void wait_clk7 (void);

/*_____________________________________________________________________________________________________________
Funktion:		verz�gert die Programmausf�hrung um 10 Takte.
R�ckgabewert:	keiner
Parameter 1:	keiner
*/
extern void wait_clk10 (void);

/*_____________________________________________________________________________________________________________
Funktion:		Fragt Taste auf L-Signal ab. Bei gedr�ckter Taste wird die Entprellzeit abgewartet 
				ansonsten sofort R�cksprung
R�ckgabewert:	1 bei erkanntem Tastendruck, 0 bei nichterkanntem Tastendruck
Parameter 1:	Zeiger auf Port, an dem sich der Schalter befindet
				im aufrufenden Programm wie folgt definieren:
				
				unsigned char *Portname;				//Zeiger deklarieren
				Portname=(unsigned char*) &PIND;	//Adresse zuweisen

Parameter 2:	Stelle, an der sich der Schalter befindet (0-7)
Parameter 3:	Verz�gerungszeit in ms (100ms optimal f�r Mikrotaster)
*/
extern unsigned char press_butten (volatile unsigned char *p, unsigned char position, unsigned int entprellzeit);

/*_____________________________________________________________________________________________________________
Funktion:		wartet bist Taste wieder losgelassen wird
R�ckgabewert:	keiner
Parameter 1:	Zeiger auf Port, an dem sich der Schalter befindet
				im aufrufenden Programm wie folgt definieren:
				
				unsigned char *Portname;				//Zeiger deklarieren
				Portname=(unsigned char*) &PIND;	//Adresse zuweisen

Parameter 2:	Stelle, an der sich der Schalter befindet (0-7)
Parameter 3:	Loslassen-Verz�gerungszeit in ms (100ms optimal f�r Mikrotaster)
*/
void hold_butten (unsigned char *p, unsigned char position, unsigned int entprellzeit);		
#endif 

