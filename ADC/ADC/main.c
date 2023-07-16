/*
 * ADC.c
 *
 * Created		:	16/07/2023 12:31:43
 * Author		:	User
 * Description	:	Using Analog-Digital Converter (ADC)
					An analog voltage is read on the ADC1 pin and then an LED 
					connected to PB2 pin is turned on if the voltage is above
					a given threshold value 
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define THRESHOLD 800

volatile uint16_t reg1, reg2, adc_val;

int main(void)
{
	DDRB = (1 << PORTB2);	/*configure PB2 as output (LED)*/
	
	/*
	initialize the ADC
	*/
	
	PRR &= ~(1 << PRADC);	/*disable Power Reduction ADC bit*/
	
	ADCSRA |= (1 << ADEN);	/*enable ADC (ADC control and status reg)*/

	/*enable ADC interrupts*/
	ADCSRA |= (1 << ADIE);
	
	/*enable prescaler for ADC clock*/
	ADCSRA |= 0b00000111; /*prescaler = 128*/
	
	/*select ADC Vref = AVcc*/
	ADMUX |= 0b01000000;	/* REFS1 = 0, REFS0 = 1 */
		
	/*select ADC0 as input channel*/
	ADMUX |= 0b00000001;	/* MUX3 = 0, MUX2 = 0, MUX1 = 0, MUX0 = 1 */
	
	sei();	/*enable global interrupts by setting I-bit in SREG*/
	
	while (1)
	{	
		/*start ADC conversion*/
		ADCSRA |= (1 << ADSC);	
	}
}

ISR(ADC_vect)
{
	/*
	Read the values from the data registers
	ADCL is read first (it locks the data register until ADCH is read) 
	*/
	reg1 = ADCL;	/*lower 8-bits*/
	reg2 = ADCH;	/*upper 2-bits*/
	adc_val = (reg2 << 8) + reg1;	/*10-bit ADC output*/
	
	if (adc_val >= THRESHOLD) {
		PORTB |= (1 << PORTB2);
	}
	else if (adc_val < THRESHOLD) {
		PORTB &= ~(1 << PORTB2);
	}
	_delay_us(500);
}

