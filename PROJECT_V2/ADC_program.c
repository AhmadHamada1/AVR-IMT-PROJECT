/*
 * ADC_program.c
 *
 *  Created on: Dec 18, 2023
 *      Author: Hamo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include  "ADC_interface.h"
#include "ADC_register.h"


void ADC_Init (void)
{
CLR_BIT(ADMUX,REFS1);
SET_BIT(ADMUX,REFS0);

CLR_BIT(ADMUX,ADLAR);

SET_BIT(ADCSRA,ADPS0);
SET_BIT(ADCSRA,ADPS1);
SET_BIT(ADCSRA,ADPS2);

SET_BIT(ADCSRA,ADEN);

}

u16 ADC_Read (u8 Channel)
{
ADMUX=((ADMUX&0b11100000)|(Channel));

SET_BIT(ADCSRA,ADSC);

while(GET_BIT(ADCSRA,ADIF)==0);

SET_BIT(ADCSRA,ADIE);
return	ADC_Reg;

}
