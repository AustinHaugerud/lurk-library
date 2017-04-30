//
// Created by reaver on 3/18/17.
//

#ifndef LURK_LURK_LISTENER_H
#define LURK_LURK_LISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<unistd.h>

struct lurk_client_connection;

struct lurk_listener
{
    struct sockaddr_in sad;
    int socket;
};

struct lurk_listener * lurk_listener_allocate();

struct lurk_listener * lurk_listener_make(int port_number);

struct lurk_client_connection * lurk_listener_accept(struct lurk_listener * listener);

void lurk_listener_free(struct lurk_listener *);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_LISTENER_H
