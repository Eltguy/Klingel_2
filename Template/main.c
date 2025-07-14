/*
Titel     : AVR_native - Testprogramm/Template
--------------------------------------------------------------------------------------
Funktion  : zur Verwendung als Template für reine C-Programmierung von AVR-MCUs
            und Upload per USBasp. Entsprechende Einstellungen sind in der PlatformIO.ini
            bereits vorgenommen. Damit kann eine komfortable Programmierung unter
            VSCode/PlatformIO erfolgen und Microchip Sudio wird damit überflüssig.
  
Schaltung : keine
--------------------------------------------------------------------------------------
Prozessor : entsprechend Einstellung in der Platformio.ini
Datum     : 09.06.2025
Version   : 1.0
Autor     : c 2025 by Peter Lampe
*/

#ifndef F_CPU											//wenn nicht schon anderweitig definiert,
#define F_CPU 8000000UL						//dann F_CPU hier sauber definieren
#endif
#define UART_BAUD_RATE 9600UL

//------------------- verwendete Header-Files einbinden-------------------------------
#include  <avr/io.h>						  //device specific I/O definitions
//#include 	<stdint.h>				  		//Standard Integer Types
//#include 	<stdlib.h>				  		//General utilities
//#include 	<string.h>				  		//Strings
//#include 	<math.h>				  		  //Mathematics
//#include 	<stdio.h>				  		  //Standard IO facilities
#include  <avr/interrupt.h>				//Interruptbearbeitung
//#include 	<avr/eeprom.h>					//EEPROM-Zugriff
//#include 	<avr/sleep.h>					  //sleep modes
//#include 	<avr/wdt.h>						  //Watchdog timer handling
#include  <util/delay.h>					//Convenience functions for busy-wait delay loops
#include  <uart.h>                //eigene UART-Bibliothek einbinden (siehe /INCLUDE)
//#include	<ADC.h>							    //eigene ADC-Bibliothek einbinden (siehe /INCLUDE)

//------------------------------------ Defines ---------------------------------------

//------------------------------------ globale Variablen -----------------------------

//--------------------------------------- Prototypes ---------------------------------

//***************************** Hauptprogramm ****************************************
int main (void)
{
  /*																									//UART initialisieren  
	char buffer[5];										                  //Puffer zur Umwandlung Integer->String <stdlib.h>
  unsigned int Wert = 12345;
  unsigned char Basisadresse = 72;                    //Basisadresse ADC, Pin ADDR auf GND
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));	//Initialisierung UART
  sei();												                      //Interruptfreigabe für UART <avr/interrupt.h>
  uart_puts("UART funktioniert\r");
  itoa(Wert, buffer, 10);
  uart_puts(buffer);
	
																				              //Port initialisieren
	DDRC&= ~(1<<SWITCH);  								              //Eingang initialisieren
  PORTC|= (1<<SWITCH);  								              //Pullup an Tastereingang setzen
  DDRC|= ((1<<LED)|(1<<REL));						              //Ausgänge initialisieren
  
	if (!(PINC &(1<<SWITCH)))					  	              //Taster gedrückt?
    {
     PORTC^= ((1<<LED)|(1<<REL)|(1<<MUTE));		        //ja, dann LED/Relais/Muting umschalten
	   while (!(PINC &(1<<SWITCH)))				              //wartet solange, bis Taster losgelassen wird
	   _delay_ms(10);	                                  //Entprell-Verzögerung beim loslassen des Tasters
	  }

	*/ 
    
  
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));	    //Initialisierung UART
  sei();												                          //Interruptfreigabe f�r UART <avr/interrupt.h>
    
 while(1)
 {
  uart_puts("*********************************** \n");    //formatierte Ausgabe auf Terminal
  uart_puts("* AVR_native unter PlatformIO :-) * \n");      
  uart_puts("*********************************** \n \n");
  _delay_ms(3000);
 }

  return 0;
}

//************************************************************************************

//***************************** Functions intern *************************************

//***************************** Interrupt-Handler ************************************

/*
//------------------------------------------------------------------------------------
ISR(INT0_vect)					  //External Interrupt Request 0
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(INT1_vect)					  // External Interrupt Request 1
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(PCINT0_vect)					// Pin Change Interrupt Request 0
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(PCINT1_vect)					// Pin Change Interrupt Request 1
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(WDT_vect)					    // Watchdog Time-out Interrupt
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(PCINT2_vect)					// Pin Change Interrupt Request 2
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIM2_COMPA_vect)			// Timer/Counter2 Compare Match A
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIM2_COMPB_vect)			// Timer/Counter2 Compare Match B
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER2_OVF_vect)			// Timer/Counter2 Overflow
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER1_CAPT_vect)			// Timer/Counter1 Capture Event
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)		// Timer/Counter1 Compare Match A
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER1_COMPB_vect)		// Timer/Counter1 Compare Match B
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)		 	// Timer/Counter1 Overflow
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIM0_COMPA_vect)			// Timer/Counter0 Compare Match A
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIM0_COMPB_vect)			// Timer/Counter0 Compare Match B
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)			// Timer/Counter0 Overflow
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(SPI_STC_vect)				  // Serial Transfer Complete
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(USART_RXC_vect)				// USART, Rx Complete
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(USART_UDRE_vect)			// USART Data Register Empty
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(USART_TXC_vect)				// USART, Tx Complete
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(ADC_vect)					    // ADC Conversion Complete
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(EE_RDY_vect)				  // EEPROM Ready
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(ANA_COMP_vect)				// Analog Comparator
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(TWI_vect)					    // 2-wire Serial Interface
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
ISR(SPM_RDY_vect)				  // Store Program Memory Ready
{
}
//------------------------------------------------------------------------------------
*/