################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Mustafa/Desktop/atmega32/2_sourceCode/BSP/HAL/LED/led.c 

OBJS += \
./BSP/HAL/LED/led.o 

C_DEPS += \
./BSP/HAL/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/HAL/LED/led.o: C:/Users/Mustafa/Desktop/atmega32/2_sourceCode/BSP/HAL/LED/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

