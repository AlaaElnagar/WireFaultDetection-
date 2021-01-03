/*
 * SensrsPinsConfig.h
 *
 *  Created on: Dec 29, 2020
 *      Author: PC
 */

#ifndef SENSRSPINSCONFIG_H_
#define SENSRSPINSCONFIG_H_

/*
 *pOrt SeleCtion

 00 -       MGPIO_PORTA
 10 -       MGPIO_PORTB
 20 -       MGPIO_PORTC

 *pIns SeleCtion

 30 -       MGPIO_PIN0
 40 -       MGPIO_PIN1
 50 -       MGPIO_PIN2
 60 -       MGPIO_PIN3
 70 -       MGPIO_PIN4
 80 -       MGPIO_PIN5
 90 -       MGPIO_PIN6
 10 -       MGPIO_PIN7
 11 -       MGPIO_PIN8
 12 -       MGPIO_PIN9
 13 -       MGPIO_PIN10
 14 -       MGPIO_PIN11
 15 -       MGPIO_PIN12
 16 -       MGPIO_PIN13
 17 -       MGPIO_PIN14
 18 -       MGPIO_PIN15

*/





/*used sensors pins configration*/

#define ENCODER_A_PIN                        MGPIO_PIN0
#define ENCODER_B_PIN                        MGPIO_PIN1
#define ENCODER_SWITCH_PIN                   MGPIO_PIN2
#define BATTERYLVL_PIN	                     MGPIO_PIN3
#define THERMISTOR_PIN                       MGPIO_PIN4


/*used sensors port configration*/


/*eNCODER pIN A*/
#define ENCODER_PA_PORT 					MGPIO_PORTB
/*eNCODER pIN B*/
#define ENCODER_PB_PORT 					MGPIO_PORTB
#define ENCODER_SWITCH_PORT 			    MGPIO_PORTB


#define BATTERYLVL_PORT                 MGPIO_PORTA
#define THERMISTOR_PORT                 MGPIO_PORTA















#endif /* SENSRSPINSCONFIG_H_ */
