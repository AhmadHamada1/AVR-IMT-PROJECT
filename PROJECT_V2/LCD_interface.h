/*****************************************************************/
/* Author  : Hamo                                                */
/* SWC     : LCD                                                 */
/* Version : 1.0                                                 */
/* Date    : 11 Dec 2023                                         */
/*****************************************************************/
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/***************************************************************************************/
/********************************** Fucntion Definition ********************************/
/***************************************************************************************/

/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C           // display on, cursor oFF, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position
#define lcd_SetCGRAM       0x40         // set cursor position

/***************************************************************************************/
/********************************** LCD DIO *********************************************/
/***************************************************************************************/

#define lcd_DATAPORT       PORT_D
#define lcd_CONTROLPORT       PORT_C
#define lcd_RSPIN       DIO_PIN_NUM_C4
#define lcd_RWPIN       DIO_PIN_NUM_C5
#define lcd_EPIN       DIO_PIN_NUM_C6
#define LineOneStart		128
#define LineTwoStart		192

/***************************************************************************************/
/********************************** Fucntion Definition ********************************/
/***************************************************************************************/


void LCD_vidInit(void);
void LCD_vidSendCommand(u8 u8CmdCpy);
void LCD_vidWriteCharctr(u8 u8DataCpy);
void LCD_vidWriteString (const char* pu8StringCpy);
void LCD_WRITE_STRING( char* string);
void Gotoxy (u8 x,u8 y);
void LCD_vidWriteExtraChar (u8 x,const u8* y);
void LCD_writeNum_u8(u8 num);
void LCD_writeNum_u32(u32 num);
#endif /* LCD_INTERFACE_H_ */

