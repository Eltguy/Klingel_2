//************************************************************************************************************
//*                             			     Klingelschild 1.7					                                        
//*                                         für ATmega48												  	  												
//*                                      c 2014 by Peter Lampe												  											
//*                             Umsetzung auf Visual Studio Code 15.07.2025                                                                //
//************************************************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>

#ifndef F_CPU																
#define F_CPU 8000000UL											
#endif
#define Baud_Rate 9600UL										       //Baudrate UART für eventuelles Hardware-Debugging

#define AutoHold 1                                 //AutoHold-Pin PC1
#define ONTIME 30                                  //Nachlaufzeit [s]
                                                   //Betriebszeit Display = PIR-Laufzeit + ONTIME
volatile int TimeDelay = ONTIME;                   //Nachlaufzähler, initialisiert
//-------------------------------------------------------------------------------------------

int main(void)
{
  uint8_t i;                                        //allgemeine Laufvariable

  DDRC|=(1<<AutoHold);                              //AutoHold-Pin als Ausgang konfigurieren
  PORTC|=(1<<AutoHold);                             //und auf High setzen
  
  TCCR1A&=~((1<<WGM11)|(1<<WGM10));                 //Timer 1 im normalen Mode konfigurieren  
  TCNT1=0x85EE;                                     //Timer1 Preloading für 1s bei 8MHz
  TCCR1B|=(1<<CS12);                                //Prescaler = 256; Timer1 startet   
  
  sei();                                            //Interrupts global aktivieren
  TIMSK1|=(1<<TOIE1);                               //Timer1 Overflow Interrupt an, ISR scharf

  lcd_init(LCD_DISP_ON);									          //LCD initialisieren
  lcd_clrscr();														          //Display löschen Curser home
  
  while (1)                                         //in Endlosschleife:
  {
                                                    //1.Seite anzeigen
    lcd_puts("                 Willkommen bei\n");	//Text 1. Zeile
    lcd_puts("                ****************");		//Text 2. Zeile
   
    for (i=0; i<16; i++)                            //von rechts nach links scrollen
    {
      lcd_command(LCD_MOVE_DISP_LEFT);
      _delay_ms(30);                                //Scrollgeschwindigkeit
    }
  
    _delay_ms(3000);                                //Anzeigedauer
    lcd_clrscr();														        //Display löschen, Curser home
    

                                                    //2.Seite anzeigen
    lcd_command(LCD_HOME);												  //Cursor home
    lcd_puts("                  Martha & Max  \n");	//Text 1. Zeile 
    lcd_puts("                   Mustermann ");		  //Text 2. Zeile
   
    for (i=0; i<16; i++)
    {
      lcd_command(LCD_MOVE_DISP_LEFT);              //von rechts nach links scrollen
      _delay_ms(30);                                //Scrollgeschwindigkeit
    }
    _delay_ms(5000);                                //Anzeigedauer
    lcd_clrscr();													          //Display löschen Corser home
  }
}

//-------------------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)                        //Timer1 Overflow Interrupt Service Routine
{
  if (TimeDelay>0)                          //unterhalb der Nachlaufzeit?
  {                                         //ja, dann
     TimeDelay--;                           //Nachlaufzähler zurückzählen
     TCNT1=0x85EE;                          //Timer1 erneut für 1s laden
     TCCR1B|=(1<<CS12);                     //und wieder startet   
  }
  else                                      //nein, Zeit abgelaufen
  {                                         //dann
    PORTC&=~(1<<AutoHold);                  //AutoHold-Pin auf Low setzen, 
  }                                         //und damit Klingelschild abschalten
return;                                     //ISR verlassen (wird wohl nicht mehr ausgeführt)
}