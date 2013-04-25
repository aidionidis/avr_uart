
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
