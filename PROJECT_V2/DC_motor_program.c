/*
 * DC_motor_program.c
 *
 *  Created on: Dec 13, 2023
 *      Author: ahmed saeed
 */


/*
 * main.c
 *
 *  Created on: Dec 13, 2023
 *      Author: ahmed saeed
 */


/*
 * DCmotor.c
 *
 *  Created on: Aug 11, 2023
 *      Author: ahmed saeed
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "DC_motor_interface.h"
#include "DC_motor_config.h"
#include "DIO_interface.h"


void DCM_voidRotateCW(void)
{
	DIO_voidWritePin(DCM_PORT,DCM_PIN0,DIO_LOW);
	DIO_voidWritePin(DCM_PORT,DCM_PIN1,DIO_HIGH);

}
void DCM_voidRotateCCW(void)
{
	DIO_voidWritePin(DCM_PORT,DCM_PIN1,DIO_LOW);
	DIO_voidWritePin(DCM_PORT,DCM_PIN0,DIO_HIGH);

}
void DCM_voidStop(void)
{
	DIO_voidWritePin(DCM_PORT,DCM_PIN1,DIO_LOW);
	DIO_voidWritePin(DCM_PORT,DCM_PIN0,DIO_LOW);

}
