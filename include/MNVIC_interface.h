#ifndef _MNVIC_INTERFACE_H_
#define _MNVIC_INTERFACE_H_






#define MNVIC_PEND_SV      -6
#define MNVIC_SYSTICK      -5

#define MNVIC_SV_CALL      -4

#define MNVIC_MEM_MANAGE   -3
#define MNVIC_BUS_FAULT    -2
#define MNVIC_USAGE_FAULT  -1


#define MNVIC_EXTI0_IRQ      6
#define MNVIC_EXTI15_10_IRQ  40
#define MNVIC_DMA1_IRQ       11



#define MNVIC_EXTI0_IRQ      6
#define MNVIC_EXTI1_IRQ      7
#define MNVIC_EXTI2_IRQ      8
#define MNVIC_EXTI3_IRQ      9
#define MNVIC_EXTI4_IRQ      10
#define MNVIC_EXTI5_IRQ      23
#define MNVIC_EXTI6_IRQ      23
#define MNVIC_EXTI7_IRQ      23
#define MNVIC_EXTI8_IRQ      23
#define MNVIC_EXTI9_IRQ      23
#define MNVIC_EXTI10_IRQ     40
#define MNVIC_EXTI11_IRQ     40
#define MNVIC_EXTI12_IRQ     40
#define MNVIC_EXTI13_IRQ     40
#define MNVIC_EXTI14_IRQ     40
#define MNVIC_EXTI15_IRQ     40

#define MNVIC_TMR1_UP_IRQ     25







void MNVIC_voidInit(void);

void MNVIC_voidSetPrioirty( s8 Copy_u8INTID , u8 Copy_u8Group , u8 Copy_u8Sub );

void MNVIC_voidEnablePeri ( u8 Copy_u8INTID );
void MNVIC_voidDisablePeri( u8 Copy_u8INTID );

void MNVIC_voidSetPending   ( u8 Copy_u8INTID );
void MNVIC_voidClearPending ( u8 Copy_u8INTID );

u8 MNVIC_u8GetActive ( u8 Copy_u8INTID );


#endif
