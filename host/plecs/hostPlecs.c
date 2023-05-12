/*
 * hostPlecs.c
 *
 *  Created on: 06.05.2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "hostPlecs.h"
#include "../common/stypes.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
static stypesMeasurements_t xhMeasurements;
static stypesSimData_t xhSimData;
static stypesControl_t xhControl;
static stypesControllerData_t xhControllerData;

static void *vplecsMeas;
static void *vplecsSimData;
static void *vplecsControl;
static void *vplecsControllerData;
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

	uint8_t *dst, *src;
	uint32_t k;

	src = (uint8_t *)( vplecsMeas );
	dst = (uint8_t *)( &xhMeasurements );
	k = sizeof(stypesMeasurements_t);
	while(k--) *dst++ = *src++;

	src = (uint8_t *)( vplecsSimData );
	dst = (uint8_t *)( &xhSimData );
	k = sizeof(stypesSimData_t);
	while(k--) *dst++ = *src++;
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

	uint8_t *src, *dst;
	uint32_t k;

	dst = (uint8_t *)( vplecsControl );
	src = (uint8_t *)( &xhControl );
	k = sizeof(stypesControl_t);
	while(k--) *dst++ = *src++;

	dst = (uint8_t *)( vplecsControllerData );
	src = (uint8_t *)( &xhControllerData );
	k = sizeof(stypesControllerData_t);
	while(k--) *dst++ = *src++;
}
//-----------------------------------------------------------------------------
//=============================================================================
