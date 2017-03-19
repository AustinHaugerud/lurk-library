//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"lurk_protocol_message.h"
#include<ftr_io_buffer.h>
#include<ftr_io_buffer_seeker.h>

struct lurk_protocol_message * lurk_protocol_message_allocate()
{
    return malloc(sizeof(struct lurk_protocol_message));
}

void lurk_protocol_message_free(struct lurk_protocol_message * msg)
{
    free(msg);
}

void lurk_protocol_message_type_write(struct lurk_protocol_message * msg, struct ftr_io_buffer_seeker * seeker)
{
    ftr_swrite_bytes(seeker, &msg->type, sizeof(ftr_u8));
}

struct lurk_protocol_message * __alloc_lurk_message_head__(int type)
{
    struct lurk_protocol_message * result = lurk_protocol_message_allocate();
    result->type = (ftr_u8)type;
}
