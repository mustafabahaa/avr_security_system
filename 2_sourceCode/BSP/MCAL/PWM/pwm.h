/*
 * pwm.h
 *
 *  Created on: Mar 13, 2021
 *      Author: Lenovo
 */

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_

#include "../../INCLUDE/common_macros.h"
#include "../../INCLUDE/micro_config.h"
#include"../../INCLUDE/std_types.h"

/* -- Global -----------------------------------------------------------------
 **  PWM_1_intialization.h()
 **
 **  parameters : void
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 ** this function initialize the necessary control bits to enable fast pwm mode
 **
 **
 **  TCCR0 - Timer Counter Control Register (TIMER0)
 **  -----------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 6 : WGM00  Wave form generation mode  [SET to 1]
 ** BIT 5 : COM01  Compare Output Mode        [SET to 1]
 ** BIT 4 : COM00  Compare Output Mode        [SET to 0]
 ** BIT 3 : WGM01  Wave form generation mode  [SET to 1]
 ** BIT 2 : CS02   Clock Select               [SET to 0]
 ** BIT 1 : CS01   Clock Select               [SET to 0]
 ** BIT 0 : CS00   Clock Select               [SET to 1]
 **
 ** The above settings are for
 ** --------------------------
 **
 ** Timer Clock = CPU Clock (No Prescalling)
 ** Mode        = Fast PWM
 ** PWM Output  = Non Inverted
 **
 */

/** ------------------------------------------------------------------------*/
void  PWM_1_intialization();

/* -- Global -----------------------------------------------------------------
 **  PWM_1_OUTPUT.h()
 **
 **  parameters : uint8 duty
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 **  this function pass a value from 0 to 255 to the OCR0 register which
 **  controls the output voltage of pin PB3 from 0 to v maximum 5 volts
 **--------------------------------------------------------------------------*/
void  PWM_1_OUTPUT(uint8 duty);

/* -- Global -----------------------------------------------------------------
 **  PWM_2_intialization.h()
 **
 **  parameters : void
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 ** this function initialize the necessary control bits to enable fast pwm mode
 **
 **  TCCR1A - Timer Counter Control Register (TIMER1-channel 1)
 **  -----------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 7 : COM1A1  Compare Output Mode         [SET to 1]
 ** BIT 6 : COM1A0  Compare Output Mode         [SET to 0]
 ** BIT 1 : WGM11   Wave form generation mode   [SET to 1]
 ** BIT 0 : WGM10   Wave form generation mode   [SET to 1]
 **
 **
 **  TCCR1B - Timer Counter Control Register (TIMER1-channel 2)
 **  ---------------------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 2 : CS12   Clock Select               [SET to 0]
 ** BIT 1 : CS11   Clock Select               [SET to 0]
 ** BIT 0 : CS10   Clock Select               [SET to 1]
 **
 ** The above settings are for
 ** --------------------------
 **
 ** Timer Clock = CPU Clock (No Prescalling)
 ** Mode        = Fast PWM
 ** PWM Output  = Non Inverted
 **
 */
/** ------------------------------------------------------------------------*/
void  PWM_2_intialization();

/* -- Global -----------------------------------------------------------------
 **  PWM_2_OUTPUT.h()
 **
 **  parameters : uint8 duty
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 **  this function pass a value from 0 to 1023 to the OC1A register which
 **  controls the output voltage of pin PD5 from 0 to v maximum 5 volts
 **--------------------------------------------------------------------------*/
void  PWM_2_OUTPUT(uint16 duty);

/* -- Global -----------------------------------------------------------------
 **  PWM_3_intialization.h()
 **
 **  parameters : void
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 ** this function initialize the necessary control bits to enable fast pwm mode
 **
 **  TCCR1A - Timer Counter Control Register (TIMER1-channel 1)
 **  ---------------------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 5 : COM1B1  Compare Output Mode         [SET to 1]
 ** BIT 4 : COM1B0  Compare Output Mode         [SET to 0]
 ** BIT 1 : WGM11   Wave form generation mode   [SET to 1]
 ** BIT 0 : WGM10   Wave form generation mode   [SET to 1]
 **
 **
 **  TCCR1B - Timer Counter Control Register (TIMER1-channel 2)
 **  ---------------------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 2 : CS12   Clock Select               [SET to 0]
 ** BIT 1 : CS11   Clock Select               [SET to 0]
 ** BIT 0 : CS10   Clock Select               [SET to 1]
 **
 ** The above settings are for
 ** --------------------------
 **
 ** Timer Clock = CPU Clock (No Prescalling)
 ** Mode        = Fast PWM
 ** PWM Output  = Non Inverted
 **
 */
/** ------------------------------------------------------------------------*/
void  PWM_3_intialization();

/* -- Global -----------------------------------------------------------------
 **  PWM_3_OUTPUT.h()
 **
 **  parameters : uint16 duty
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 **  this function pass a value from 0 to 1023 to the OC1B register which
 **  controls the output voltage of pin PD4 from 0 to v maximum 5 volts
 **--------------------------------------------------------------------------*/
void  PWM_3_OUTPUT(uint16 duty);

/* -- Global -----------------------------------------------------------------
 **  PWM_4_intialization.h()
 **
 **  parameters : void
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 ** this function initialize the necessary control bits to enable fast pwm mode
 **
 **
 **  TCCR2 - Timer Counter Control Register (TIMER2)
 **  -----------------------------------------------
 **  BITS DESCRIPTION
 **
 **
 ** NO:   NAME   DESCRIPTION
 ** --------------------------
 ** BIT 6 : WGM20  Wave form generation mode  [SET to 1]
 ** BIT 5 : COM21  Compare Output Mode        [SET to 1]
 ** BIT 4 : COM20  Compare Output Mode        [SET to 0]
 ** BIT 3 : WGM21  Wave form generation mode  [SET to 1]
 ** BIT 2 : CS22   Clock Select               [SET to 0]
 ** BIT 1 : CS21   Clock Select               [SET to 0]
 ** BIT 0 : CS20   Clock Select               [SET to 1]
 **
 ** The above settings are for
 ** --------------------------
 **
 ** Timer Clock = CPU Clock (No Prescalling)
 ** Mode        = Fast PWM
 ** PWM Output  = Non Inverted
 **
 */

/** ------------------------------------------------------------------------*/
void  PWM_4_intialization();

/* -- Global -----------------------------------------------------------------
 **  PWM_4_OUTPUT.h()
 **
 **  parameters : uint8 duty
 **  return    : void
 **
 ** -- implementation ---------------------------------------------------------
 **  this function pass a value from 0 to 255 to the OCR2 register which
 **  controls the output voltage of pin PD7 from 0 to v maximum 5 volts
 **--------------------------------------------------------------------------*/
void  PWM_4_OUTPUT(uint8 duty);


#endif /* MCAL_PWM_PWM_H_ */
