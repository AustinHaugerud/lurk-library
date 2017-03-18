//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"lurk_protocol_message.h"

struct lurk_protocol_message * lurk_protocol_message_allocate()
{
    return malloc(sizeof(struct lurk_protocol_message));
}

void lurk_protocol_message_free(struct lurk_protocol_message * msg)
{
    free(msg);
}

struct lurk_protocol_message * __alloc_lurk_message_head__(int type)
{
    struct lurk_protocol_message * result = lurk_protocol_message_allocate();
    result->type = (ftr_u8)type;
}
