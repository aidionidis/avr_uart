/**
 * simpleUsart V 0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * Email: logan24.42@gmail.com
 * Licence: AS-IS
 * Microcontroller: avr family (tested on attiny2313)
 * 
 * Ultra-simple uart echo example
 *
 **/

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h" 
#undef F_CPU
#define F_CPU   8000000UL


int main( void )
{
	char c;
    
        init_usart();
    while(1)
	{        
		

        c=getc_usart();
         if (c)
         {
             if (c == 'a'){
                putstr_usart("It works!");
                c=0;
            }
            else{
                putc_usart(c);
            }
             
             c=0;
         }
	}

}                 

