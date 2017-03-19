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

ftr_u16 lurk_leave_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_leave_blob(struct lurk_protocol_message * msg);

#endif //LURK_LURK_LEAVE_H
