#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define LOW_LEVEL 0
#define IOC 1 //interrupt on Change.
#define FALLING_EDGE 2
#define RISING_EDGE 3

#define EXT0 0
#define EXT1 1
#define EXT2 2

#define EXT0_MODE IOC //you can select the mode //
/*
options:
LOW_LEVEL
IOC
FALLING_EDGE
RISING_EDGE
*/
#define EXT1_MODE IOC
//you can select the mode //
/*
options:
LOW_LEVEL
IOC
FALLING_EDGE
RISING_EDGE
*/
#define EXT2_MODE FALLING_EDGE
//you can select the mode //
/*
options:
FALLING_EDGE
RISING_EDGE
*/

void EXT_INTERRUPT_VID_INIT(void);
void EXT_INTERRUPT_VID_ENABLE(u8 interrupt_number);
void EXT_INTERRUPT_VID_DISABLE(u8 interrupt_number);
void EXT_INTERRUPT_VID_SET_MODE(u8 interrupt_number , u8 mode);
void EXT0_VID_SET_CALL_BACK(void (*PTR)(void));
void EXT1_VID_SET_CALL_BACK(void (*PTR)(void));
void EXT2_VID_SET_CALL_BACK(void (*PTR)(void));

#endif /* EXTI_INTERFACE_H_ */
