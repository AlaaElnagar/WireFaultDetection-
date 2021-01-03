/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 8-9-2020                                                                */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_private.h"
#include "Timer_interface.h"

/************************************************************************************************************* */
/*Static global variables*/
/************************************************************************************************************* */
/* Variable to define interval mode of Timer*/
static volatile uint8 TIM_u8IntervalMode;

/************************************************************************************************************* */
/*Private macros*/
/************************************************************************************************************* */
/* Local macros to set and get Interval mode for timer interrupt*/
#define TIM_SET_INTERVAL_MODE(MODE)                          TIM_u8IntervalMode = MODE
#define TIM_GET_INTERVAL_MODE()                               (TIM_u8IntervalMode & 1)
/************************************************************************************************************* */

static void (*Timer_CallBack)(void);
/************************************************************************************************************* */

void TIM_vInit(TIM_TypeDef *TIMERx,TIM_ConfigType *TIM_ConfigPtr)
{
	TIM_vSetPeriodValue(TIMERx,TIM_ConfigPtr->PeriodVal);

	TIM_vSetPrescalerValue(TIMERx,TIM_ConfigPtr->PrescalerVal);

	TIM_vSetURS_State(TIMERx,TIM_ConfigPtr->Update_event_State);

	TIM_vSetARR_Buffer(TIMERx,TIM_ConfigPtr->AutoReloadBuffer);

	TIM_vSetCMS_State(TIMERx,TIM_ConfigPtr->Center_Aligned_Mode);

	TIM_vSetDirection(TIMERx,TIM_ConfigPtr->Direction_State);

	TIM_vSetClkDiv(TIMERx,TIM_ConfigPtr->Clock_Div_Factor);

	TIM_vSetOPM_State(TIMERx,TIM_ConfigPtr->OnePulse_Mode);

	TIM_vSet_Interrupt(TIMERx,TIM_ConfigPtr->UDI_State);

	TIM_vSetCounterState(TIMERx,TIM_ConfigPtr->Counter_State);

}
/************************************************************************************************************* */

void TIM_vSetPeriodValue(TIM_TypeDef *TIMERx , uint32 Copy_u32PeriodVal)
{
	TIMERx->ARR = Copy_u32PeriodVal;
}
/************************************************************************************************************* */

void TIM_vSetPrescalerValue(TIM_TypeDef *TIMERx , uint32 Copy_u32PrescalerVal)
{
	TIMERx->PSC = Copy_u32PrescalerVal;
}
/************************************************************************************************************* */

void TIM_vSetCounterState(TIM_TypeDef *TIMERx,CNT_State Copy_x_State)
{
	switch(Copy_x_State)
	{
	case Disable_CNT:
		CLEAR_BIT(TIMERx->CR1,0);
		break;
	case Enable_CNT:
		SET_BIT(TIMERx->CR1,0);
		break;
	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetURS_State(TIM_TypeDef *TIMERx,URS_State Copy_xUpdate_event_State)
{
	switch(Copy_xUpdate_event_State)
	{
	case Disable_Update_Event:
		CLEAR_BIT(TIMERx->CR1,1);
		break;
	case Enable_Update_Event:
		SET_BIT(TIMERx->CR1,1);
		break;
	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetARR_Buffer(TIM_TypeDef *TIMERx,ARR_Buffer_State Copy_xAutoReloadBuffer)
{
	switch(Copy_xAutoReloadBuffer)
	{
	case Disable_ARR_Buffer:
		CLEAR_BIT(TIMERx->CR1,7);
		break;
	case Enable_ARR_Buffer:
		SET_BIT(TIMERx->CR1,7);
		break;
	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetCMS_State(TIM_TypeDef *TIMERx,CMS_State Copy_xCenter_Aligned_Mode)
{
	switch(Copy_xCenter_Aligned_Mode)
	{
	case Edge_Aligned_Mode:
		CLEAR_BIT(TIMERx->CR1,5);
		CLEAR_BIT(TIMERx->CR1,6);
		break;

	case Center_Aligned_Mode_1:
		SET_BIT(TIMERx->CR1,5);
		CLEAR_BIT(TIMERx->CR1,6);
		break;

	case Center_Aligned_Mode_2:
		CLEAR_BIT(TIMERx->CR1,5);
		SET_BIT(TIMERx->CR1,6);
		break;

	case Center_Aligned_Mode_3:
		SET_BIT(TIMERx->CR1,5);
		SET_BIT(TIMERx->CR1,6);
		break;

	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetDirection(TIM_TypeDef *TIMERx,DIR_State Copy_xDirection_State)
{
	switch(Copy_xDirection_State)
	{
	case UpCounter:
		CLEAR_BIT(TIMERx->CR1,4);
		break;
	case DownCounter:
		SET_BIT(TIMERx->CR1,4);
		break;
	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetClkDiv(TIM_TypeDef *TIMERx,Clk_Div Copy_xClock_Div_Factor)
{
	switch(Copy_xClock_Div_Factor)
	{
	case Div_1:
		CLEAR_BIT(TIMERx->CR1,8);
		CLEAR_BIT(TIMERx->CR1,9);
		break;

	case Div_2:
		SET_BIT(TIMERx->CR1,8);
		CLEAR_BIT(TIMERx->CR1,9);
		break;

	case Div_3:
		CLEAR_BIT(TIMERx->CR1,8);
		SET_BIT(TIMERx->CR1,9);
		break;

	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetOPM_State(TIM_TypeDef *TIMERx,OPM_State Copy_xOnePulse_Mode)
{
	switch(Copy_xOnePulse_Mode)
	{
	case Counter_Not_stopped_Update_Event:
		CLEAR_BIT(TIMERx->CR1,3);
		break;

	case Counter_stopped_Update_Event:
		SET_BIT(TIMERx->CR1,3);
		break;

	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSet_Interrupt(TIM_TypeDef *TIMERx,TIM_Update_INT_State Copy_xIntState)
{
	switch(Copy_xIntState)
	{
	case Disable_TIM_Update_Interrupt:
		CLEAR_BIT(TIMERx->DIER,0);
		break;
	case Enable_TIM_Update_Interrupts:
		SET_BIT(TIMERx->DIER,0);
		break;
	default:
		break;
	}
}
/************************************************************************************************************* */

void TIM_vSetBusyWait(TIM_TypeDef *TIMERx,uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe)
{
	/*Assign ticks to load register*/
	TIMERx->ARR = Copy_u32Ticks * Copy_u32TicksTybe;
	/*Start timer*/
	SET_BIT(TIMERx->CR1,0);
	/*Wait until busy wait flag is raised */
	while(GET_BIT(TIMERx->SR,0) == 0);
	/*Stop timer*/
	CLEAR_BIT(TIMERx->CR1,0);
	/*Clear Timer registers*/
	TIMERx->ARR = 0;
	/*Clear interrupt flag*/
	CLEAR_BIT(TIMER1->SR,0);
}

/************************************************************************************************************* */

void TIM_vSetIntervalSingle  (TIM_TypeDef *TIMERx, uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe, void (*Copy_vpFuncPtr)(void) )
{
	/*Stop timer*/
	CLEAR_BIT(TIMERx->CR1,0);
	/*Clear Timer registers*/
	TIMERx->ARR = 0;
	/*Assign ticks to load register*/
	TIMERx->ARR = Copy_u32Ticks * Copy_u32TicksTybe ;
	/* Assign callBack function */
	Timer_CallBack = Copy_vpFuncPtr;
	/* Set Mode to Single */
	TIM_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);
	/*Enable Timer interrupt*/
	SET_BIT(TIMERx->DIER,0);
	/*Start timer*/
	SET_BIT(TIMERx->CR1,0);
}

/************************************************************************************************************* */

void TIM_vSetIntervalPeriodic(TIM_TypeDef *TIMERx,uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe , void (* Copy_vpFuncPtr) (void))
{
	/*Assign ticks to load register*/
	TIMERx->ARR = Copy_u32Ticks * Copy_u32TicksTybe ;
	/*Assign the function to the callback function */
	Timer_CallBack = Copy_vpFuncPtr;
	/* Set Mode to Single */
	TIM_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
	/*Enable Timer interrupt*/
	SET_BIT(TIMERx->DIER,0);
	/*Start the counter*/
	SET_BIT(TIMERx->CR1,0);
}
/************************************************************************************************************* */

void TIM1_UP_IRQHandler (void)
{
	if(TIM_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
	{
		/*Disable Timer interrupt*/
		CLEAR_BIT(TIMER1->DIER,0);
		/*Stop the counter*/
		CLEAR_BIT(TIMER1->CR1,0);
		/*Clear timer registers*/
		TIMER1->ARR = 0;
	}
	else
	{
		/*No Action*/
	}

	/*Execute callback function*/
	Timer_CallBack();

	/*Clear interrupt flag*/
	CLEAR_BIT(TIMER1->SR,0);
}


void  TIM_vIdGetCNT(TIM_TypeDef *TIMERx,u16 volatile*Copy_Pu16GetCNT)
  {
	Copy_Pu16GetCNT    =   &TIMERx->CNT    ;
	u16 volatile dd1   =   *Copy_Pu16GetCNT;
	u16 volatile dd2   =   *Copy_Pu16GetCNT;
	u16 volatile dd3   =   *Copy_Pu16GetCNT;
	u16 volatile dd4   =   *Copy_Pu16GetCNT;

  }










