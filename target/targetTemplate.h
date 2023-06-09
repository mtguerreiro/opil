/*
 * targetTemplate.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

#ifndef TARGET_TEMPLATE_H_
#define TARGET_TEMPLATE_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void targetTemplateInitialize(void *params);
//-----------------------------------------------------------------------------
int32_t targetTemplateUpdateMeasurements(void *meas, int32_t size);
//-----------------------------------------------------------------------------
int32_t targetTemplateUpdateSimData(void *simData, int32_t size);
//-----------------------------------------------------------------------------
void targetTemplateRunControl(void);
//-----------------------------------------------------------------------------
int32_t targetTemplateGetControl(void **control);
//-----------------------------------------------------------------------------
int32_t targetTemplateGetControllerData(void **controllerData);
//-----------------------------------------------------------------------------
//=============================================================================


#endif /* TARGET_TEMPLATE_H_ */
