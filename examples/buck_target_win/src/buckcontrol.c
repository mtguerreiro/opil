/*
 * buckcontrol.c
 *
 *  Created on: 09.05.2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "buckcontrol.h"
#include "stdio.h"

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================

//#define DEBUG

// Control parameters
#define k1_raw           0.24279100529100536f
#define k2_raw           0.22154174015285136f
#define kr_raw           0.33185185185185195f
#define max_i            8.0f
#define min_i            0.0f
#define range_i          (max_i - min_i)
#define adc_res_i        4095.0f
#define adc_gain_i       (adc_res_i/range_i)
#define max_v_out        35.0f
#define min_v_out        0.0f
#define range_v_out      (max_v_out - min_v_out)
#define adc_res_v_out    4095.0f
#define adc_gain_v_out   (adc_res_v_out/range_v_out)
#define k1               (k1_raw/adc_gain_i)
#define k2               (k2_raw/adc_gain_v_out)
#define kr               kr_raw

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void buckcontrolInitialize(void)
{
#ifdef DEBUG
	printf("Initializing control... ");
	printf("Success!\n\r");
	
    printf("k1_raw=%f\n",k1_raw);
    printf("k2_raw=%f\n",k2_raw);
    printf("kr_raw=%f\n",kr_raw);
    printf("max_i=%f\n",max_i);
    printf("min_i=%f\n",min_i);
    printf("range_i=%f\n",range_i);
    printf("adc_res_i=%f\n",adc_res_i);
    printf("adc_gain_i=%f\n",adc_gain_i);
    printf("max_v_out=%f\n",max_v_out);
    printf("min_v_out=%f\n",min_v_out);
    printf("range_v_out=%f\n",range_v_out);
    printf("adc_res_v_out=%f\n",adc_res_v_out);
    printf("adc_gain_v_out=%f\n",adc_gain_v_out);
    printf("k1=%f\n",k1);
    printf("k2=%f\n",k2);
    printf("kr=%f\n",kr);
#endif // DEBUG
}
//-----------------------------------------------------------------------------
void buckcontrol
(
    void *ms,
    void *sd,
    void *ctl,
    void *ctlrdata
)
{
    stypesMeasurements_t *meas = (stypesMeasurements_t *)ms;
	stypesSimData_t *simdata = (stypesSimData_t *)sd;
	stypesControl_t *control = (stypesControl_t *)ctl;
	stypesControllerData_t *controllerdata = (stypesControllerData_t *)ctlrdata;
    
	static float D = 0.0f;

	D = simdata->V_ref*kr - k1*meas->i - min_i - k2*meas->v_out - min_v_out;
	
	if(D<0.0f)
		control->D = 0.0f;
	else if(D>1.0f)
		control->D = 1.0f;
	else
		control->D = D;
	
	controllerdata->t_exec = 42.0f;
	
#ifdef DEBUG
	printf("i=%f, v_out=%f, V_ref=%f\n", meas->i, meas->v_out, simdata->V_ref);
#endif //DEBUG
}
//-----------------------------------------------------------------------------
//=============================================================================
