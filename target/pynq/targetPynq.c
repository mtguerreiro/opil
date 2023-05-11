/*
 * targetPynq.c
 *
 *  Created on: 8 de mai de 2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "target/pynq/targetPynq.h"
#include "common/stypes.h"

#include "stdio.h"

#include "invcontrol.h"
//#include "invsfb.h"
//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
static stypesMeasurements_t xtMeasurements;
static stypesSimData_t xtSimData;
static stypesControl_t xtControl;
static stypesControllerData_t xtControllerData;

static float k1 = (float)(3.3595991e+07);
static float k2 = (float)(8.0000000e+03);
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void targetPynqInitialize(void *params){

	invcontrolInitialize();
}
//-----------------------------------------------------------------------------
int32_t targetPynqUpdateMeasurements(void *meas, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xtMeasurements );
	src = (uint8_t *)( meas );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
int32_t targetPynqUpdateSimData(void *simData, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xtSimData );
	src = (uint8_t *)( simData );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
void targetPynqRunControl(void){

	invcontrol(&xtMeasurements, &xtSimData, &xtControl, &xtControllerData);
	//invsfb(&xtMeasurements, &xtSimData, &xtControl, &xtControllerData);

//	xtControl.u = k1 * xtSimData.ref - k1 * xtMeasurements.y - k2 * xtMeasurements.y_dot;
//
//	xtControllerData.t_exec = 5.03f;
}
//-----------------------------------------------------------------------------
int32_t targetPynqGetControl(void **control){

	*control = (void *)( &xtControl );

	return sizeof(stypesControl_t);
}
//-----------------------------------------------------------------------------
int32_t targetPynqGetControllerData(void **controllerData){

	*controllerData = (void *)( &xtControllerData );

	return sizeof(stypesControllerData_t);
}
//-----------------------------------------------------------------------------
//=============================================================================
