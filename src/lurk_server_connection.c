//
// Created by reaver on 3/17/17.
//

#include"lurk_server_connection.h"
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/ip.h>
#include <ftr_types.h>

struct lurk_server_connection * lurk_server_connection_allocate()
{
    return malloc(sizeof(struct lurk_server_connection));
}

void lurk_server_connection_free(struct lurk_server_connection * connection)
{
    free(connection->hostname);
    free(connection);
}

struct lurk_server_connection * lurk_server_connection_make(
        const char * hostname, int port_number)
{
    struct sockaddr_in sad;

    sad.sin_port = htons((ftr_u16)port_number);
    sad.sin_family = AF_INET;

    int skt = socket(AF_INET, SOCK_STREAM, 0);

    struct hostent * server = gethostbyname(hostname);
    struct in_addr ** addr_list = (struct in_addr**)server->h_addr_list;
    struct in_addr * addr = addr_list[0];
    sad.sin_addr = *addr;

    if(connect(skt, (struct sockaddr*)&sad, sizeof(struct sockaddr_in)) != 0)
    {
        return NULL;
    }

    struct lurk_server_connection * connection = lurk_server_connection_allocate();
    connection->server = server;

    connection->hostname = malloc(strlen(hostname));
    strcpy(connection->hostname, hostname);

    connection->port_number = port_number;

    connection->socket = skt;

    connection->server_address = sad;

    return connection;
}

void lurk_server_connection_close(struct lurk_server_connection * connection)
{
    close(connection->socket);
    lurk_server_connection_free(connection);
}
