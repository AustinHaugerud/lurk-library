//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_LEAVE_H
#define LURK_LURK_LEAVE_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

struct lurk_leave
{
    struct lurk_protocol_message * protocol;
};

struct lurk_leave * lurk_leave_allocate();

struct lurk_leave * lurk_leave_create();

void lurk_leave_head_free(struct lurk_protocol_message * msg);

void lurk_leave_free(struct lurk_leave *);

void lurk_leave_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

#endif //LURK_LURK_LEAVE_H
