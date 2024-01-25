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
#include "DC_motor_interface.h"

#include "Keybad_interface.h"
#include "LCD_interface.h"
#include "LCD_extra.h"
#include <util/delay.h>
#include "EEPROM_interface.h"
#include "ADC_interface.h"
//#include "TIM1.h"
#include "Global_Interrupt_interface.h"
#include "EXTI_interface.h"

#include "MTWI_interface.h"

void ENTER_PASS(void);

void SET_PASS(void);

u8 spiro=0;
u8 Bigcola=0;

//void function_1(void);


void ISR_LM35_Timer0(void);
u32 Temperature=0;
int main(void)
{
	u8 key_pressed = 0;
	u8 Data;
	//number of cans initialized
	u8 spiro=1;
	u8 Bigcola=10;
	EEPROM_vWrite(EEPROM_SPIRO_ADDRESS,spiro);
	EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
	DIO_voidInit();


	ADC_Init ();
	KPD_init();
	LCD_vidInit();
	LCD_vidSendCommand( lcd_EntryMode);
	ADC_Init ();
	TIM0_voidInit();
	TIM0_voidSetCallBackCompareInt(ISR_LM35_Timer0);
	TIM0_voidSetOCRValue(150);
	TIM0_voidEnable(PRESCALER_8);
	TIM0_voidEnableComparINt();


	TWI_vMasterInit();
	Global_Interrupt_Enable();

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

	Global_Interrupt_Enable();


	//flag to print one time
	u8 LCD_flag=0;
	if(!LCD_flag)
	{

		Gotoxy(0,1);

		LCD_vidWriteString("Machine-KO");
		Gotoxy(0,2);
		LCD_vidWriteString("1:Options 2:buy");
		LCD_flag=1;

	}

	while(1)
	{
		if(!LCD_flag)
		{

			Gotoxy(0,1);

			LCD_vidWriteString("Machine-KO");
			Gotoxy(0,2);
			LCD_vidWriteString("1:Options 2:buy");
			LCD_flag=1;

		}

		Gotoxy(14,1);
		LCD_vidWriteCharctr(DEGREES_SYMBOL);
		LCD_vidWriteCharctr('C');

		Gotoxy(12,1);
		LCD_writeNum_u32(Temperature);
		LCD_vidWriteCharctr(' ');



		//wait for the keypad pressing
		key_pressed = NOT_PRESSED;
		u8 display = 0;
		display=KPD_GetKey()-ASCII_ZERO;
		switch(display)
		{
		case 1:	//OPTIONS
			//don't need now
			Global_Interrupt_Disable();
			LCD_flag=0;


			LCD_vidSendCommand(lcd_Clear);

			//Entering Password
			LCD_vidWriteString("Enter Password :");

			u8 key_pressed = 0;
			u8 pass_counter=0;
			u8 pass_entered=0;

			while (pass_counter<PASS_SIZE)
			{
				key_pressed = NOT_PRESSED;
				while (key_pressed == NOT_PRESSED)
				{
					key_pressed = KPD_GetKey();
				}

				//equation to save the entered pass in a variable
				//we enter 1 , 1 , 1 then 2 >>>> so it makes it 1112
				pass_entered = pass_entered * 10 + (key_pressed - '0');

				LCD_vidWriteCharctr(key_pressed);

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

			//variable for checking the password and compare it with saved one
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
					_delay_ms(500);
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
							DCM_voidStop();

							Gotoxy(0,1);
							LCD_vidWriteString("Item is Added");
							_delay_ms(500);


						}
						else{


							LCD_vidSendCommand(lcd_Clear);
							//UPDATE THE COLA NUMBER IN EEPROM
							Bigcola++;
							EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
							//MOTOR WORK AS CAN IS OUT
							DCM_voidRotateCW();
							_delay_ms(2000);
							DCM_voidStop();

							Gotoxy(0,1);

							LCD_vidWriteString("Item is Added");
							_delay_ms(500);

						}


						break;
					case '2':

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



						//temp
						break;

					default :
						break;

					}

				}



			}
			//WRONG PASSWORD
			else
			{
				////BUZZ_ON AND PRINT INCORRECT PASSWORD

				DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_HIGH);
				LCD_vidWriteString("INCORRECT");
				Gotoxy(0,2);
				LCD_vidWriteString("PASSWORD");
				_delay_ms(500);
				DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_LOW);
				LCD_vidSendCommand(lcd_Clear);



			}

			break;
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>					<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Case2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		case 2: //BUY

			//FLAG OF THE FIRST LCD IN WHILE
			LCD_flag=1;
			Global_Interrupt_Disable();


			while(key_pressed!='3'){
				LCD_vidSendCommand(lcd_Clear);

				_delay_ms(500);
				Gotoxy(0,1);
				LCD_vidWriteString("1:spiro");

				Gotoxy(0,2);
				LCD_vidWriteString("2:BigCola 3:out");
				//WHATEVER HE SELECTS THE ITEM WILL DECREASE BY ONE AND MOTOR WILL WORK

				key_pressed = NOT_PRESSED;

				while (key_pressed == NOT_PRESSED)
				{
					key_pressed = KPD_GetKey();
				}
				if (key_pressed=='1')
				{
					//CAN IS 0
					if (spiro==0)
					{

						//BUZZER ON AND PRINT THERE IS NO CANS
						DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_HIGH);
						_delay_ms(700);


						DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_LOW);

						LCD_vidSendCommand(lcd_Clear);
						LCD_vidWriteString("NOT AVAILABLE!");
						_delay_ms(700);

					}
					else
					{
						LCD_vidSendCommand(lcd_Clear);
						//UPDATE THE NUMBER IN SAVE IT IN EEPROM
						spiro--;
						EEPROM_vWrite(EEPROM_SPIRO_ADDRESS,spiro);
						DIO_voidWritePin(PORT_C,DIO_PIN_NUM_C7,DIO_HIGH);
						LCD_vidSendCommand(lcd_Clear);

						//MOTOR WORK AS THE ITEM IS OUT
						Gotoxy(0,1);
						DCM_voidRotateCCW();
						DIO_voidTogglePin(PORT_A,DIO_PIN_NUM_A1);
						LCD_vidWriteString("ENJOY Refreshing!");
						_delay_ms(1000);
						DCM_voidStop();
						DIO_voidTogglePin(PORT_A,DIO_PIN_NUM_A1);
						LCD_vidSendCommand(lcd_Clear);



					}
				}
				else if(key_pressed=='2')
				{
					if (Bigcola==0)
					{
						//BUZZER ON AND PRINT THERE IS NO CANS
						DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_HIGH);
						LCD_vidWriteString("NOT AVAILABLE!");
						_delay_ms(700);
						DIO_voidWritePin(PORT_A,DIO_PIN_NUM_A2,DIO_LOW);
						LCD_vidSendCommand(lcd_Clear);

					}
					else
					{
						Bigcola--;
						EEPROM_vWrite(EEPROM_COLA_ADDRESS,Bigcola);
						LCD_vidSendCommand(lcd_Clear);

						DIO_voidWritePin(PORT_C,DIO_PIN_NUM_C7,DIO_HIGH);
						LCD_vidSendCommand(lcd_Clear);

						//MOTOR WORK AS THE ITEM IS OUT

						DCM_voidRotateCCW();
						DIO_voidTogglePin(PORT_A,DIO_PIN_NUM_A1);
						Gotoxy(0,1);
						LCD_vidWriteString("ENJOY Refreshing!");
						_delay_ms(1000);
						DCM_voidStop();
						DIO_voidTogglePin(PORT_A,DIO_PIN_NUM_A1);
						LCD_vidSendCommand(lcd_Clear);


					}


				}
			}

			break;

		default:
			LCD_flag=0;
			LCD_vidSendCommand(lcd_Clear);


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
	u8 key_pressed = 0;

	u8 pass_counter=0;
	u8 pass_entered=0;

	while (pass_counter<PASS_SIZE)
	{
		key_pressed = NOT_PRESSED;
		while (key_pressed == NOT_PRESSED)
		{
			key_pressed = KPD_GetKey();
		}
		//equation to calculate the number entered and put it into a variable
		//we enter 1 ,1 , 1 , 2 it makes it 1112
		pass_entered = pass_entered * 10 + (key_pressed - '0');

		LCD_vidWriteCharctr(key_pressed);

		_delay_ms(CHARACTER_PREVIEW_TIME);
		//move cursor to the previous location To hide the pass entered
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


void ISR_LM35_Timer0(void)
{
	static u16 Local_u8Counter ;


	if(Local_u8Counter == 5)
	{
		u16 read=0;


		u32 millivolt=0;
		read =ADC_Read(Channel_A0);
		millivolt=(((u32)read*5000)/1024);
		Temperature = (millivolt + 5) / 10;
		Local_u8Counter=0;
	}
	Local_u8Counter++;
}
