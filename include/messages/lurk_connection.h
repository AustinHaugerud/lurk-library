//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_CONNECTION_H
#define LURK_LURK_CONNECTION_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_CONNECTION_ROOM_NAME_LENGTH 32

struct lurk_connection
{
    struct lurk_protocol_message * protocol;

    ftr_u16 room_number;

    ftr_u8 room_name[LURK_CONNECTION_ROOM_NAME_LENGTH];

    ftr_u16 description_length;

    ftr_u8 * description;
};

struct lurk_connection * lurk_connection_allocate();

struct lurk_connection * lurk_connection_create();

void lurk_connection_free(struct lurk_connection *);

void lurk_connection_head_free(struct lurk_protocol_message * msg);

void lurk_connection_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_connection_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_connection_blob(struct lurk_protocol_message * msg);

#endif //LURK_LURK_CONNECTION_H
