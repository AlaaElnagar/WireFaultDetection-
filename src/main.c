/*
 * main.c

 *
 *  Created on: Dec 30, 2020
 *  Created on: Dec 29, 2020
 *      Author: AlaaElnagar
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "MSTK_interface.h"
#include "STMU_interface.h"
#include "Timer_interface.h"
#include "ADC_interface.h"
#include "SensorsPinsInerface.h"
#include "WIRE_INSP_Interface.h"

u8  x = 0;

volatile u32 Enc_U32Counter        ;
volatile u32 Enc_U32Revelution     ;
volatile u32 Enc_U32NewRevelution  ;
volatile u32 Enc_U32OldRevelution  ;
Enc_Date_t encoder1;
Tasks_t TASK1 ,TASK2,TASK3,TASK4;
WireData_St Wire1_Data;

u32 Glob_u32SchedStartT;
u32 volatile  T1;
u16 volatile  T2=0;
u32 volatile *Glob_u32MstkOvFTime=&T1 ;
u32 cap1;
u32 cap2;
u16 volatile *Glob_Pu16GetCNT = &T2  ;

u16 Glob_u16TIMtickSys ;
u16 Glob_u16TIMtickNum ;


void Timr1_VidIsrFunc(void)
{

*Glob_u32MstkOvFTime+=(Glob_u16TIMtickNum * Glob_u16TIMtickSys);
cap1=Wire1_Data.CapacitanceNF;
cap2=Wire1_Data.CapacitanceUF;
u8 DEBUGa=9;

}



void TASK1_vIdEncoderFunc(){

	//*Glob_u32MstkOvFTime+=(ms*TASK1.Periodicity *Glob_u32SchedStartT);

	Enc_vIdGetEncData(&encoder1,1,100 ) ;

u8 DebugVar =0;

}
void TASK2_vidThermistorFunc(){



}


void TASK3_vidBatteryLvlFunc(){



}

void TASK4_vidWireInspec(){



}
void TASK5_vidSysTicCount(){



}


int main(void)

{

	MRCC_voidInitSysClock();//Initialization System Clock Speed 8Mhz Crystel
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOA_EN );//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOB_EN );//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOC_EN );//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , (u8)MRCC_ADC1_EN);//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_TIMER_1_EN) ;

	/*Timer 1 */
	    TIM_ConfigType    		   timer1                    ;
		timer1.Counter_State     = Enable_CNT                ;
		timer1.PrescalerVal      = 8                         ;
		timer1.Direction_State = UpCounter                   ;
		TIM_vInit(TIMER1 , &timer1)                          ;

		Glob_u16TIMtickSys    = (u16)  TIM_TICKS_MS          ;
		Glob_u16TIMtickNum    =  1000                          ;

		TIM_vSetIntervalPeriodic(TIMER1,Glob_u16TIMtickNum ,Glob_u16TIMtickSys	 ,&Timr1_VidIsrFunc) ;
		MNVIC_voidEnablePeri( MNVIC_TMR1_UP_IRQ );

        SensorsPin_vIdInit ();

        TASK1.Task_Func = TASK1_vIdEncoderFunc;
        TASK1.Periodicity = 1;
        TASK2.Task_Func = TASK2_vidThermistorFunc;
        TASK2.Periodicity = 3000;
        TASK3.Task_Func = TASK3_vidBatteryLvlFunc;
        TASK3.Periodicity = 2000;
        TASK4.Task_Func = TASK4_vidWireInspec;
        TASK4.Periodicity = 1000;

        STMU_VidAddTask(TASK1) ;
        STMU_VidAddTask(TASK2) ;
        STMU_VidAddTask(TASK3) ;
        STMU_VidAddTask(TASK4) ;


   /*This function is responsible for starting TMU scheduler with a specific system tick (from 0 to 16777ms)*/

    Glob_u32SchedStartT=120							  ;

	STMU_VidStartSchudler(Glob_u32SchedStartT)        ;

	TIM_vIdGetCNT(TIMER1,Glob_Pu16GetCNT)             ;

	 while(1){

	 WireInsp_VIdCheck(&Wire1_Data,Glob_u32MstkOvFTime,Glob_Pu16GetCNT) ;

	       }

	return 0;

            }


