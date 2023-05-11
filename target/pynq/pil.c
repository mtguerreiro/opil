/*
 * pil.c
 *
 *  Created on: 06.05.2023
 *      Author: Marco Guerreiro
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include <target/pynq/pil.h>

#include "FreeRTOS.h"
#include "task.h"

/* OPiL */
#include "opiltarget.h"
#include "target/pynq/targetPynq.h"
#include "comm/pynq/targetCommPynqSock.h"
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

		/* Where should we place this? */
		targetPynqInitialize(0);

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

	/* Initializes opil */
	opiltargetCommConfig_t comm;
	opiltargetControlConfig_t control;

	comm.openConn = targetCommPynqSockOpenConnection;
	comm.closeConn = targetCommPynqSockCloseConnection;
	comm.sendData = targetCommPynqSockSendData;
	comm.receiveData = targetCommPynqSockReceiveData;

	control.updateMeas = targetPynqUpdateMeasurements;
	control.updateSimData = targetPynqUpdateSimData;
	control.runControl = targetPynqRunControl;
	control.getControl = targetPynqGetControl;
	control.getControllerData = targetPynqGetControllerData;

	opiltargetInitialize(&comm, &control);

	/* Creates the server socket */
	if( targetCommPynqInitialize() != 0 )
		vTaskDelay(2000 / portTICK_PERIOD_MS);

}
//-----------------------------------------------------------------------------
//=============================================================================
