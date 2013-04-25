/**
 * simpleUsart V 0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * Email: logan24.42@gmail.com
 * Licence: AS-IS
 * Microcontroller: avr family (tested on attiny2313)
 * 
 * simpleUsart is a non-blocking(interrupt driven) firmware and primitive layer for avr microcontrollers.
 * It is intended for ATtiny2313 but with little or no effort will work on any avr microcontroller.
 * simpleUsart implements a circular buffer to recive and put data in the uart data registry.
 *
 *
 * USAGE:
 * 1) Add usart.c and fw_usart.c to your makefile
 * 2) See example main.c
 * 3) Enjoy!
 *
 **/
#include <stdlib.h>
#include "usart.h"

char _usart_initialized = 0;

void init_usart(void)
{
    _fw_init_usart();
    _usart_initialized = 1; //sets global flag to 1 indicating an initialized USART peripheral
}

//*****************************************************************
//; getc_usart() gets a single character from usart firmware layer
//*****************************************************************
char getc_usart(void)
{
    if (_usart_initialized == 0){
        return -1;    
    }
    return _fw_getc_usart();

}
//*********************************************************************
//; putc_usart(char c) puts a single character to usart firmware layer
//*********************************************************************
char putc_usart(char c)
{
    if (_usart_initialized == 0){
        return -1;    
    }
    _fw_putc_usart(c);
    return 0;

}
//*********************************************************************************
//; putstr_usart(char* str) sends a null terminated string to usart firmware layer
//*********************************************************************************
char putstr_usart(char* str)
{
    int i=0;
    if (_usart_initialized == 0){
        return -1;    
    }   

    do
    {
        _fw_putc_usart( (char) str[i] );
    }while ((char)str[++i] != 0);
    return 0;
}


//****************************************************************************************************************************
//;charToBin (unsigned char character, char* ret) convert "character" to binary and saves it on "ret" buffer  (needs stdlib.h)
//****************************************************************************************************************************
void charToBin (unsigned char character, char* ret)
{
    itoa(character,ret,2);
}