/*****************************************************************/
/* Author  : ahmed saeed                                         */
/* Layer   : MCAL                                                */
/* SWC     : TIMER0                                              */
/* Version : 1.0                                                 */
/* Date    : 16 Aug 2023                                         */
/*****************************************************************/
#include "BIT_Math.h"
#include "STD_Types.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

pf TIM0_pfOVFCallBack=NULL_PTR;
pf TIM0_pfCmpCallBack=NULL_PTR;





void TIM0_voidInit(void)
{
#if TIMO_MODE == TIM0_NORMAL
	 CLR_BIT(TCCR0, 6);
	    CLR_BIT(TCCR0, 3);
	    // Clear WGM01 and WGM00 for normal mode
	    CLR_BIT(TCCR0, 1);
	    CLR_BIT(TCCR0, 0);
#elif  TIMO_MODE == TIM0_CTC
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#elif  TIMO_MODE == TIM0_FAST_PWM
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#elif  TIMO_MODE == TIM0_PHASE_PWM
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/* set normal if there is no selection*/
#else
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
#endif

#if TIMO_WAVE == TIM0_TOGL_OC0
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_CLEAR_OC0
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_SET_OC0
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_FAST_INVERT_OC0
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_FAST_NONINVERT_OC0
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_PHASE_INVERT_OC0
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMO_WAVE == TIM0_PHASE_NONINVERT_OC0
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	/*default is oco dicdonnected */
#else
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);

#endif



}
/* used to enable and update presclar */




void TIM0_voidEnable(u8 u8PreScaler)
{
	TCCR0=TCCR0&0b11111000;
	TCCR0=TCCR0|u8PreScaler;
}


void TIM0_voidDisable(void)
{
	TCCR0=TCCR0&0b11111000;
}

void TIM0_voidEnableOvfINt(void)
{
	SET_BIT(TIMSK,0);
}

void TIM0_voidDisableOvfINt(void)
{
	CLR_BIT(TIMSK,0);
}

void TIM0_voidEnableComparINt(void)
{
	SET_BIT(TIMSK,1);

}

void TIM0_voidDisableCompareINt(void)
{
	CLR_BIT(TIMSK,1);
}


void TIM0_voidSetTCNTValue(u8 u8TcntReg)
{
	TCNT0=u8TcntReg;
}

void TIM0_voidSetOCRValue(u8 u8OcrReg)
{
	OCR0=u8OcrReg;
}

u8 TIM0_u8ReadTcntReg(void)
{
	return TCNT0;
}

void TIM0_voidSetCallBackOvfInt(pf pfOvfcallBack)
{
	TIM0_pfOVFCallBack=pfOvfcallBack;
}

void TIM0_voidSetCallBackCompareInt(pf pfComcallBack)
{
	TIM0_pfCmpCallBack=pfComcallBack;

}
void __vector_11 (void)   __attribute__ ((signal));

void __vector_11 (void)
{
	if (TIM0_pfOVFCallBack!=NULL_PTR)
	{
		TIM0_pfOVFCallBack();
	}
	else
	{
		///
	}

}

void __vector_10 (void)   __attribute__ ((signal));

void __vector_10 (void)
{
	if (TIM0_pfCmpCallBack!=NULL_PTR)
	{
		TIM0_pfCmpCallBack();
	}
	else
	{

	}

}




