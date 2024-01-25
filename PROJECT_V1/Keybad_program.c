/*****************************************************************/
/* Author  : Hamo                                                */
/* SWC     : Keybad                                              */
/* Version : 1.0                                                 */
/* Date    : 12 Dec 2023                                         */
/*****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Keybad_interface.h"
#include <util/delay.h>

//u8 KPD_arr[4][4]=
//{
//		{7,8,9,15},
//		{4,5,6,7},
//		{1,2,3,15},
//		{12,0,14,15}
//};
	u8 KPD_arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}}; //keypad buttons


void KPD_init(void)
{
	u8 i;


	for(i=ROW_START;i<=ROW_END;i++)
	{
		//DIO_SETPINDIR(KPD_PORT,PIN INPUT) WE DID IT FROM DIO_CONFIG.H
		DIO_voidWritePin(KPD_PORT,i,DIO_HIGH);
	}

	for(i=COLUMN_START;i<=COLUMN_END;i++)
	{
		//DIO_SETPINDIR(KPD_PORT,PIN OUTPUT) WE DID IT FROM DIO_CONFIG.H
		DIO_voidWritePin(KPD_PORT,i,DIO_HIGH);
	}


}


u8 KPD_GetKey(void)
{
	u8 key=NoPressedKEY;
	u8 i,j,k;
	u8 result;
	u8 exitflag=0;

	for(i=0;i<4;i++)
	{
		//SET ALL COLUMNS HIGH
		for(k=COLUMN_START;k<=COLUMN_END;k++)
		{
			DIO_voidWritePin(KPD_PORT,k,DIO_HIGH);

		}

		//SET COLUMNS LOW
		DIO_voidWritePin(KPD_PORT,(COLUMN_START+i),DIO_LOW);

		for(j=0;j<4;j++)
		{
			result=DIO_u8ReadPin(KPD_PORT,(ROW_START+j));
			_delay_ms(20);
			if(result==DIO_LOW)
			{
				key=KPD_arr[j][i];
				exitflag=1;
				if(exitflag==1)
				{
					break;
				}
			}
		}
		if(exitflag==1)
		{
			break;
		}
	}

	return key;
}



