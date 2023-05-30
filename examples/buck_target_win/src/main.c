/*
 * main.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: marco
 */

#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

#include "opiltarget.h"

#include "ctlrif/ctlrif.h"
#include "comm/win/targetCommWinSock.h"

#include "buckcontrol.h"

int main(int argc, char **argv){

	/* Initializes target */
	ctlrifInitialize(buckcontrolInitialize, buckcontrol);

	/* Initializes opil */
	opiltargetCommConfig_t comm;
	opiltargetControlConfig_t control;

	comm.openConn = targetCommWinSockOpenConnection;
	comm.closeConn = targetCommWinSockCloseConnection;
	comm.sendData = targetCommWinSockSendData;
	comm.receiveData = targetCommWinSockReceiveData;

	control.updateMeas = ctlrifUpdateMeasurements;
	control.updateSimData = ctlrifUpdateSimData;

	control.initControl = ctlrifInitializeControl;
	control.runControl = ctlrifRunControl;

	control.getControl = ctlrifGetControl;
	control.getControllerData = ctlrifGetControllerData;

	opiltargetInitialize(&comm, &control);

	opiltargetConnectToHost(0);

	while( opiltargetExchangeDataHost() == 0 );

	opiltargetDisconnectFromHost(0);

	return 0;
}
