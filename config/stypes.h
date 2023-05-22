/*
 * stypes.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

#ifndef S_TYPES_H_
#define S_TYPES_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
typedef struct{
	float ii_a_k;
	float ii_b_k;
	float ii_c_k;

	float ig_a_k;
	float ig_b_k;
	float ig_c_k;

	float vc_a_k;
	float vc_b_k;
	float vc_c_k;

	float vg_ab_k;
	float vg_ac_k;
	float vg_bc_k;
}stypesMeasurements_t;

typedef struct{
	float ig_d_ref;
	float ig_q_ref;
}stypesSimData_t;

typedef struct{
	float ud;
	float uq;
}stypesControl_t;

typedef struct{
	float theta;
	float t_exec;
	float niters;
}stypesControllerData_t;
//=============================================================================

#endif /* S_TYPES_H_ */
