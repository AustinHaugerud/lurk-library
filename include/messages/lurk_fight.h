//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_FIGHT_H
#define LURK_LURK_FIGHT_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

struct lurk_fight
{
    struct lurk_protocol_message * protocol;
};

struct lurk_fight * lurk_fight_allocate();

struct lurk_fight * lurk_fight_create();

void lurk_fight_head_free(struct lurk_protocol_message * msg);

void lurk_fight_free(struct lurk_fight *);

void lurk_fight_read(struct lurk_protocol_message *, struct lurk_data_source * src);

ftr_u16 lurk_fight_blob_size(struct lurk_protocol_message *);

ftr_u8 * lurk_fight_blob(struct lurk_protocol_message *);

#endif //LURK_LURK_FIGHT_H
