/*
 * host.h
 *
 *  Created on: 12.05.2023
 *      Author: LRS
 */

#ifndef HOST_H_
#define HOST_H_

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
/**
 * @brief Initializes the host.
 *
 * @param meas Pointer to buffer holding measurement data in the simulation.
 * @param simData Pointer to buffer holding simulation data in the simulation.
 * @param control Pointer to buffer holding control data in the simulation.
 * @param controllerData Pointer to buffer holding controller data in the
 * 						 simulation.
 */
void hostInitialize(
		void *meas, void *simData,
		void *control, void *controllerData
		);
//-----------------------------------------------------------------------------
/**
 * @brief Updates simulation data.
 *
 * The data stored in the meas and simData buffers are internally copied to the
 * measurements and simulation data structures.
 */
void hostUpdateSimulation(void);
//-----------------------------------------------------------------------------
/**
 * @brief Gets measurements.
 *
 * The location of the structure holding the measurements data is stored in
 * meas.
 *
 * @param meas Address of pointer to hold the address of the
 * 			   measurement data structure.
 * @return The size of the measurement data structure, in bytes.
 */
int32_t hostGetMeasurements(void **meas);
//-----------------------------------------------------------------------------
/**
 * @brief Gets (additional) simulation data.
 *
 * The location of the structure holding the simulation data is stored in
 * simData.
 *
 * @param meas Address of pointer to hold the address of the
 * 			   measurement data structure.
 * @return The size of the measurement data structure, in bytes.
 */
int32_t hostGetSimData(void **simData);
//-----------------------------------------------------------------------------
/**
 * @brief Updates the control data.
 *
 * The internal control structure is updated with the new data.
 *
 * @param control Pointer to control data.
 * @param size Size of the control data, in bytes.
 * @return Always returns 0.
 */
int32_t hostUpdateControl(void *control, int32_t size);
//-----------------------------------------------------------------------------
/**
 * @brief Updates the controller data.
 *
 * The internal controller data structure is updated with the new data.
 *
 * @param controlelrData Pointer to controller data.
 * @param size Size of the controller data, in bytes.
 * @return Always returns 0.
 */
int32_t hostUpdateControllerData(void *controllerData, int32_t size);
//-----------------------------------------------------------------------------
/**
 * @brief Applies control and controller data to the simulation.
 */
void hostApplyControl(void);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* HOST_H_ */
