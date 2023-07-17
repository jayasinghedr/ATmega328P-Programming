/*
 * pwm.h
 *
 * Created		:	17/07/2023 10:51:33
 * Author		:	User
 * Description	:	PWM Control
 */ 


#ifndef PWM_H_
#define PWM_H_

static void
initialize_timer0_fast_pwm (void)
{
	/*
	 * 8-bit Timer/Counter0 is used to generate PWM waveform
	 * to enable Timer0 the PRTIM0 bit must be disabled in PRR register
	 * Mode - Compare match output A, Fast PWM
	 */
	
	/*set DDR register for Timer0 mode A (OC0A -> PD6)*/
	DDRD |= (1<<PORTD6);
	
	/*Control registers*/
	TCCR0A |= (1<<COM0A1);	/*non-inverting fast PWM*/
	TCCR0A |= (1<<WGM01) | (1<<WGM00);	/*counts up to 0xFF*/
	TCCR0B |= (1<<CS01);	/*set Timer0 clock prescaler to 8 (7.81kHz)*/
	
	/*interrupt mask register*/
	TIMSK0 |= (1<<OCIE0A);	/*interrupt when TCNT0 = OCR0A*/ 
	
}

#endif /* PWM_H_ */