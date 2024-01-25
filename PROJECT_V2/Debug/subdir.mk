################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DC_motor_program.c \
../DIO_program.c \
../EEPROM_program.c \
../EXTI_program.c \
../Global_Interrupt_program.c \
../Keybad_program.c \
../LCD_program.c \
../MTWI_program.c \
../TIM1.c \
../TIMER0_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./DC_motor_program.o \
./DIO_program.o \
./EEPROM_program.o \
./EXTI_program.o \
./Global_Interrupt_program.o \
./Keybad_program.o \
./LCD_program.o \
./MTWI_program.o \
./TIM1.o \
./TIMER0_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DC_motor_program.d \
./DIO_program.d \
./EEPROM_program.d \
./EXTI_program.d \
./Global_Interrupt_program.d \
./Keybad_program.d \
./LCD_program.d \
./MTWI_program.d \
./TIM1.d \
./TIMER0_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


