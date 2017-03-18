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

#endif //LURK_LURK_START_H
