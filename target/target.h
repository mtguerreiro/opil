/*
 * target.h
 *
 *  Created on: 8 de mai de 2023
 *      Author: LRS
 */

#ifndef TARGET_H_
#define TARGET_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

#include "config/stypes.h"
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
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * @brief Initializes the target.
 */
void targetInitialize(
		targetControlInit_t controlInit, targetControlRun_t controlRun
		);
//-----------------------------------------------------------------------------
/**
 * @brief Updates measurements data.
 *
 * The internal measurements structure is updated with the new data.
 *
 * @param meas Pointer to measurements data.
 * @param size Size of the measurements data, in bytes.
 * @return Always returns 0.
 */
int32_t targetUpdateMeasurements(void *meas, int32_t size);
//-----------------------------------------------------------------------------
/**
 * @brief Updates simulation data.
 *
 * The internal simulation data structure is updated with the new data.
 *
 * @param simData Pointer to simulation data.
 * @param size Size of the simulation data, in bytes.
 * @return Always returns 0.
 */
int32_t targetUpdateSimData(void *simData, int32_t size);
//-----------------------------------------------------------------------------
void targetInitializeControl(void);
//-----------------------------------------------------------------------------
/**
 * @brief Runs the control algorithm.
 */
void targetRunControl(void);
//-----------------------------------------------------------------------------
/**
 * @brief Gets control data.
 *
 * The location of the structure holding the control data is stored in control.
 *
 * @param control Address of pointer to hold the address of the
 * 			      control data structure.
 * @return The size of the control data structure, in bytes.
 */
int32_t targetGetControl(void **control);
//-----------------------------------------------------------------------------
/**
 * @brief Gets controller data.
 *
 * The location of the structure holding the controller data is stored in
 * controllerData.
 *
 * @param controllerData Address of pointer to hold the address of the
 * 			             controller data structure.
 * @return The size of the control data structure, in bytes.
 */
int32_t targetGetControllerData(void **controllerData);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* TARGET_H_ */
