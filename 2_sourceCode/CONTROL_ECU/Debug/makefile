################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/port/subdir.mk
-include MCAL/e_interrupt/subdir.mk
-include MCAL/GPIO/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/BUTTON/subdir.mk
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
CONTROL_ECU.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: CONTROL_ECU.elf secondary-outputs

# Tool invocations
CONTROL_ECU.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CONTROL_ECU.map -mmcu=atmega16 -o "CONTROL_ECU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CONTROL_ECU.lss: CONTROL_ECU.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CONTROL_ECU.elf  >"CONTROL_ECU.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CONTROL_ECU.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 CONTROL_ECU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CONTROL_ECU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
