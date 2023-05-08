/*
 * hostPlecs.c
 *
 *  Created on: 06.05.2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "host/plecs/hostPlecs.h"
#include "common/stypes.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
stypesMeasurements_t xhMeasurements;
stypesSimData_t xhSimData;
stypesControl_t xhControl;
stypesControllerData_t xhControllerData;

void *vplecsMeas;
void *vplecsSimData;
void *vplecsControl;
void *vplecsControllerData;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void hostPlecsInitialize(
		void *meas, void *simData,
		void *control, void *controllerData){

	vplecsMeas = meas;
	vplecsSimData = simData;
	vplecsControl = control;
	vplecsControllerData = controllerData;
}
//-----------------------------------------------------------------------------
void hostPlecsUpdateSimulation(void){

	float *p;

	p = (float *)vplecsMeas;
	xhMeasurements.y = (float)(p[0]);
	xhMeasurements.y_dot = (float)(p[1]);

	p = (float *)vplecsSimData;
	xhSimData.ref = (float)(p[0]);
}
//-----------------------------------------------------------------------------
int32_t hostPlecsGetMeasurements(void **meas){

	*meas = (void *)( &xhMeasurements );

	return sizeof(stypesMeasurements_t);
}
//-----------------------------------------------------------------------------
int32_t hostPlecsGetSimData(void **simData){

	*simData = (void *)( &xhSimData );

	return sizeof(stypesSimData_t);
}
//-----------------------------------------------------------------------------
int32_t hostPlecsUpdateControl(void *control, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xhControl );
	src = (uint8_t *)( control );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
int32_t hostPlecsUpdateControllerData(void *controllerData, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xhControllerData );
	src = (uint8_t *)( controllerData );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
void hostPlecsApplyControl(void){

	float *p;

	p = (float *)vplecsControl;
	p[0] = xhControl.u;

	p = (float *)vplecsControllerData;
	p[0] = xhControllerData.t_exec;
}
//-----------------------------------------------------------------------------
//=============================================================================
