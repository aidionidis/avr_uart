/**
 * simpleUsart V 0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * Email: logan24.42@gmail.com
 * Licence: AS-IS
 * Microcontroller: avr family (tested on attiny2313)
 *
 **/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "fw_usart.h"
//#define DEBUG_USART

ISR (USART_RX_vect)
{
    char recivedByte;
    recivedByte = UDR;
    rbuffer[r_buf_in] = recivedByte;
    r_buf_in = ( (r_buf_in+1) % RXSIZE); //Updates input pointer of the RX buffer.  
                                         //No black magic here, if you need help with circular buffers, check the wikipedia article.
    #ifdef DEBUG_USART
        _fw_putc_usart('q');
    #endif
}

ISR (USART_UDRE_vect)
{
    if (t_buf_in != t_buf_out) /* Checks if transmit buffer is not empty.
                                (NOTE: in this condition, buffer could be full, but we only care for a buffer empty condition).*/
        {
            UDR = tbuffer[t_buf_out]; //load the transmit shift register with corresponding byte.
            t_buf_out = ( (t_buf_out+1) % TXSIZE); //increment circular buffer OUT pointer by 1.
        }
    else
        {
			//If no data as been writen to UDR, we need to disable UDRE interrupt manually.
            UCSRB &= ~(1<<UDRIE);            
        }
}

//************************************************************
//; _fw_usart_init() initialize USART circuitry and buffers
//************************************************************
void _fw_init_usart(void)
{
    //initialize circular buffers
    t_buf_out = r_buf_out = t_buf_in = r_buf_in = 0;
    t_last_op = r_last_op = 0;      
    
    UBRRH = (_FW_BAUDRATE >> 8);			//Load baudrate (see _fw_usart.h)
    UBRRL = (_FW_BAUDRATE);
    UCSRC |= ((1<<UCSZ0) | (1<<UCSZ1));		//8 Bit data, 1 bit stop, no parity.
    UCSRB |= ( (1 << RXEN) | (1 << TXEN) );	//Enable Tx and Rx circuitry.
    UCSRB |= (1 << RXCIE);					//Enable Rx complete interrupt. (UDR empty interrupt will be enabled in putc routine)
    sei();									//Enable global interrupts
} 

//*****************************************************************
//;_fw_getc_usart() gets a single character from reception buffer
//*****************************************************************
unsigned char _fw_getc_usart(void)
{
    char c;
    if (r_buf_in != r_buf_out) //If reception buffer not empty...
    {
        c = rbuffer[r_buf_out];
		r_last_op = LAST_OP_READ;
		r_buf_out = ((r_buf_out + 1) % RXSIZE);
        #ifdef DEBUG_USART
            _fw_putc_usart('i');
        #endif
		return c;
    }
    else
    {
        return 0;
    }

}
//*****************************************************************
//;_fw_putc_usart() puts a single character to transmission buffer
//*****************************************************************

void _fw_putc_usart(unsigned char c)
{
	tbuffer[t_buf_in] = c;
	
	t_last_op = LAST_OP_WRITE;
	t_buf_in = ((t_buf_in + 1) % TXSIZE);
		
	UCSRB |= (1 << UDRIE);  //enable UDR empty interrupt.
}