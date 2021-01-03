/*
 * SensorsPinsInerface.h

 *
 *  Created on: Dec 29, 2020
 *      Author: Alaa Elnagar
 */

#ifndef SENSORSPINSINERFACE_H_
#define SENSORSPINSINERFACE_H_

#define HIGH                   1
#define LOW                    0
#define MINUTE                 60000000
#define ENC_PPR		           20
#define PI			           3.14
#define WHEEL_RADIOUS          2.5         /*In cm */

#define WHEEL_CIRCUMESTANCE(r)(2*PI*r)

typedef struct {
 u64 ENC_u32Pulses;
 u32 ENC_u32RPM ;
 f32 ENC_f32LinerDistance;
 u32 ENC_u32BackDistance;

}Enc_Date_t ;



void SensorsPin_vIdInit (void);
void Enc_vIdGetEncData(Enc_Date_t *Enc_Data ,u8 Copy_u8TASK_Periodicity,u32 Copy_u32TickTime  );


#endif /* SENSORSPINSINERFACE_H_ */
