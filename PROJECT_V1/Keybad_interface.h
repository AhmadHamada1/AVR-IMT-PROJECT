/*****************************************************************/
/* Author  : Hamo                                                */
/* SWC     : Keybad                                              */
/* Version : 1.0                                                 */
/* Date    : 12 Dec 2023                                         */
/*****************************************************************/
#ifndef KEYBAD_INTERFACE_H_
#define KEYBAD_INTERFACE_H_

#define 	KPD_PORT		PORT_B
#define 	ROW_START		DIO_PIN_NUM_A0
#define 	ROW_END			DIO_PIN_NUM_A3
#define 	COLUMN_START	DIO_PIN_NUM_A4
#define 	COLUMN_END		DIO_PIN_NUM_A7

#define NoPressedKEY	0xff

#define SEVSEG_PORT_NAME  PORT_A

void KPD_init(void);
u8 KPD_GetKey(void);


#endif
