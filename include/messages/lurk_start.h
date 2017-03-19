//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_START_H
#define LURK_LURK_START_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

struct lurk_start
{
    struct lurk_protocol_message * protocol;
};

struct lurk_start * lurk_start_allocate();

struct lurk_start * lurk_start_create();

void lurk_start_head_free(struct lurk_protocol_message * msg);

void lurk_start_free(struct lurk_start *);

void lurk_start_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_start_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_start_blob(struct lurk_protocol_message * msg);

#endif //LURK_LURK_START_H
