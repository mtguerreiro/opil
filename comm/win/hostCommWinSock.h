/*
 * hostCommWinSock.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

#ifndef HOST_COMM_WIN_SOCK_H_
#define HOST_COMM_WIN_SOCK_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "stdint.h"
#include "stddef.h"

//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
#define HOST_COMM_WIN_SOCK_ERR_SOCK_INI				-1
#define HOST_COMM_WIN_SOCK_ERR_SOCK_CREATE			-2
#define HOST_COMM_WIN_SOCK_ERR_SOCK_SERVER_CONN		-3
#define	HOST_CONN_WIN_SOCK_ERR_SOCK_SEND			-4
#define HOST_CONN_WIN_SOCK_ERR_SOCK_RECV			-5
#define HOST_CONN_WIN_SOCK_ERR_SOCK_SHUTDOWN		-6
#define HOST_CONN_WIN_SOCK_ERR_SERVER_DISCONNECTED	-7
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * @brief Initializes and opens the client socket.
 *
 * @param params Not used, can be given as 0 or NULL.
 * @return 0 if socket was opened successfully, otherwise an error code.
 */
int32_t hostCommWinSockOpenConnection(void *params);
//-----------------------------------------------------------------------------
/**
 * @brief Closes the client socket previously opened.
 *
 * @param params Not used, can be given as 0 or NULL.
 * @return 0 if socket was closed successfully, an error code otherwise.
 */
int32_t hostCommWinSockCloseConnection(void *params);
//-----------------------------------------------------------------------------
/**
 * @brief Sends data through the previously opened socket.
 *
 * @param buffer Pointer to buffer holding data to be sent.
 * @param size Size of buffer, in bytes.
 * @return 0 if data was sent successfully, an error code otherwise.
 */
int32_t hostCommWinSockSendData(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
/**
 * @brief Receives data from the previously opened socket.
 *
 * @param buffer Pointer to buffer to hold data.
 * @param size Number of bytes to receive.
 * @return 0 if data was received successfully, an error code otherwise.
 */
int32_t hostCommWinSockReceiveData(void *buffer, int32_t size);
//-----------------------------------------------------------------------------
//=============================================================================

#endif /* HOST_COMM_WIN_SOCK_H_ */
