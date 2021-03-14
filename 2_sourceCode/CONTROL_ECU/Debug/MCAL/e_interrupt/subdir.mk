################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/e_interrupt/e_interrupt.c 

OBJS += \
./MCAL/e_interrupt/e_interrupt.o 

C_DEPS += \
./MCAL/e_interrupt/e_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/e_interrupt/%.o: ../MCAL/e_interrupt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


