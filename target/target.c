/*
 * target.c
 *
 *  Created on: 8 de mai de 2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "target.h"

#include "invcontrol.h"
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

static targetControlInit_t xcontrolInit = 0;
static targetControlRun_t xcontrolRun = 0;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void targetInitialize(
		targetControlInit_t controlInit, targetControlRun_t controlRun
		){

	xcontrolInit = controlInit;
	xcontrolRun = controlRun;
}
//-----------------------------------------------------------------------------
int32_t targetUpdateMeasurements(void *meas, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xtMeasurements );
	src = (uint8_t *)( meas );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
int32_t targetUpdateSimData(void *simData, int32_t size){

	uint8_t *src, *dst;

	dst = (uint8_t *)( &xtSimData );
	src = (uint8_t *)( simData );

	while(size--) *dst++ = *src++;

	return 0;
}
//-----------------------------------------------------------------------------
void targetInitializeControl(void){

	if( xcontrolInit ) xcontrolInit();
}
//-----------------------------------------------------------------------------
void targetRunControl(void){

	if( xcontrolRun )
		xcontrolRun(&xtMeasurements, &xtSimData, &xtControl, &xtControllerData);
}
//-----------------------------------------------------------------------------
int32_t targetGetControl(void **control){

	*control = (void *)( &xtControl );

	return sizeof(stypesControl_t);
}
//-----------------------------------------------------------------------------
int32_t targetGetControllerData(void **controllerData){

	*controllerData = (void *)( &xtControllerData );

	return sizeof(stypesControllerData_t);
}
//-----------------------------------------------------------------------------
//=============================================================================
