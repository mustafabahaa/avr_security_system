# avr_security_system

## Project Description

project is a door lock or safe , consists of 
HMI-UNIT ( LCD - Keypad )
CTRL-UNIT ( Buzzer - External EEPROM - Servo Motor ) 
both connected with UART channel

### HMI-UNIT - CTRL-UNIT
This unit is used for password entry using the LCD as interface and keypad to enter the values.
If system is opened for the first time it will require a new password to be set. 
If password is set before then the already saved password will be required by the system.
Upon password entry it will send a signal to the CTRL-unit to verify the system.
CTRL-unit verfiy the password and lock or unlock the system using the servo motor.
The servo motor in real mechanical system act as the actucator for the door opening or closing.
The system accepts 3 wrong password entries , if it's consumed the system will go to Alarm and freeze state.

## Folder Structure 

### 1_docs
datasheet for the microcontroller used

### 2_sourceCode
SecuritySystem\SecuritySystem.atsln
the containing project for the two ECU's project  ( CONTROL_ECU.atsln - HMI_ECU.atsln )
2_sourceCode\SecuritySystem\CONTROL_ECU\CONTROL_ECU.atsln  ( CTRL-ECU Project )
2_sourceCode\SecuritySystem\HMI_ECU\HMI_ECU.atsln  ( HMI-ECU Project  )

2_sourceCode\SecuritySystem\HMI_ECU\main.c   ( Main Program for HMI-ECU )
2_sourceCode\SecuritySystem\CONTROL_ECU\main.c  ( Main Program for CTRL-ECU )

2_sourceCode\STACK\BSP\MCAL
( e_interrupt - GPIO - I2C - PORT - SPI - TIMER - UART )

2_sourceCode\STACK\BSP\HAL
( BUTTON - BUZZER - DC_MOTOR - EEPROM - KEYPAD - LCD - LED - SERVO_MOTOR )

2_sourceCode\STACK\BSP\includes
common types and macros

2_sourceCode\STACK\Managers
MessagingUnit : abstraction layer for communication between the 2 ECU

3_sourceCode\STACK\Services
SoftwareUart : Software UART layer for debugging ( not used right now ) 
Logger : Logger component to debug all the program layers

2_sourceCode\STACK\Utility
delay : a custom delay library 
password_management : a library that hande all password operations maybe hashing and encrypting in future
std_library : std lib to write custom implementation to any std function by C



