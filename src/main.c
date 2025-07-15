//************************************************************************************************************
//*                             			     Klingelschild 1.7					                                        
//*                                         für ATmega48												  	  												
//*                                      c 2014 by Peter Lampe												  											
//*                             Umsetzung auf Visual Studio Code 15.07.2025                                                                //
//************************************************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

#ifndef F_CPU																
#define F_CPU 8000000UL											
#endif
#define Baud_Rate 9600UL										        //Baudrate UART für eventuelles Hardware-Debugging

int main(void)
{
  unsigned char i;                                  //allgemeine Laufvariable

  lcd_init(LCD_DISP_ON);									          //LCD initialisieren
  lcd_clrscr();														          //Display löschen Curser home
  while (1)
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