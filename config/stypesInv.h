/*
 * stypesInv.h
 *
 *  Created on: 24 de mai de 2023
 *      Author: LRS
 */

#ifndef S_TYPES_INV_H_
#define S_TYPES_INV_H_

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
}stypesMeasurementsInv_t;

typedef struct{
	float ig_d_ref;
	float ig_q_ref;
}stypesSimDataInv_t;

typedef struct{
	float ud;
	float uq;
}stypesControlInv_t;

typedef struct{
	float theta;
	float t_exec;
	float niters;
}stypesControllerDataInv_t;
//=============================================================================

#endif /* S_TYPES_INV_H_ */
