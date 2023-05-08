/*
 * targetCommWinSock.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: LRS
 */

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include "targetCommWinSock.h"

#include "stdio.h"
#include "winsock2.h"
//=============================================================================

//=============================================================================
/*------------------------------- Definitions -------------------------------*/
//=============================================================================
#define TARGET_COMM_WIN_SOCK_SERVER_PORT	8080
#define TARGET_COMM_WIN_SOCK_BUFFER_SIZE	512
#define TARGET_COMM_WIN_SOCK_BACKLOG		5

//=============================================================================

//=============================================================================
/*--------------------------------- Globals ---------------------------------*/
//=============================================================================
WSADATA wsaData;
SOCKET server_socket = INVALID_SOCKET, client_socket = INVALID_SOCKET;
struct sockaddr_in server_addr, client_addr;
int client_len;

//=============================================================================

//=============================================================================
/*-------------------------------- Functions --------------------------------*/
//=============================================================================
//-----------------------------------------------------------------------------
int32_t targetCommWinSockOpenConnection(void *params){

    /* Initializes Winsock */
    if( WSAStartup(MAKEWORD(2,2),&wsaData) != 0 ){
        printf("WSAStartup failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    /* Creates the server socket */
    if( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET ){
        printf("Error creating socket. Error Code : %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    /* Sets up the server address structure */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TARGET_COMM_WIN_SOCK_SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    /* Binds the server socket to the address */
    if( bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR ){
        printf("Error binding socket. Error Code : %d", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    /* Listens for incoming connections */
    if( listen(server_socket, TARGET_COMM_WIN_SOCK_BACKLOG) == SOCKET_ERROR ){
        printf("Error listening for connections. Error Code : %d", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Waiting for connections...\n");

    /* Waits for a connection */
    client_len = sizeof(client_addr);
    if( (client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == INVALID_SOCKET ) {
        printf("Error accepting connection. Error Code : %d", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Client connected from %s\n", inet_ntoa(client_addr.sin_addr));

	return 0;
}
//-----------------------------------------------------------------------------
int32_t targetCommWinSockCloseConnection(void *params){

	int32_t status;

    status = shutdown(client_socket, SD_SEND);
    if( status == SOCKET_ERROR ){
        printf("shutdown failed: %d\n", WSAGetLastError());
        status = TARGET_CONN_WIN_SOCK_ERR_SOCK_SHUTDOWN;
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

	return status;
}
//-----------------------------------------------------------------------------
int32_t targetCommWinSockSendData(void *buffer, int32_t size){

	int32_t sent, totalSent;
	uint8_t *p = (uint8_t *)buffer;

	totalSent = 0;

	while( totalSent < size ){

		sent = send(client_socket, (void *)p, size - totalSent, 0);

		if( sent == SOCKET_ERROR ){
	        printf("send failed: %d\n", WSAGetLastError());
	        closesocket(client_socket);
	        closesocket(server_socket);
	        WSACleanup();
	        return TARGET_CONN_WIN_SOCK_ERR_SOCK_SEND;
		}

		p = p + sent;
		totalSent += sent;
	}

	return 0;
}
//-----------------------------------------------------------------------------
int32_t targetCommWinSockReceiveData(void *buffer, int32_t size){

	int32_t received, totalReceived;
	uint8_t *p = (uint8_t *)buffer;

	totalReceived = 0;
	while( totalReceived < size ){

		received = recv(client_socket, (void*)p, size - totalReceived, 0);

		if( received == 0 ){
			printf("Connection closed by client.\n");
			return TARGET_CONN_WIN_SOCK_ERR_CLIENT_DISCONNECTED;
		}
		else if( received < 0 ){
	        printf("recv failed: %d\n", WSAGetLastError());
	        closesocket(client_socket);
	        closesocket(server_socket);
	        WSACleanup();
	        return TARGET_CONN_WIN_SOCK_ERR_SOCK_RECV;
		}

		p = p + received;
		totalReceived += received;
	}

	return 0;
}
//-----------------------------------------------------------------------------
//=============================================================================
