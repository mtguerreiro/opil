/*
 * opilhost.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: marco
 */

#ifndef OPILHOST_H_
#define OPILHOST_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
#define OPIL_HOST_CONFIG_BUFFER_SIZE	512

/**
 * Signature of function to open a target connection.
 *
 * @param params Generic parameters to be passed to the function.
 * @return The function should return 0 if the connection was successful.
 */
typedef int32_t (*ohCommOpenConn_t)(void *params);

/**
 * Signature of function to close a target connection.
 *
 * @param params Generic parameters to be passed to the function.
 * @return The function should return 0 if the disconnection was successful.
 */
typedef int32_t (*ohCommCloseConn_t)(void *params);

/**
 * Signature of function to send data to the target.
 *
 * @param buffer Pointer to buffer holding data to be sent.
 * @param size Size of buffer, in bytes.
 * @return The function should return 0 if data was sent successfully.
 */
typedef int32_t (*ohCommSendData_t)(void *buffer, int32_t size);

/**
 * Signature of function to receive data from the target.
 *
 * @param buffer Pointer to buffer to hold data.
 * @param size Number of bytes to receive.
 * @return The function should return 0 if data was received successfully.
 */
typedef int32_t (*ohCommReceiveData_t)(void *buffer, int32_t size);

typedef void (*ohUpdateSim_t)(void);
typedef int32_t (*ohGetMeas_t)(void **meas);
typedef int32_t (*ohGetSimData_t)(void **simdata);

typedef int32_t (*ohUpdateControl_t)(void *control, int32_t size);
typedef int32_t (*ohUpdateControllerData_t)(void *controllerdata, int32_t size);
typedef void (*ohApplyControl_t)(void);

typedef struct{
	ohCommOpenConn_t openConn;
	ohCommCloseConn_t closeConn;
	ohCommSendData_t sendData;
	ohCommReceiveData_t receiveData;
}opilhostCommConfig_t;

typedef struct{
	ohUpdateSim_t updateSim;
	ohGetMeas_t getMeas;
	ohGetSimData_t getSimData;

	ohUpdateControl_t updateControl;
	ohUpdateControllerData_t updateControllerData;
	ohApplyControl_t applyControl;
}opilhostSimConfig_t;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
int32_t opilhostInitialize(
		opilhostCommConfig_t *commConfig,
		opilhostSimConfig_t* simConfig
		);
//-----------------------------------------------------------------------------
int32_t opilhostConnectToTarget(void *params);
//-----------------------------------------------------------------------------
int32_t opilhostExchangeDataTarget(void);
//-----------------------------------------------------------------------------
int32_t opilhostDisconnectFromTarget(void *params);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* OPILHOST_H_ */
