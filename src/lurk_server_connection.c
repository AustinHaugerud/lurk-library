//
// Created by reaver on 3/17/17.
//

#include"lurk_server_connection.h"
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

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

    struct lurk_server_connection * connection  = lurk_server_connection_allocate();

    connection->hostname = malloc(strlen(hostname));
    strcpy(connection->hostname, hostname);

    connection->port_number = port_number;

    connection->socket = socket(AF_INET, SOCK_STREAM, 0);

    if(connection->socket < 0)
    {
        lurk_server_connection_free(connection);
        return NULL;
    }

    connection->server = gethostbyname(connection->hostname);

    if(connection->server == NULL)
    {
        lurk_server_connection_free(connection);
        return NULL;
    }

    connection->server_address.sin_family = AF_INET;
    connection->server_address.sin_port = (in_port_t)port_number;

    struct in_addr ** addr_list = (struct in_addr * *)connection->server->h_addr_list;
    connection->server_address.sin_addr = *(addr_list[0]);

    connect(
            connection->socket,
            (struct sockaddr *)&connection->server_address,
            sizeof(struct sockaddr_in)
    );
}

void lurk_server_connection_close(struct lurk_server_connection * connection)
{
    close(connection->socket);
    lurk_server_connection_free(connection);
}
