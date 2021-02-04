################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/atmega32/2_sourceCode/MCAL/port/port.c 

OBJS += \
./2_sourceCode/MCAL/port/port.o 

C_DEPS += \
./2_sourceCode/MCAL/port/port.d 


# Each subdirectory must supply rules for building sources it contributes
2_sourceCode/MCAL/port/port.o: D:/Github/atmega32/2_sourceCode/MCAL/port/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Github\atmega32\2_sourceCode\HAL\BUTTON" -I"D:\Github\atmega32\2_sourceCode\HAL\LED" -I"D:\Github\atmega32\2_sourceCode\includes" -I"D:\Github\atmega32\2_sourceCode\MCAL\e_interrupt" -I"D:\Github\atmega32\2_sourceCode\MCAL\GPIO" -I"D:\Github\atmega32\2_sourceCode\MCAL\port" -I"D:\Github\atmega32\2_sourceCode\programs\eInterrupts" -I"D:\Github\atmega32\2_sourceCode\programs\gpio" -I"D:\Github\atmega32\2_sourceCode\programs\port" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


