
#define F_CPU   16000000
#define BUAD    9600
#define BRC     ((F_CPU/16/BUAD) - 1)
#define BUFFER_SIZE  128

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

char txBuffer[BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;
char rxBuffer[BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;




void appendSerial(char c)
{
	txBuffer[serialWritePos] = c;
	serialWritePos++;
	
	if(serialWritePos >= BUFFER_SIZE)
	{
		serialWritePos = 0;
	}
}



void serialWrite(char c[])
{
	for(uint8_t i = 0; i < strlen(c); i++)
	{
		appendSerial(c[i]);
	}
	
	if(UCSR0A & (1 << UDRE0))
	{
		UDR0 = 0;
	}
}



ISR(USART_TX_vect)
{
	if(serialReadPos != serialWritePos)
	{
		UDR0 = txBuffer[serialReadPos];
		serialReadPos++;
		
		if(serialReadPos >= BUFFER_SIZE)
		{
			serialReadPos++;
		}
	}
}


ISR(USART_RX_vect)
{
	rxBuffer[rxWritePos] = UDR0;
	
	rxWritePos++;
	
	if(rxWritePos >= BUFFER_SIZE)
	{
		rxWritePos = 0;
	}
}


char peekChar(void)
{
	char ret = '\0';
	
	if(rxReadPos != rxWritePos)
	{
		ret = rxBuffer[rxReadPos];
	}
	
	return ret;
}


char getChar(void)
{
	char ret = '\0';
	
	if(rxReadPos != rxWritePos)
	{
		ret = rxBuffer[rxReadPos];
		
		rxReadPos++;
		
		if(rxReadPos >= BUFFER_SIZE)
		{
			rxReadPos = 0;
		}
	}
	
	return ret;
}

int serial_read(void)
{
	UBRR0H = (BRC >> 8);
	UBRR0L =  BRC;
	
	UCSR0B = (1 << RXEN0)  | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	DDRB = (1 << PORTB0);
	
	sei();
	
	while(1)
	{
		char c = getChar();
		
		if(c == '1')
		{
			sbi(PORTB, PORTB0);
		}
		else if(c =='0')
		{
			cbi(PORTB, PORTB0);
		}
	}
}


int serial_write(void)
{
	UBRR0H = (BRC >> 8);
	UBRR0L =  BRC;
	
	UCSR0B = (1 << TXEN0)  | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	sei();
	
	serialWrite("HELLO\n\r");
	
	
	_delay_ms(1500);
	
	
	
	while(1)
	{
	}
}


void init_serial(){
	 
	 serial_write();
	 serial_read();
	 
	
}


int main(void)
{
    init_serial(); /* initialize serial port */
    //init_timer() ; /* initialize timer – for the bonus only */
    	while(1){
    
	    }
}

