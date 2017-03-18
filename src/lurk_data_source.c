//
// Created by reaver on 3/17/17.
//

#include"lurk_data_source.h"
#include"lurk_server_connection.h"
#include"lurk_client_connection.h"
#include<unistd.h>
#include<stdlib.h>
#include<ftr_broke_types.h>
#include<ftr_io_operations.h>
#include <string.h>

struct lurk_data_source * lurk_data_source_allocate()
{
    return malloc(sizeof(struct lurk_data_source));
}

struct lurk_data_source * lurk_data_source_make_from_server(struct lurk_server_connection * connection)
{
    struct lurk_data_source * result = lurk_data_source_allocate();
    result->type = LURK_DATA_SOURCE_FROM_SERVER;
    result->server_connection = connection;
    return result;
}

struct lurk_data_source * lurk_data_source_make_from_client(struct lurk_client_connection * connection)
{
    struct lurk_data_source * result = lurk_data_source_allocate();
    result->type = LURK_DATA_SOURCE_FROM_CLIENT;
    result->client_connection = connection;
}

int lurk_data_source_read_type(struct lurk_data_source * source)
{
    return lurk_data_source_read_u8(source);
}

char * lurk_data_source_read(struct lurk_data_source * source, ftr_u32 size)
{
    char * result = NULL;

    if(source->type == LURK_DATA_SOURCE_FROM_SERVER)
    {
        struct lurk_server_connection * connection = source->server_connection;
        result = malloc(size);
        read(connection->socket, result, size);
    }
    else if(source->type == LURK_DATA_SOURCE_FROM_CLIENT)
    {
        // TODO
    }

    return result;
}

ftr_u8 lurk_data_source_read_u8(struct lurk_data_source * source)
{
    char * result = lurk_data_source_read(source, sizeof(ftr_u8));
    int int_result = *result;
    free(result);
    return (ftr_u8)int_result;
}

ftr_u16 lurk_data_source_read_u16(struct lurk_data_source * source)
{
    char * data = lurk_data_source_read(source, sizeof(ftr_u16));
    struct ftr_brokeu16 broke;
    memcpy(broke.bytes, data, sizeof(ftr_u16));
    free(data);
    return ftr_assemble_u16b(&broke);
}

ftr_s16 lurk_data_source_read_s16(struct lurk_data_source * source)
{
    char * data = lurk_data_source_read(source, sizeof(ftr_s16));
    struct ftr_brokes16 broke;
    memcpy(broke.bytes, data, sizeof(ftr_s16));
    free(data);
    return ftr_assemble_s16b(&broke);
}
