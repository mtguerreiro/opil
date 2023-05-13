/*
 * opiltarget.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

#ifndef OPILTARGET_H_
#define OPILTARGET_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * Size of buffer used to temporarily store received data.
 * The size is in bytes.
 */
#define OPIL_TARGET_CONFIG_BUFFER_SIZE	512
//-----------------------------------------------------------------------------
/**
 * Signature of function to open a host connection.
 *
 * @param params Generic parameters to be passed to the function.
 * @return The function should return 0 if the connection was successful.
 */
typedef int32_t (*otCommOpenConn_t)(void *params);
//-----------------------------------------------------------------------------
/**
 * Signature of function to close a host connection.
 *
 * @param params Generic parameters to be passed to the function.
 * @return The function should return 0 if the disconnection was successful.
 */
typedef int32_t (*otCommCloseConn_t)(void *params);
//-----------------------------------------------------------------------------
/**
 * Signature of function to send data to the host.
 *
 * @param buffer Pointer to buffer holding data to be sent.
 * @param size Size of buffer, in bytes.
 * @return The function should return 0 if data was sent successfully.
 */
typedef int32_t (*otCommSendData_t)(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
/**
 * Signature of function to receive data from the host.
 *
 * @param buffer Pointer to buffer to hold data.
 * @param size Number of bytes to receive.
 * @return The function should return 0 if data was received successfully.
 */
typedef int32_t (*otCommReceiveData_t)(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
typedef int32_t (*otUpdateMeas_t)(void *meas, int32_t size);
typedef int32_t (*otUpdateSimData_t)(void *simData, int32_t size);

typedef void (*otInitControl_t)(void);
typedef void (*otRunControl_t)(void);

typedef int32_t (*otGetControl_t)(void **control);
typedef int32_t (*otGetControllerData_t)(void **controllerData);

typedef struct{
	otCommOpenConn_t openConn;
	otCommCloseConn_t closeConn;
	otCommSendData_t sendData;
	otCommReceiveData_t receiveData;
}opiltargetCommConfig_t;

typedef struct{
	otUpdateMeas_t updateMeas;
	otUpdateSimData_t updateSimData;

	otInitControl_t initControl;
	otRunControl_t runControl;

	otGetControl_t getControl;
	otGetControllerData_t getControllerData;

}opiltargetControlConfig_t;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
int32_t opiltargetInitialize(
		opiltargetCommConfig_t *commConfig,
		opiltargetControlConfig_t* targetConfig
		);
//-----------------------------------------------------------------------------
int32_t opiltargetConnectToHost(void *params);
//-----------------------------------------------------------------------------
int32_t opiltargetExchangeDataHost(void);
//-----------------------------------------------------------------------------
int32_t opiltargetDisconnectFromHost(void *params);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* OPILTARGET_H_ */
