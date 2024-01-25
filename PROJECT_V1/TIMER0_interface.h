/*****************************************************************/
/* Author  : ahmed saeed                                         */
/* Layer   : MCAL                                                */
/* SWC     : TIMER0                                              */
/* Version : 1.0                                                 */
/* Date    : 16 Aug 2023                                         */
/*****************************************************************/
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


#define PRESCALER_1      1
#define PRESCALER_8      2
#define PRESCALER_64     3
#define PRESCALER_256    4
#define PRESCALER_1024   5

#define ETERNAL_CLOCK_RISING     7
#define ETERNAL_CLOCK_FALLING    6


void TIM0_voidInit(void);
void TIM0_voidEnable(u8 u8PreScaler);
void TIM0_voidDisable(void);
void TIM0_voidEnableOvfINt(void);
void TIM0_voidDisableOvfINt(void);
void TIM0_voidEnableComparINt(void);
void TIM0_voidDisableCompareINt(void);
void TIM0_voidSetCallBackOvfInt(pf pfOvfcallBack);
void TIM0_voidSetCallBackCompareInt(pf pfComcallBack);
void TIM0_voidSetTCNTValue(u8 u8TcntReg);
void TIM0_voidSetOCRValue(u8 u8OcrReg);
u8 TIM0_u8ReadTcntReg(void);
void TIM0_delay_ms(u16 milliseconds);










#endif
