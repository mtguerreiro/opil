/*
 * stypes.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

#ifndef S_TYPES_MMC_H_
#define S_TYPES_MMC_H_

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
	float i[7];
	float v[4];
}stypesMeasurements_t;

typedef struct{
	float P;
	float Q;
}stypesSimData_t;

typedef struct{
	float m[6];
}stypesControl_t;

typedef struct{
	float t_exec;
}stypesControllerData_t;
//=============================================================================

#endif /* S_TYPES_MMC_H_ */
