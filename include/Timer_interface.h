/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 8-9-2020                                                                */
/*////////////////////////////////////////////////////////////////////////////// */
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "Timer_private.h"

/************************************************************************************************************* */
/*TIM ticks types*/
#define TIM_TICKS_US                    1
#define TIM_TICKS_MS					1000
#define TIM_TICKS_S						1000000

/************************************************************************************************************* */
/* TIM clock source options*/
#define	TIM_CLK_SRC_AHB_DIVIDED_BY_8        0
#define	TIM_CLK_SRC_AHB						1

/************************************************************************************************************* */
/* TIM Interval modes*/
#define TIM_SINGLE_INTERVAL_MODE		    0
#define TIM_PERIODIC_INTERVAL_MODE	     	1

/************************************************************************************************************* */
typedef enum
{
	Disable_CNT,
	Enable_CNT
}CNT_State;

typedef enum
{
	Disable_TIM_Update_Interrupt,
	Enable_TIM_Update_Interrupts
}TIM_Update_INT_State;

typedef enum
{
	Disable_Update_Event,
	Enable_Update_Event
}URS_State;

typedef enum
{
	Disable_ARR_Buffer,
	Enable_ARR_Buffer
}ARR_Buffer_State;

typedef enum
{
	Edge_Aligned_Mode,
	Center_Aligned_Mode_1,
	Center_Aligned_Mode_2,
	Center_Aligned_Mode_3
}CMS_State;

typedef enum
{
	UpCounter,
	DownCounter
}DIR_State;

typedef enum
{
	Div_1,
	Div_2,
	Div_3
}Clk_Div;

typedef enum
{
	Counter_Not_stopped_Update_Event,
	Counter_stopped_Update_Event
}OPM_State;

typedef struct
{
	uint32 PeriodVal;
	uint32 PrescalerVal;
	URS_State Update_event_State;
	ARR_Buffer_State AutoReloadBuffer;
	CMS_State Center_Aligned_Mode;
	CNT_State Counter_State;
	DIR_State Direction_State;
	Clk_Div Clock_Div_Factor;
	OPM_State OnePulse_Mode;
	TIM_Update_INT_State UDI_State;
}TIM_ConfigType;


void TIM_vInit(TIM_TypeDef *TIMERx,TIM_ConfigType *TIM_ConfigPtr);



void TIM_vSetPeriodValue(TIM_TypeDef *TIMERx , uint32 PeriodVal);
void TIM_vSetPrescalerValue(TIM_TypeDef *TIMERx , uint32 PrescalerVal);


void TIM_vSetCounterState(TIM_TypeDef *TIMERx,CNT_State Copy_xState);
void TIM_vSetURS_State(TIM_TypeDef *TIMERx,URS_State Copy_xUpdate_event_State);
void TIM_vSetARR_Buffer(TIM_TypeDef *TIMERx,ARR_Buffer_State Copy_xAutoReloadBuffer);
void TIM_vSetCMS_State(TIM_TypeDef *TIMERx,CMS_State Center_Copy_xAligned_Mode);
void TIM_vSetDirection(TIM_TypeDef *TIMERx,DIR_State Copy_xDirection_State);
void TIM_vSetClkDiv(TIM_TypeDef *TIMERx,Clk_Div Copy_xClock_Div_Factor);
void TIM_vSetOPM_State(TIM_TypeDef *TIMERx,OPM_State Copy_xOnePulse_Mode);
void TIM_vSet_Interrupt(TIM_TypeDef *TIMERx,TIM_Update_INT_State Copy_xIntState);
void TIM_vSetBusyWait(TIM_TypeDef *TIMERx,uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe);
void TIM_vSetIntervalSingle  (TIM_TypeDef *TIMERx,uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe, void (*Copy_vpFuncPtr)(void) );
void TIM_vSetIntervalPeriodic(TIM_TypeDef *TIMERx,uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe , void (* Copy_vpFuncPtr) (void));

void  TIM_vIdGetCNT(TIM_TypeDef *TIMERx,u16 volatile*Copy_Pu16GetCNT);

#endif
