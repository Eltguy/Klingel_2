//************************************************************************************************************
//*                             			     Klingelschild 1.6					                                        
//*                                         für ATmega48												  	  												
//*                                      c 2014 by Peter Lampe												  											
//*                             Umsetzung auf Visual Studio Code 15.07.2025                                                                //
//************************************************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include "Switchtiming.h"

#ifndef F_CPU																
#define F_CPU 8000000UL											
#endif
#define Baud_Rate 9600UL										        //Baudrate UART für eventuelles Hardware-Debugging

int main(void)
{
  unsigned char i;

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
      wait_ms (50);
    }
    wait_ms (5000);
    /*for (i=0; i<16; i++)
    {
      lcd_command(LCD_MOVE_DISP_LEFT);
      wait_ms (50);
    }*/
    lcd_clrscr();														        //Display löschen, Curser home
    
    lcd_puts("                *  Eva & Peter *\n");	//Text 1. Zeile
    lcd_puts("                *     Lampe    *");		//Text 2. Zeile
   
    for (i=0; i<16; i++)
    {
      lcd_command(LCD_MOVE_DISP_LEFT);
      wait_ms (50);
    }
    wait_ms (10000);
    /*for (i=0; i<16; i++)
    {
      lcd_command(LCD_MOVE_DISP_LEFT);
      wait_ms (50);
    }*/
    lcd_clrscr();													          //Display löschen Corser home
  }
}













void wait_until_key_pressed(void)
{
  unsigned char temp1, temp2;
  unsigned int i;
  
  do {
    temp1 = PINB;                  // read input
    for(i=0;i<65535;i++);
    temp2 = PINB;                  // read input
    temp1 = (temp1 & temp2);       // debounce input
  } while ( temp1 & _BV(PINB2) );
  
  loop_until_bit_is_set(PINB,PINB2);            /* wait until key is released */
}