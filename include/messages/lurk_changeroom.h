//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_CHANGEROOM_H
#define LURK_LURK_CHANGEROOM_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

struct lurk_changeroom
{
    struct lurk_protocol_message * protocol;

    ftr_u16 room_number;
};

struct lurk_changeroom * lurk_changeroom_allocate();

struct lurk_changeroom * lurk_changeroom_create();

void lurk_changeroom_free(struct lurk_changeroom *);

void lurk_changeroom_head_free(struct lurk_protocol_message *);

void lurk_changeroom_read(struct lurk_protocol_message * self, struct lurk_data_source * src);

#endif //LURK_LURK_CHANGEROOM_H
