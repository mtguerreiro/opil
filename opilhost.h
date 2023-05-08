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

typedef int32_t (*ohCommOpenConn_t)(void *params);
typedef int32_t (*ohCommCloseConn_t)(void *params);
typedef int32_t (*ohCommSendData_t)(void *buffer, int32_t size);
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
