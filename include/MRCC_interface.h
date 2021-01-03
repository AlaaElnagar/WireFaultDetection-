

#ifndef _MRCC_INTERFACE_
#define _MRCC_INTERFACE_

#define MRCC_AHB    0
#define MRCC_APB1   1
#define MRCC_APB2   2

/* AHB */

/* APB2 */


enum  {

	MRCC_GPIOA_EN = 2 ,
	MRCC_GPIOB_EN = 3 ,
	MRCC_GPIOC_EN = 4 ,
	MRCC_AFIO_EN   =0 ,
	MRCC_ADC1_EN   = 9,
	MRCC_ADC2_EN ,
    MRCC_TIMER_1_EN   ,
	MRCC_ADC3_EN=15

};



#define MRCC_DMA1_EN   0

/* APB1 */

void MRCC_voidInitSysClock(void);


void MRCC_voidEnablePerClock( u8 Copy_u8BusId , u8 Copy_u8PerId );

void MRCC_voidDisablePerClock( u8 Copy_u8BusId , u8 Copy_u8PerId );

#endif 
