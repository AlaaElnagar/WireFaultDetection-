/*
 * WIRE_INSP_Interface.h

 *
 *  Created on: Dec 30, 2020
 *      Author: Alaa Elnagar
 *      MOB   :+201019793647
 */

#ifndef WIRE_INSP_INTERFACE_H_
#define WIRE_INSP_INTERFACE_H_

#define ms     1000
#define us     1


typedef struct {

	u16 WireType     ;    /*To change Correction factors according to*/
	f32 InspRes      ;    /*inspection resistance in ohm */
	u16 FaultDistance;      /*Length in cm*/
	f32 CapacitanceUF;
	f32 CapacitanceNF;

}WireData_St;


enum Values{
	WireType =1 ,
	InspRes  =1000000,
	FaultDistance=1,
  Capacitance=1
 };




void WireInsp_vIdInit(WireData_St *Copy_StData) ;
void WireInsp_VIdCheck (WireData_St *Copy_StData,u32 volatile  *Copy_u32MstkOvFTime,u16 volatile *Copy_Pu16GetCNT);


















#endif /* WIRE_INSP_INTERFACE_H_ */
