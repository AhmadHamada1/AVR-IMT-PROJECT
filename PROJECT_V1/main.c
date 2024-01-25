/*
 * main.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Ahmed Hamada
 */

//#include <avr/io.h>
#include "main_config.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER0_interface.h"
#include "DIO_interface.h"
#include "Keybad_interface.h"
#include "LCD_interface.h"
#include "LCD_extra.h"
#include "DC_motor_interface.h"
#include <util/delay.h>
#include "EEPROM_interface.h"
#include "TIM1.h"
#include "Global_Interrupt_interface.h"
#include "EXTI_interface.h"
#include "UART_interface.h"
#include "MTWI_interface.h"

void ENTER_PASS(void);

void SET_PASS(void);
void	SERVO_ON(void);

void function_1(void);

u8 spiro=0;
u8 Bigcola=0;
int main(void)
{
	//number of cans initialized
	spiro=1;
	Bigcola=10;
	EEPROM_vWrite(EEPROM_SPIRO_ADDRESS,spiro);
	EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
	u8 key_pressed = 0;
	u8 Data;

	DIO_voidInit();

	UART_voidInit();
	KPD_init();
	LCD_vidInit();
	LCD_vidSendCommand( lcd_EntryMode);
	TIM1_voidInit();
	TIM1_voidSetIcuRegValue(20000);

	//PRESCALAR 8
	TIM1_voidEnable(2);
	EXT_INTERRUPT_VID_INIT();

	Global_Interrupt_Enable();

	EXT_INTERRUPT_VID_ENABLE(EXT0);
	//EXT TO MAKE THE SERVO ON IF SOMEONE BOUGHT CANS
	EXT0_VID_SET_CALL_BACK(&SERVO_ON);

	UART_voidInit();


	TWI_vMasterInit();


	DIO_voidPullUpState(PORT_D,DIO_PIN_NUM_D2,Enable_PullUp);


	/*<<<<<<<<<<Setting passwords if not set>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */

	EEPROM_vRead(ADMIN_PASS_STATUS_ADDRESS,&Data);
	if(Data!=PASS_SET)
	{


		LCD_vidWriteString("Set Machine");
		Gotoxy(0,2);
		LCD_vidWriteString("Password");
		_delay_ms(1000);
		LCD_vidSendCommand(lcd_Clear);
		LCD_vidWriteString("Set pass");
		Gotoxy(0,2);
		SET_PASS();
	}
	//To save password for comparison
	u8 saved_pass=0;

	EEPROM_vRead(EEPROM_PASS_ADDRESS,&saved_pass);

	LCD_vidSendCommand(lcd_Clear);


	u8 LCD_flag=0;
	u8 x;
	while(1)
	{
		//flag to print one time

		if(!LCD_flag)
		{

			Gotoxy(3,1);

			LCD_vidWriteString("Machine-KO");
			Gotoxy(0,2);
			LCD_vidWriteString("1:Options 2:buy");
			LCD_flag=1;

		}


		key_pressed = NOT_PRESSED;
		u8 display = 0;

		display=KPD_GetKey()-ASCII_ZERO;

		//TO GET THE VALUE FROM UART TTL AND CHECK ON IT WHAT TO DO
		x=UART_u8ReceiveData();
		switch(x)
		{
		case '1':	//OPTIONS


			LCD_flag=0;
			LCD_vidSendCommand(lcd_Clear);

			//Entering Password
			LCD_vidWriteString("Enter Password :");
			ENTER_PASS();

			//for checking the password
			u8 checking=0;
			EEPROM_vRead(EEPROM_CHECK_PASS_ADDRESS,&checking);


			if( saved_pass==checking)
			{
				LCD_vidSendCommand(lcd_Clear);

				LCD_vidWriteString("Correct Password");
				_delay_ms(500);

				while(key_pressed!='3'){
					//IF Pass RIGHT GO TO options >>> add items of cans number
					LCD_vidSendCommand(lcd_Clear);
					_delay_ms(1000);
					Gotoxy(0,1);
					LCD_vidWriteString("1:Add items");


					Gotoxy(0,2);
					LCD_vidWriteString("2:Cans No 3:OUT");

					key_pressed = NOT_PRESSED;

					while (key_pressed == NOT_PRESSED)
					{
						key_pressed = KPD_GetKey();
					}
					LCD_vidSendCommand(lcd_Clear);

					switch(key_pressed)
					{


					//AFTER ADDING ITEMS THE ITEMS WILL BE UPDATED

					case '1':

						Gotoxy(0,1);
						LCD_vidWriteString("item to add is: ");
						Gotoxy(0,2);

						LCD_vidWriteString("1:Spiro 2:Cola");
						key_pressed = NOT_PRESSED;

						while (key_pressed == NOT_PRESSED)
						{
							key_pressed = KPD_GetKey();
						}
						if (key_pressed=='1')
						{
							//update the spiro cans number in eeprom
							spiro++;
							EEPROM_vWrite(EEPROM_SPIRO_ADDRESS,spiro);
							LCD_vidSendCommand(lcd_Clear);


							//MOTOR WORK AS CAN IS OUT
							DCM_voidRotateCW();
							_delay_ms(1000);

							Gotoxy(0,1);
							LCD_vidWriteString("Item is Added");
							_delay_ms(500);
							DCM_voidStop();


						}
						else{

							LCD_vidSendCommand(lcd_Clear);
							//update the spiro cans number in eeprom
							Bigcola++;
							EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
							//MOTOR WORK AS CAN IS OUT
							DCM_voidRotateCW();
							_delay_ms(1000);

							Gotoxy(0,1);

							LCD_vidWriteString("Item is Added");
							_delay_ms(300);
							DCM_voidStop();

						}


						break;
					case '2':
						LCD_flag=0;
						LCD_vidSendCommand(lcd_Clear);
						Gotoxy(0,1);
						LCD_vidWriteString("Spiro : ");

						//VARIABLES TO PUT THE NUM OF CANS TO SHOW IT ON LCD
						u8 spiro_num=0;
						u8 cola_num=0;
						EEPROM_vRead(EEPROM_SPIRO_ADDRESS,&spiro_num);
						EEPROM_vRead(EEPROM_COLA_ADDRESS,&cola_num);

						LCD_writeNum_u8(spiro_num);
						Gotoxy(0,2);
						LCD_vidWriteString("Big-Cola: ");

						LCD_writeNum_u8(cola_num);
						_delay_ms(2000);

						break;

					default :
						LCD_flag=0;
						break;

					}

				}



			}
			else//WRONG PASSWORD
			{
				////BUZZ_ON AND PRINT INCORRECT PASSWORD
				DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D6,DIO_HIGH);
				LCD_vidWriteString("INCORRECT");
				Gotoxy(0,2);
				LCD_vidWriteString("PASSWORD");
				_delay_ms(1000);

				DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D6,DIO_LOW);
				LCD_vidSendCommand(lcd_Clear);

			}
			break;
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>					<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		case '2': //right

			while(key_pressed!='3'){
				LCD_vidSendCommand(lcd_Clear);

				_delay_ms(500);
				Gotoxy(0,1);
				LCD_vidWriteString("1:spiro");

				Gotoxy(0,2);
				LCD_vidWriteString("2:BigCola 3:out");
				//WHATEVER HE SELECTS THE ITEM WILL DECREASE BY ONE AND SERVO WILL WORK

				key_pressed = NOT_PRESSED;

				while (key_pressed == NOT_PRESSED)
				{
					key_pressed = KPD_GetKey();
				}
				if (key_pressed=='1')
				{
					LCD_vidSendCommand(lcd_Clear);
					if (spiro==0)
					{
						//BUZZER ON AND PRINT THERE IS NO CANS
						DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D3,DIO_HIGH);
						LCD_vidWriteString("NOT AVAILABLE!");
						_delay_ms(700);
						DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D3,DIO_LOW);
						LCD_vidSendCommand(lcd_Clear);

					}
					else
					{
						//UPDATE THE NUMBER IN SAVE IT IN EEPROM
						spiro--;
						EEPROM_vWrite(EEPROM_SPIRO_ADDRESS,spiro);

						LCD_vidSendCommand(lcd_Clear);
						Gotoxy(0,1);
						LCD_vidWriteString("ENJOY Refreshing!");

						//INTERRUPT TO Servo WORK AS THE CAN IS OUT
						DIO_voidTogglePin(PORT_D,DIO_PIN_NUM_D2);

						_delay_ms(550);

					}
				}
				else{

					if (Bigcola==0)
					{
						//BUZZER ON AND PRINT THERE IS NO CANS
						DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D3,DIO_HIGH);
						LCD_vidWriteString("NOT AVAILABLE!");
						_delay_ms(700);

						DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D3,DIO_LOW);
						LCD_vidSendCommand(lcd_Clear);

					}
					else
					{
						//UPDATE THE NUMBER IN SAVE IT IN EEPROM
						Bigcola--;
						EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
						LCD_vidSendCommand(lcd_Clear);
						Gotoxy(0,1);
						LCD_vidWriteString("ENJOY Refreshing!");

						//INTERRUPT TO Servo WORK AS THE CAN IS OUT
						DIO_voidTogglePin(PORT_D,DIO_PIN_NUM_D2);


						_delay_ms(550);

					}
				}
			}

			break;

		default:
			break;
		}

	}


}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void SET_PASS(void){
	//SET Password from 3 digit
	u8 pass_counter=0;
	u8 pass=0;
	u8 key_pressed = 0;

	while (pass_counter<PASS_SIZE)
	{
		key_pressed = NOT_PRESSED;
		while (key_pressed == NOT_PRESSED)
		{
			key_pressed = KPD_GetKey();

		}
		pass = pass * 10 + (key_pressed - '0');

		LCD_vidWriteCharctr(key_pressed);

		_delay_ms(CHARACTER_PREVIEW_TIME);
		Gotoxy(0+pass_counter,2);
		LCD_vidWriteCharctr(PASSWORD_SYMBOL);
		_delay_ms(100);
		pass_counter++;

	}

	LCD_vidSendCommand(lcd_Clear);
	//SAVE PASSWORD & SAVE THE STATUS AS SET
	EEPROM_vWrite(EEPROM_PASS_ADDRESS,pass);
	EEPROM_vWrite(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);
	LCD_vidWriteString("Password is Saved");
	_delay_ms(1000);
	LCD_vidSendCommand(lcd_Clear);

}


void ENTER_PASS(void)
{
	//	u8 key_pressed = 0;

	u8 pass_counter=0;
	u8 pass_entered=0;
	u8 x;
	u8 flag=1;
	while (pass_counter<PASS_SIZE)
	{
		//		key_pressed = NOT_PRESSED;
		while (flag)
		{
			//			key_pressed = KPD_GetKey();
			x=UART_u8ReceiveData();
			if(x)
			{
				flag=0;
			}
		}
		//equation to save the entered pass in a variable
		//we enter 1 , 1 , 1 then 2 >>>> so it makes it 1112
		pass_entered = pass_entered * 10 + (x - '0');

		LCD_vidWriteCharctr(x);
		flag=1;
		_delay_ms(CHARACTER_PREVIEW_TIME);
		//go to the previous location to hide the pass entered
		Gotoxy(0+pass_counter,2);
		LCD_vidWriteCharctr(PASSWORD_SYMBOL);
		_delay_ms(100);
		pass_counter++;

	}
	LCD_vidSendCommand(lcd_Clear);

	//SAVE PASSWORD & SAVE THE STATUS AS SET
	EEPROM_vWrite(EEPROM_CHECK_PASS_ADDRESS,pass_entered);
	//EEPROM_vWrite(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);
	_delay_ms(1000);
	LCD_vidSendCommand(lcd_Clear);

}



void SERVO_ON(void)
{
	DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D7,DIO_HIGH);


	u16 u16Counter;

	// Move to 90 degrees
	for (u16Counter = 750; u16Counter < 1500; u16Counter++)
	{
		TIM1_voidSetCmpARegValue(u16Counter);
		_delay_ms(10);
		u16Counter	=        u16Counter+5	;
	}
	// Wait for stability (optional)
	_delay_ms(500);

	// Stop at 90 degrees
	TIM1_voidSetCmpARegValue(1500);  // Adjust the value for precise 90 degrees

	DIO_voidWritePin(PORT_D,DIO_PIN_NUM_D7,DIO_LOW);

	//	    // Move to 90 degrees
	//	    TIM1_voidSetCmpARegValue(1500);  // Adjust the value for precise 90 degrees
	//
	//	    // Wait for stability (optional)
	//	    _delay_ms(500);


}



void function_1(void)
{
	for(int i=0 ;i<2;i++){
		_delay_ms(550);
		DIO_voidTogglePin(PORT_D,DIO_PIN_NUM_D6);
		_delay_ms(550);
	}
}
