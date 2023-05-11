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

	float *p;

	p = (float *)vplecsMeas;
	xhMeasurements.ii_a_k = (float)(p[0]);
	xhMeasurements.ii_b_k = (float)(p[1]);
	xhMeasurements.ii_c_k = (float)(p[2]);

	xhMeasurements.ig_a_k = (float)(p[3]);
	xhMeasurements.ig_b_k = (float)(p[4]);
	xhMeasurements.ig_c_k = (float)(p[5]);

	xhMeasurements.vc_a_k = (float)(p[6]);
	xhMeasurements.vc_b_k = (float)(p[7]);
	xhMeasurements.vc_c_k = (float)(p[8]);

	xhMeasurements.vg_ab_k = (float)(p[9]);
	xhMeasurements.vg_ac_k = (float)(p[10]);
	xhMeasurements.vg_bc_k = (float)(p[11]);

	p = (float *)vplecsSimData;
	xhSimData.ig_d_ref = (float)(p[0]);
	xhSimData.ig_q_ref = (float)(p[1]);
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
	p[0] = xhControl.ud;
	p[1] = xhControl.uq;

	p = (float *)vplecsControllerData;
	p[0] = xhControllerData.theta;
	p[1] = xhControllerData.niters;
	p[2] = xhControllerData.t_exec;
}
//-----------------------------------------------------------------------------
//=============================================================================
