//
// Created by reaver on 3/18/17.
//

#include"lurk_client_connection.h"
#include<stdlib.h>
#include<unistd.h>

struct lurk_client_connection * lurk_client_connection_allocate()
{
    return malloc(sizeof(struct lurk_client_connection));
}

void lurk_client_connection_free(struct lurk_client_connection * con)
{
    free(con);
}

void lurk_client_connection_close(struct lurk_client_connection * con)
{
    close(con->socket);
}
