/*
 * targetPynq.c
 *
 *  Created on: 8 de mai de 2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "target.h"
#include "common/stypes.h"

#include "invcontrol.h"
//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
typedef void (*targetControlInit_t)(void);
typedef void (*targetControlRun_t)(
		stypesMeasurements_t *meas,
		stypesSimData_t *simData,
		stypesControl_t *control,
		stypesControllerData_t *controllerData
		);
//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
static stypesMeasurements_t xtMeasurements;
static stypesSimData_t xtSimData;
static stypesControl_t xtControl;
static stypesControllerData_t xtControllerData;

static targetControlInit_t xcontrolInit = invcontrolInitialize;
static targetControlRun_t xcontrolRun = invcontrol;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void targetInitialize(void){

	if( xcontrolInit ) xcontrolInit();
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
