//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_DATA_SOURCE_H
#define LURK_LURK_DATA_SOURCE_H

#include<ftr_types.h>

#define LURK_DATA_SOURCE_FROM_SERVER 0
#define LURK_DATA_SOURCE_FROM_CLIENT 1

struct lurk_server_connection;
struct lurk_client_connection;

struct lurk_data_source
{
    int type;
    union
    {
        struct lurk_client_connection * client_connection;
        struct lurk_server_connection * server_connection;
    };
};

struct lurk_data_source * lurk_data_source_allocate();

struct lurk_data_source * lurk_data_source_make_from_server(struct lurk_server_connection *);

struct lurk_data_source * lurk_data_source_make_from_client(struct lurk_client_connection *);

int lurk_data_source_read_type(struct lurk_data_source * source);

char * lurk_data_source_read(struct lurk_data_source * source, ftr_u32 size);

ftr_u8 lurk_data_source_read_u8(struct lurk_data_source * source);
ftr_u16 lurk_data_source_read_u16(struct lurk_data_source * source);
ftr_s16 lurk_data_source_read_s16(struct lurk_data_source * source);

#endif //LURK_LURK_DATA_SOURCE_H
