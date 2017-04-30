//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_SERVER_CONNECTION_H
#define LURK_LURK_SERVER_CONNECTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include<netdb.h>
#include<netinet/in.h>

struct lurk_server_connection
{
    char * hostname;
    int port_number;

    int socket;

    struct sockaddr_in server_address;
    struct hostent * server;
};
struct lurk_server_connection * lurk_server_connection_allocate();

void lurk_server_connection_free(struct lurk_server_connection *);

struct lurk_server_connection * lurk_server_connection_make(
        const char *hostname, int port_number);

void lurk_server_connection_close(struct lurk_server_connection *);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_SERVER_CONNECTION_H
