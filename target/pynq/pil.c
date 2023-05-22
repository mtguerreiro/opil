/*
 * pil.c
 *
 *  Created on: 06.05.2023
 *      Author: Marco Guerreiro
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "target/target.h"
#include "pil.h"

#include "FreeRTOS.h"
#include "task.h"

/* OPiL */
#include "opiltarget.h"
#include "comm/pynq/targetCommPynqSock.h"

/* Control */
#include "invcontrol.h"
//=============================================================================

//=============================================================================
/*--------------------------------- Defines ---------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================

//=============================================================================

//=============================================================================
/*-------------------------------- Prototypes -------------------------------*/
//=============================================================================
static void pilInitialize(void);
//=============================================================================

//=============================================================================
/*---------------------------------- Task -----------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
void pil(void *param){

	pilInitialize();

	while(1){
		if( opiltargetConnectToHost(0) != 0 ) continue;

		while( opiltargetExchangeDataHost() == 0 );

		opiltargetDisconnectFromHost(0);
	}
}
//-----------------------------------------------------------------------------
//=============================================================================

//=============================================================================
/*---------------------------- Static functions -----------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
static void pilInitialize(void){

	/* Creates the server socket */
	if( targetCommPynqInitialize() != 0 )
		vTaskDelay(2000 / portTICK_PERIOD_MS);

	/* Initializes target */
	targetInitialize(invcontrolInitialize, invcontrol);

	/* Initializes opil */
	opiltargetCommConfig_t comm;
	opiltargetControlConfig_t control;

	comm.openConn = targetCommPynqSockOpenConnection;
	comm.closeConn = targetCommPynqSockCloseConnection;
	comm.sendData = targetCommPynqSockSendData;
	comm.receiveData = targetCommPynqSockReceiveData;

	control.updateMeas = targetUpdateMeasurements;
	control.updateSimData = targetUpdateSimData;

	control.initControl = targetInitializeControl;
	control.runControl = targetRunControl;

	control.getControl = targetGetControl;
	control.getControllerData = targetGetControllerData;

	opiltargetInitialize(&comm, &control);
}
//-----------------------------------------------------------------------------
//=============================================================================
