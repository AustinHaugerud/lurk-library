//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_CLIENT_CONNECTION_H
#define LURK_LURK_CLIENT_CONNECTION_H

struct lurk_client_connection
{
    int socket;
};

struct lurk_client_connection * lurk_client_connection_allocate();

struct lurk_client_connection * lurk_client_connection_make(int socket);

void lurk_client_connection_free(struct lurk_client_connection *);

void lurk_client_connection_close(struct lurk_client_connection *);

#endif //LURK_LURK_CLIENT_CONNECTION_H
