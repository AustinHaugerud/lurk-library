//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_ACCEPT_H
#define LURK_LURK_ACCEPT_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

struct lurk_accept
{
    struct lurk_protocol_message * protocol;
    ftr_u8 action_type;
};

struct lurk_accept * lurk_accept_allocate();

struct lurk_accept * lurk_accept_create();

void lurk_accept_free(struct lurk_accept *);

void lurk_accept_head_free(struct lurk_protocol_message * msg);

void lurk_accept_read(struct lurk_protocol_message * self, struct lurk_data_source * src);

ftr_u16 lurk_accept_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_accept_blob(struct lurk_protocol_message * msg);

#endif //LURK_LURK_ACCEPT_H
