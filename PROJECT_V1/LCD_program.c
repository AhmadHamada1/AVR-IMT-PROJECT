/*****************************************************************/
/* Author  : Ahmed Hamada                                                */
/* SWC     : LCD                                                 */
/* Version : 1.0                                                 */
/* Date    : 11 Dec 2023                                         */
/*****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include <stdint.h>


#include <util/delay.h>
//#include "LCD_private.h"
//#include "LCD_config.h"

void LCD_vidInit(void)
{
	//PORT IS OUTPUT FORM CONFIGURATION DIO_CONFIG.H

	//make enable low
	DIO_voidWritePin(lcd_CONTROLPORT ,lcd_EPIN,DIO_LOW);

	_delay_ms(30);
	LCD_vidSendCommand(lcd_Home);
	_delay_ms(5);
	LCD_vidSendCommand(lcd_FunctionSet8bit);
	_delay_ms(5);
	LCD_vidSendCommand(lcd_DisplayOn);
	_delay_ms(5);
	LCD_vidSendCommand(lcd_Clear);
	_delay_ms(5);
	LCD_vidSendCommand(lcd_EntryMode);
	_delay_ms(5);

}

void LCD_vidSendCommand(u8 u8CmdCpy)
{
	//COMMAND(0) OR DATA(1)
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_RSPIN,DIO_LOW);
	//read(1) OR write(0)
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_RWPIN,DIO_LOW);

	//make enable low
	DIO_voidWritePin(lcd_CONTROLPORT ,lcd_EPIN,DIO_LOW);

	//WRITE COMMAND ON DATA_PINS
	DIO_voidWritePort(lcd_DATAPORT,u8CmdCpy);

	//ENABLE SEQUENCE
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_EPIN,DIO_HIGH);
	_delay_ms(5);
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_EPIN,DIO_LOW);

}
void LCD_vidWriteCharctr(u8 u8DataCpy)
{
	//COMMAND(0) OR DATA(1)
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_RSPIN,DIO_HIGH);
	//read(1) OR write(0)
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_RWPIN,DIO_LOW);

	//make enable low
	DIO_voidWritePin(lcd_CONTROLPORT ,lcd_EPIN,DIO_LOW);

	//WRITE COMMAND ON DATA_PINS
	DIO_voidWritePort(lcd_DATAPORT,u8DataCpy);

	//ENABLE SEQUENCE
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_EPIN,DIO_HIGH);
	_delay_ms(5);
	DIO_voidWritePin(lcd_CONTROLPORT,lcd_EPIN,DIO_LOW);
}

void LCD_vidWriteString (const char* pu8StringCpy)//LCD_vidWriteString
{

	// check for \0 in while and send or :

//	u8 i=0;
//
//	for(i=0;i<u8Index;i++)
//	{
//		LCD_vidWriteCharctr(pu8StringCpy[i]);
//	}
	 while (*pu8StringCpy != '\0') {
	        LCD_vidWriteCharctr(*pu8StringCpy);
	        pu8StringCpy++;
	    }
}
	void LCD_WRITE_STRING( char* string)
	{
		int count=0;
		while(*string > 0){
			count++;
			LCD_vidWriteCharctr( *string++);
			if(count ==16){
				Gotoxy( 1, 1);
			}
			if(count == 32 || count==33){
				LCD_vidSendCommand(lcd_Clear);
				Gotoxy(0,1);
				count=0;
			}
		}
	}



void Gotoxy (u8 x,u8 y)
{
	if(x>=0 && x<16)
	{
		switch(y)
		{
		case 1:
				LCD_vidSendCommand(x+LineOneStart);
			break;
		case 2:
			LCD_vidSendCommand(x+LineTwoStart);
			break;
		default:
			break;
		}
	}
	else
	{
		//do nothing
	}

}
void LCD_vidWriteExtraChar (u8 x,const u8* y)
{

	u8 i;

	LCD_vidSendCommand(lcd_SetCGRAM + (x * 8)); // Set CGRAM address  0x40 = 0b010000000

	for (i = 0; i < 8; i++) {
	        LCD_vidWriteCharctr(y[i]);
	}
	    // Return to DDRAM address
	    Gotoxy(0,1); //0b1000 0000
}

void custom_itoa(int num, char* buffer, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
    }

    // Handle negative numbers only if base is 10
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num = num / base;
    }

    // Append negative sign for base 10
    if (isNegative && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

void LCD_writeNum_u8(u8 num) {
    // Convert the integer to a string
    char numString[12];  //
    itoa(num, numString, 10);

    // Write the string to the LCD
    LCD_vidWriteString(numString);
}

void LCD_writeNum_u32(u32 num) {
    char numString[12];  // Assuming a 32-bit unsigned integer, so at most 10 digits plus null-terminator
    custom_itoa(num, numString, 10);  // Base 10

    // Write the string to the LCD
    LCD_vidWriteString(numString);
}

