/**
 * simpleUsart V 0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * Email: logan24.42@gmail.com
 * Licence: AS-IS
 * Microcontroller: avr family (tested on attiny2313)
 *
 **/
 
//prototypes
#include "fw_usart.h"
#include <stdlib.h>

void init_usart(void);
char getc_usart(void);
char putc_usart(char c);
char putstr_usart(char* str);
void charToBin (unsigned char character, char* ret); /*function to return the binary decomposition of a char. 
                                                        Usefull for usart debugging*/