/*****************************************************************/
/* Author  : Ahmed Hamada                                                */
/* SWC     : DIO                                                 */
/* Version : 1.0                                                 */
/* Date    : 07 Dec 2023                                         */
/*****************************************************************/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define DIO_INPUT	0
#define DIO_OUTPUT	1

#define DIO_LOW		0
#define DIO_HIGH	1

#define Enable_PullUp			1
#define Disable_PullUp			0

#define PORT_A		1
#define PORT_B		2
#define PORT_C		3
#define PORT_D		4

//port A pins
#define DIO_PIN_NUM_A0		0
#define DIO_PIN_NUM_A1		1
#define DIO_PIN_NUM_A2		2
#define DIO_PIN_NUM_A3		3
#define DIO_PIN_NUM_A4		4
#define DIO_PIN_NUM_A5		5
#define DIO_PIN_NUM_A6		6
#define DIO_PIN_NUM_A7		7

//port B pins
#define DIO_PIN_NUM_B0		0
#define DIO_PIN_NUM_B1		1
#define DIO_PIN_NUM_B2		2
#define DIO_PIN_NUM_B3		3
#define DIO_PIN_NUM_B4		4
#define DIO_PIN_NUM_B5		5
#define DIO_PIN_NUM_B6		6
#define DIO_PIN_NUM_B7		7

//port C pins
#define DIO_PIN_NUM_C0		0
#define DIO_PIN_NUM_C1		1
#define DIO_PIN_NUM_C2		2
#define DIO_PIN_NUM_C3		3
#define DIO_PIN_NUM_C4		4
#define DIO_PIN_NUM_C5		5
#define DIO_PIN_NUM_C6		6
#define DIO_PIN_NUM_C7		7

//port D pins
#define DIO_PIN_NUM_D0		0
#define DIO_PIN_NUM_D1		1
#define DIO_PIN_NUM_D2		2
#define DIO_PIN_NUM_D3		3
#define DIO_PIN_NUM_D4		4
#define DIO_PIN_NUM_D5		5
#define DIO_PIN_NUM_D6		6
#define DIO_PIN_NUM_D7		7


/* Configure directions+pull up */
void DIO_voidInit(void);

void DIO_voidWritePin(u8 u8PortCpy ,u8 u8PinCpy,u8 u8ValueCpy);
u8 DIO_u8ReadWritePin(u8 u8PortCpy ,u8 u8PinCpy);

void DIO_voidTogglePin(u8 u8PortCpy ,u8 u8PinCpy);

void DIO_voidWritePort(u8 u8PortCpy,u8 u8ValueCpy);

void DIO_voidPullUpState(u8  u8PortCpy,u8 u8PinCpy,u8 u8state);



#endif
