//
// Created by reaver on 3/18/17.
//

#include<stdlib.h>
#include"lurk_client_connection.h"
#include"lurk_listener.h"

struct lurk_listener * lurk_listener_allocate()
{
    return malloc(sizeof(struct lurk_listener));
}

struct lurk_listener * lurk_listener_make(int port_number)
{
    struct lurk_listener * result = lurk_listener_allocate();

    result->sad.sin_port = htons(port_number);
    result->sad.sin_addr.s_addr = INADDR_ANY;
    result->sad.sin_family = AF_INET;

    result->socket = socket(AF_INET, SOCK_STREAM, 0);

    if(result->socket < 0)
    {
        lurk_listener_free(result);
        return NULL;
    }

    bind(result->socket, (struct sockaddr *)&result->sad, sizeof(struct sockaddr_in));
    listen(result->socket, 5);

    return result;
}

struct lurk_client_connection * lurk_listener_accept(struct lurk_listener * listener)
{
    struct lurk_client_connection * connection = lurk_client_connection_allocate();
    connection->socket = accept(listener->socket, 0, 0);
    return connection;
}

void lurk_listener_free(struct lurk_listener * listener)
{
    free(listener);
}
