/*
 * WIRE_INSP_Prog.c
 *  Created on: Dec 30, 2020
 *      Author: Alaa Elnagar
 *      MOB   :+201019793647
 */

#ifndef WIRE_INSP_PROG_C_
#define WIRE_INSP_PROG_C_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "ADC_interface.h"
#include "WIRE_INSP_Config.h"
#include "WIRE_INSP_Interface.h"

ADC_InitTypeDef  adc1_conf;
u32 Glob_U32ChargStartT;
u32 Glob_U32ChargStopT;
f64 volatile Glob_f32TotalChargeT;
WireData_St Wire1_Data;

//static u16  (*TIM_vIdGetCNTCallbk1)(TIM_TypeDef *TIMERx);

u8 Glob_U8FuncLOCK;


void WireInsp_vIdInit(WireData_St *Copy_StData) {

if(Glob_U8FuncLOCK==0){
	MGPIO_voidSetPinDirection( CHARGE_PORT, CHARGE_PIN , MGPIO_OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinValue( CHARGE_PORT, CHARGE_PIN ,MGPIO_LOW);
	MGPIO_voidSetPinDirection(  CAPACITANCE_READ_PORT, CAPACITANCE_READ_PIN, MGPIO_INPUT_ANALOG );
	MGPIO_voidSetPinDirection(DISCHARGE_PORT , DISCHARGE_PIN , MGPIO_INPUT_FLOATING );

/*STOP DISCHARGING */

		ADC_vInitStruct(&adc1_conf);
		ADC_xInit(ADC1,&adc1_conf);

	Copy_StData->InspRes =InspRes ;
    Copy_StData->WireType=WireType;

	Glob_U8FuncLOCK=1;
}
else {
	/*Do nothing*/
}
return ;

}
/*check the wire capacitance */


void WireInsp_VIdDischarge(){

	/*Discharge the capacitor */
		MGPIO_voidSetPinDirection(DISCHARGE_PORT , DISCHARGE_PIN , MGPIO_OUTPUT_2MHZ_PP );

		while ( ADC_u16GetSingleConv(ADC1,ADC_CHANNEL_0,ADC_SAMPLETIME_41CYCLES5) > 0 ){
	/*Start Discharging*/
			MGPIO_voidSetPinValue(DISCHARGE_PORT,DISCHARGE_PIN,MGPIO_LOW);

		}
	/*Sto Discharging */
		MGPIO_voidSetPinDirection(DISCHARGE_PORT , DISCHARGE_PIN , MGPIO_INPUT_FLOATING );


}

void WireInsp_VIdCheck (WireData_St *Copy_StData, volatile u32 *Copy_u32MstkOvFTime,u16 volatile *Copy_Pu16GetCNT)

{
    /*Intialize for one time */
	WireInsp_vIdInit(Copy_StData);
	/*RESET ALL DATA */
	Copy_StData->CapacitanceNF = 0;
	Copy_StData->CapacitanceUF=0;
	Copy_StData->FaultDistance=0;
	*Copy_u32MstkOvFTime=0      ;
	/*Get start time from the systic*/
	Glob_U32ChargStartT   =  *((volatile u32*) 0x40012c24  )     /*  **Copy_Pu16GetCNT    */               ;
	/*2,588 is 63.2% of 4,096, which corresponds to full-scale voltage*/
	while (ADC_u16GetSingleConv(ADC1,ADC_CHANNEL_0,ADC_SAMPLETIME_41CYCLES5) < 2588 )
	 {
		/*Start Charging */
		MGPIO_voidSetPinValue(CHARGE_PORT,CHARGE_PIN,MGPIO_HIGH);
      }

	/*STOP Charging */
	MGPIO_voidSetPinValue(CHARGE_PORT,CHARGE_PIN,MGPIO_LOW);
	Glob_U32ChargStopT     =*((volatile u32*) 0x40012c24  )  /* **Copy_Pu16GetCNT */;


	Glob_f32TotalChargeT=(Glob_U32ChargStopT-Glob_U32ChargStartT) ;

	/*Getting Capacitance */
	    Copy_StData->CapacitanceUF= (Glob_f32TotalChargeT/Copy_StData->InspRes);  /*(uF)*/

	if (Copy_StData->CapacitanceUF>=1){
			/*Do noting*/
	}
      /*Convert capacitance into microfrad*/
	else{

		Copy_StData->CapacitanceNF=Copy_StData->CapacitanceUF*1000;  /*(nf)*/

	}


	WireInsp_VIdDischarge();
	u8 brekpoint=0;

	 return ;

}







/*									INCASE OF USING SYSTIC 	 tIMER 										*/

//
//void WireInsp_VIdCheck(WireData_St *Copy_StData,u32 volatile  *Copy_u32MstkOvFTime,u32 (*MSTK_u32GetElapsedTime) (void)  ){
//
///*Intialize for one time */
//	WireInsp_vIdInit(Copy_StData);
//	/*RESET ALL DATA*/
//	Copy_StData->CapacitanceNF = 0;
//	Copy_StData->CapacitanceUF=0;
//	Copy_StData->FaultDistance=0;
//	*Copy_u32MstkOvFTime=0;
//
//	//Make sure that there is no charges in the target
//	//WireInsp_VIdDischarge();
//
//	/*Get start time from the systic*/
//	Glob_U32ChargStartT = MSTK_u32GetElapsedTime();
//	/* 2,588 is 63.2% of 4,096, which corresponds to full-scale voltage*/
//
//	while ( ADC_u16GetSingleConv(ADC1,ADC_CHANNEL_0,ADC_SAMPLETIME_41CYCLES5) < 2588 ){
//
//		/*Start Charging */
//		MGPIO_voidSetPinValue(CHARGE_PORT,CHARGE_PIN,MGPIO_HIGH);
//	}
//	/*STOP Charging */
//	MGPIO_voidSetPinValue(CHARGE_PORT,CHARGE_PIN,MGPIO_LOW);
//
//	Glob_U32ChargStopT =MSTK_u32GetElapsedTime();
//
//	if (*Copy_u32MstkOvFTime>0){
//		Glob_f32TotalChargeT=((Glob_U32ChargStopT) +(*Copy_u32MstkOvFTime))-(2*Glob_U32ChargStartT) ;
//	}
//	else{
//	Glob_f32TotalChargeT=Glob_U32ChargStopT-Glob_U32ChargStartT ;
//	}
//	/*Getting Capacitance */
//	Copy_StData->CapacitanceUF= (Glob_f32TotalChargeT/Copy_StData->InspRes);  /*(uF)*/
//
//	if (Copy_StData->CapacitanceUF>=1){
//			/*Do noting*/
//	}
///*Convert capacitance into microfrad*/
//	else{
//
//		Copy_StData->CapacitanceNF=Copy_StData->CapacitanceUF*1000;  /*(nf)*/
//	}
//
//
//	WireInsp_VIdDischarge();
//	u8 brekpoint=0;
//	 return ;
//
//}


















#endif /* WIRE_INSP_PROG_C_ */
