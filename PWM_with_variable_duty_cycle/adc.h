/*
 * adc.h
 *
 * Created		: 17/07/2023 09:50:27
 * Author		: User
 * Description	: Analog-Digital Converter
 */ 


#ifndef ADC_H_
#define ADC_H_

static void 
initialize_adc (void)
{
	/*to enable ADC PRADC bit should be disabled in PRR*/
	
	/*ADC control and status register*/
	ADCSRA |= (1<<ADEN);	/*enable ADC*/
	ADCSRA |= (1<<ADIE);	/*enable ADC interrupts*/
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	/*set ADC clock prescaler to 128 (125kHz)*/
	
	/*ADC mux selection register*/
	ADMUX |= (1<<REFS0);	/*Vref=AVCC*/
	ADMUX |= (1<<MUX0);		/*select ADC1 as input channel*/
}

#endif /* ADC_H_ */