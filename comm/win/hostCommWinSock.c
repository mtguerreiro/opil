/*
 * hostCommWinSock.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "hostCommWinSock.h"

#include "stdio.h"
#include "winsock2.h"
//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
#define HOST_COMM_WIN_SOCK_SERVER_IP		"127.0.0.1"
#define HOST_COMM_WIN_SOCK_SERVER_PORT		8080
#define HOST_COMM_WIN_SOCK_BUFFER_SIZE		512

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
static WSADATA wsaData;
static SOCKET sock = INVALID_SOCKET;
static struct sockaddr_in server_addr;
//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
int32_t hostCommWinSockOpenConnection(void *params){

    int status;

    /* Initializes Winsock */
    status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if( status != 0 ) {
        printf("WSAStartup failed: %d\n", status);
        return HOST_COMM_WIN_SOCK_ERR_SOCK_INI;
    }

    /* Creates the socket on this side */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return HOST_COMM_WIN_SOCK_ERR_SOCK_CREATE;
    }

    /* Server data */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(HOST_COMM_WIN_SOCK_SERVER_IP);
    server_addr.sin_port = htons(HOST_COMM_WIN_SOCK_SERVER_PORT);

    /* Connects to the server */
    status = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if( status == SOCKET_ERROR ) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return HOST_COMM_WIN_SOCK_ERR_SOCK_SERVER_CONN;
    }

	return 0;
}
//-----------------------------------------------------------------------------
int32_t hostCommWinSockCloseConnection(void *params){

	int32_t status;

    status = shutdown(sock, SD_SEND);
    if( status == SOCKET_ERROR ){
        printf("shutdown failed: %d\n", WSAGetLastError());
        status = HOST_CONN_WIN_SOCK_ERR_SOCK_SHUTDOWN;
    }

    closesocket(sock);
    WSACleanup();

	return status;
}
//-----------------------------------------------------------------------------
int32_t hostCommWinSockSendData(void *buffer, int32_t size){

	int32_t sent, totalSent;
	uint8_t *p = (uint8_t *)buffer;

	totalSent = 0;

	while( totalSent < size ){

		sent = send(sock, (void *)p, size - totalSent, 0);

		if( sent == SOCKET_ERROR ){
	        printf("send failed: %d\n", WSAGetLastError());
	        closesocket(sock);
	        WSACleanup();
	        return HOST_CONN_WIN_SOCK_ERR_SOCK_SEND;
		}

		p = p + sent;
		totalSent += sent;
	}

	return 0;
}
//-----------------------------------------------------------------------------
int32_t hostCommWinSockReceiveData(void *buffer, int32_t size){

	int32_t received, totalReceived;
	uint8_t *p = (uint8_t *)buffer;

	totalReceived = 0;
	while( totalReceived < size ){

		received = recv(sock, (void*)p, size - totalReceived, 0);

		if( received == 0 ){
			printf("Connection closed by server.\n");
			return HOST_CONN_WIN_SOCK_ERR_SERVER_DISCONNECTED;
		}
		else if( received < 0 ){
	        printf("recv failed: %d\n", WSAGetLastError());
	        closesocket(sock);
	        WSACleanup();
	        return HOST_CONN_WIN_SOCK_ERR_SOCK_RECV;
		}

		p = p + received;
		totalReceived += received;
	}

	return 0;
}
//-----------------------------------------------------------------------------
//=============================================================================
