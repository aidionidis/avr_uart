/**
 * simpleUsart V 0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * Email: logan24.42@gmail.com
 * Licence: AS-IS
 * Microcontroller: avr family (tested on attiny2313)
 *
 **/
//Macros
#define BAUDRATE 9600
#define _FW_BAUDRATE ((F_CPU / (BAUDRATE * 16UL))-1)
#define LAST_OP_READ 1
#define LAST_OP_WRITE 2
#define TXSIZE 16
#define RXSIZE 16
#define BUFFSIZE 16

//Circular Buffer
volatile unsigned char tbuffer[TXSIZE];
volatile unsigned char rbuffer[RXSIZE];

volatile unsigned char t_buf_in;
volatile unsigned char t_buf_out;
volatile unsigned char t_last_op;  /*extra variable to know if the last operation was a read o write to the buffer
                                   in case that buf_end and buf_start are the same*/
volatile unsigned char r_buf_in;
volatile unsigned char r_buf_out;
volatile unsigned char r_last_op;

//Prototypes
void _fw_init_usart(void);
void _fw_putc_usart(unsigned char c);
unsigned char _fw_getc_usart(void);