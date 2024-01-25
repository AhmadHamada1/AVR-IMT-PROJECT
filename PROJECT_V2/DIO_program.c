/*****************************************************************/
/* Author  : Ahmed Hamada                                                */
/* SWC     : DIO                                                 */
/* Version : 1.0                                                 */
/* Date    : 07 Dec 2023                                         */
/*****************************************************************/
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

void DIO_voidInit(void)
{

DDRA=CONCAT(DIO_PIN_NUM_A7_DIR,DIO_PIN_NUM_A6_DIR,DIO_PIN_NUM_A5_DIR,DIO_PIN_NUM_A4_DIR,DIO_PIN_NUM_A3_DIR,DIO_PIN_NUM_A2_DIR,DIO_PIN_NUM_A1_DIR,DIO_PIN_NUM_A0_DIR);
DDRB=CONCAT(DIO_PIN_NUM_B7_DIR,DIO_PIN_NUM_B6_DIR,DIO_PIN_NUM_B5_DIR,DIO_PIN_NUM_B4_DIR,DIO_PIN_NUM_B3_DIR,DIO_PIN_NUM_B2_DIR,DIO_PIN_NUM_B1_DIR,DIO_PIN_NUM_B0_DIR);
DDRC=CONCAT(DIO_PIN_NUM_C7_DIR,DIO_PIN_NUM_C6_DIR,DIO_PIN_NUM_C5_DIR,DIO_PIN_NUM_C4_DIR,DIO_PIN_NUM_C3_DIR,DIO_PIN_NUM_C2_DIR,DIO_PIN_NUM_C1_DIR,DIO_PIN_NUM_C0_DIR);
DDRD=CONCAT(DIO_PIN_NUM_D7_DIR,DIO_PIN_NUM_D6_DIR,DIO_PIN_NUM_D5_DIR,DIO_PIN_NUM_D4_DIR,DIO_PIN_NUM_D3_DIR,DIO_PIN_NUM_D2_DIR,DIO_PIN_NUM_D1_DIR,DIO_PIN_NUM_D0_DIR);
}

void DIO_voidWritePin(u8 u8PortCpy ,u8 u8PinCpy,u8 u8ValueCpy)
{
	switch(u8PortCpy)
	{
	case PORT_A:
		if(u8ValueCpy==DIO_HIGH){
			SET_BIT(PORTA,u8PinCpy);
		}
		else
			CLR_BIT(PORTA,u8PinCpy);

		break;
	case PORT_B:
		if(u8ValueCpy==DIO_HIGH){
			SET_BIT(PORTB,u8PinCpy);
		}
		else
			CLR_BIT(PORTB,u8PinCpy);
		break;
	case PORT_C:
		if(u8ValueCpy==DIO_HIGH){
			SET_BIT(PORTC,u8PinCpy);
		}
		else
			CLR_BIT(PORTC,u8PinCpy);
		break;
	case PORT_D:
		if(u8ValueCpy==DIO_HIGH){
			SET_BIT(PORTD,u8PinCpy);
		}
		else
			CLR_BIT(PORTD,u8PinCpy);
		break;
	}

}
u8 DIO_u8ReadPin(u8 u8PortCpy ,u8 u8PinCpy)
{
	u8 u8PinVal ;

	switch(u8PortCpy)
	{
	case PORT_A :
		u8PinVal=GET_BIT(PINA,u8PinCpy);
		break;

	case PORT_B :
		u8PinVal=GET_BIT(PINB,u8PinCpy);
		break;
	case PORT_C :
		u8PinVal=GET_BIT(PINC,u8PinCpy);
		break;
	case PORT_D :
		u8PinVal=GET_BIT(PIND,u8PinCpy);
		break;

	}
	return u8PinVal;

}

void DIO_voidTogglePin(u8 u8PortCpy ,u8 u8PinCpy)
{
	switch(u8PortCpy)
	{
	case PORT_A:
		TOG_BIT(PORTA,u8PinCpy);
		break;
	case PORT_B:
		TOG_BIT(PORTB,u8PinCpy);
		break;
	case PORT_C:
		TOG_BIT(PORTC,u8PinCpy);
		break;
	case PORT_D:
		TOG_BIT(PORTD,u8PinCpy);
		break;


	}

}

void DIO_voidWritePort(u8  u8PortCpy,u8 u8ValueCpy)
{
	switch(u8PortCpy)
	{
	case PORT_A :
		PORTA=u8ValueCpy;
		break;
	case PORT_B :
			PORTB=u8ValueCpy;
			break;
	case PORT_C :
			PORTC=u8ValueCpy;
			break;
	case PORT_D :
			PORTD=u8ValueCpy;
			break;
	}


}

void DIO_voidPullUpState(u8  u8PortCpy,u8 u8PinCpy,u8 u8state)
{
	//check if input or output
	u8 u8Direction_status;
	switch(u8PortCpy)
		{
		case PORT_A:
			u8Direction_status=GET_BIT(DDRA,u8PinCpy);
			break;
		case PORT_B:
			u8Direction_status=GET_BIT(DDRB,u8PinCpy);
			break;
		case PORT_C:
			u8Direction_status=GET_BIT(DDRC,u8PinCpy);
			break;
		case PORT_D:
			u8Direction_status=GET_BIT(DDRD,u8PinCpy);
			break;
		}
if (u8Direction_status ==DIO_INPUT)
{
	DIO_voidWritePin(u8PortCpy,u8PinCpy,u8state);
}else {
	//DO NOTHING
}

}
