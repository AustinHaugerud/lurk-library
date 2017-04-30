//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_ROOM_H
#define LURK_LURK_ROOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_ROOM_NAME_LENGTH 32

struct lurk_room
{
    struct lurk_protocol_message * protocol;

    ftr_u16 room_number;

    ftr_u8 room_name[LURK_ROOM_NAME_LENGTH];

    ftr_u16 room_description_length;

    ftr_u8 * room_description;
};

struct lurk_room * lurk_room_allocate();

struct lurk_room * lurk_room_create();

void lurk_room_head_free(struct lurk_protocol_message *);

void lurk_room_free(struct lurk_room *);

void lurk_room_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_room_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_room_blob(struct lurk_protocol_message * msg);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_ROOM_H
