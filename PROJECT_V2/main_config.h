#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#include "STD_Types.h"

#define EEPROM_PASS_ADDRESS      (u8)0xE5
#define EEPROM_CHECK_PASS_ADDRESS      (u8)0XED
#define EEPROM_COLA_ADDRESS      (u8)0xF1
#define EEPROM_SPIRO_ADDRESS      (u8)0xFD


#define NOT_SELECTED 0xFF
#define NOT_PRESSED 0xff

#define ADMIN_PASS_STATUS_ADDRESS (u8)0X100


#define PASS_SIZE       (u8)4

#define PASSWORD_SYMBOL (u8)'*'
#define ASCII_ZERO      (u8)'0'

#define PASS_NOT_SET (u8)0xFF
#define PASS_SET     (u8)0x01

#define CHARACTER_PREVIEW_TIME (u16)200

#define DEGREES_SYMBOL		   (u8)0xDF



#endif /* MAIN_CONFIG_H_ */
