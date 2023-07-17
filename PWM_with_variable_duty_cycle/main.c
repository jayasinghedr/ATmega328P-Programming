/*
 * PWM_with_variable_duty_cycle.c
 *
 * Created		:	17/07/2023 09:29:30
 * Author		:	User
 * Description	:	A fast PWM waveform is generated at OC0A (PD6) pin of the ATmega328P.
 *					The duty cycle of the PWM can be adjusted from an analog voltage
 *					provided at ADC1 pin.
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "adc.h"
#include "pwm.h"

volatile uint16_t adc_val;

int main(void)
{
	initialize_adc();
	initialize_timer0_fast_pwm();
    
	sei();	/*enable global interrupts by setting I-bit in SREG*/
    
	while (1) 
    {
		/*start ADC conversion*/
		ADCSRA |= (1<<ADSC);
    }
}

ISR(ADC_vect)
{
	/*
	 * read the values from the ADC data registers
	 * reading ADCL first locks the access to data register until ADHC is read
	 */
	
	adc_val = ADCL + (ADCH<<8);
	
	_delay_us(200);	/*conversion time for ADC is about 13 ADC clock-cycles*/
}

ISR(TIMER0_COMPA_vect)
{
	/*
	 * update the value on the output compare register A with the value
	 * on the ADC pin. 10-bit ADC value is right shifted by 2 bits to
	 * fit in the 8-bit OCR0A register
	 */
	OCR0A = (adc_val >> 2);
}

