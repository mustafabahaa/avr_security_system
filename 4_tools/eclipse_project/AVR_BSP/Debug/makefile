################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include 2_sourceCode/programs/port/subdir.mk
-include 2_sourceCode/programs/gpio/subdir.mk
-include 2_sourceCode/programs/eInterrupts/subdir.mk
-include 2_sourceCode/MCAL/port/subdir.mk
-include 2_sourceCode/MCAL/e_interrupt/subdir.mk
-include 2_sourceCode/MCAL/GPIO/subdir.mk
-include 2_sourceCode/HAL/LED/subdir.mk
-include 2_sourceCode/HAL/BUTTON/subdir.mk
-include 2_sourceCode/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
AVR_BSP.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: AVR_BSP.elf secondary-outputs

# Tool invocations
AVR_BSP.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AVR_BSP.map -mmcu=atmega16 -o "AVR_BSP.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AVR_BSP.lss: AVR_BSP.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR_BSP.elf  >"AVR_BSP.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR_BSP.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 AVR_BSP.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AVR_BSP.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
