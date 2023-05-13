/*
 * targetCommPynqSock.h
 *
 *  Created on: 7 de mai de 2023
 *      Author: LRS
 */

#ifndef TARGET_COMM_PYNQ_SOCK_H_
#define TARGET_COMM_PYNQ_SOCK_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
#define TARGET_COMM_PYNQ_SOCK_ERR_SOCK_INI				-1
#define TARGET_COMM_PYNQ_SOCK_ERR_SOCK_BIND				-2
#define TARGET_COMM_PYNQ_SOCK_ERR_SOCK_CLIENT_CONN		-3
#define	TARGET_CONN_PYNQ_SOCK_ERR_SOCK_SEND				-4
#define TARGET_CONN_PYNQ_SOCK_ERR_SOCK_RECV				-5
#define TARGET_CONN_PYNQ_SOCK_ERR_CLIENT_SOCK_CLOSE		-6
#define TARGET_CONN_PYNQ_SOCK_ERR_CLIENT_DISCONNECTED	-7
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
/** @brief Initializes the server socket.
 */
int32_t targetCommPynqInitialize(void);
//-----------------------------------------------------------------------------
/** @brief Waits for a client connection.
 */
int32_t targetCommPynqSockOpenConnection(void *params);
//-----------------------------------------------------------------------------
/** @brief Closes the client socket.
 */
int32_t targetCommPynqSockCloseConnection(void *params);
//-----------------------------------------------------------------------------
/** @brief Sends data to the client socket.
 */
int32_t targetCommPynqSockSendData(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
/* @brief Receives data from the client socket.
 */
int32_t targetCommPynqSockReceiveData(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* TARGET_COMM_PYNQ_SOCK_H_ */
