/*
 * WIRE_INSP_Config.

 *
 *  Created on: Dec 30, 2020
 *      Author: Alaa Elnagar
 *      MOB   :+201019793647
 */

#ifndef WIRE_INSP_CONFIG_H_
#define WIRE_INSP_CONFIG_H_



#define MGPIO_PIN0   0
#define MGPIO_PIN1   1
#define MGPIO_PIN2   2
#define MGPIO_PIN3   3
#define MGPIO_PIN4   4
#define MGPIO_PIN5   5
#define MGPIO_PIN6   6
#define MGPIO_PIN7   7
#define MGPIO_PIN8   8
#define MGPIO_PIN9   9
#define MGPIO_PIN10  10
#define MGPIO_PIN11  11
#define MGPIO_PIN12  12
#define MGPIO_PIN13  13
#define MGPIO_PIN14  14
#define MGPIO_PIN15  15



#define MGPIO_PORTA  0
#define MGPIO_PORTB  1
#define MGPIO_PORTC  2



#define ARM_TARGET				1
#define AVR_TARGET 				0

#define CONTROLLER_SELECT		ARM_TARGET

#if  CONTROLLER_SELECT	==	AVR_CONTROLLER

/*defining the pins */
#define CHARGE_PIN					SEVEN
#define DISCHARGE_PIN				FIVE
#define CAPACITANCE_READ_PIN			SIX


/*the selected ports */

#define CHARGE_PORT						 PORTC_NUM
#define DISCHARGE_PORT					 PORTC_NUM
#define  CAPACITANCE_READ_PORT			 PORTA_NUM

#define DISCHARGE_RESISTOR_VALUE	     10000.0F



#elif CONTROLLER_SELECT	==	 ARM_TARGET

/*defining the pins */
#define CHARGE_PIN				  MGPIO_PIN2
#define CAPACITANCE_READ_PIN	  MGPIO_PIN0
#define DISCHARGE_PIN	          MGPIO_PIN1


/*the selected ports */

#define CHARGE_PORT						 MGPIO_PORTA
#define DISCHARGE_PORT					 MGPIO_PORTA
#define  CAPACITANCE_READ_PORT			 MGPIO_PORTA

#define DISCHARGE_RESISTOR_VALUE	     10000.0F


#endif




#endif /* WIRE_INSP_CONFIG_H_ */
