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
}stypesMeasurementsMmc_t;

typedef struct{
	float P;
	float Q;
}stypesSimDataMmc_t;

typedef struct{
	float m[6];
}stypesControlMmc_t;

typedef struct{
	float t_exec;
}stypesControllerDataMmc_t;
//=============================================================================

#endif /* S_TYPES_MMC_H_ */
