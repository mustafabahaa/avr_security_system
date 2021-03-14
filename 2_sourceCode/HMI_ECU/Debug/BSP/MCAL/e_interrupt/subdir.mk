################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Mustafa/Desktop/atmega32/2_sourceCode/BSP/MCAL/e_interrupt/e_interrupt.c 

OBJS += \
./BSP/MCAL/e_interrupt/e_interrupt.o 

C_DEPS += \
./BSP/MCAL/e_interrupt/e_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/MCAL/e_interrupt/e_interrupt.o: C:/Users/Mustafa/Desktop/atmega32/2_sourceCode/BSP/MCAL/e_interrupt/e_interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


