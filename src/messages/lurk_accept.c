//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"messages/lurk_accept.h"

struct lurk_accept * lurk_accept_allocate()
{
    return malloc(sizeof(struct lurk_accept));
}

struct lurk_accept * lurk_accept_create()
{
    struct lurk_accept * result = lurk_accept_allocate();
    result->protocol = lurk_head_create_accept();
    lurk_head_bind_refs(result, lurk_accept);
    return result;
}

void lurk_accept_free(struct lurk_accept * msg)
{
    lurk_protocol_message_free(msg->protocol);
    free(msg);
}

void lurk_accept_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_accept * ref = lurk_message_cast(lurk_accept, msg);
    lurk_accept_free(ref);
}

void lurk_accept_read(struct lurk_protocol_message * self, struct lurk_data_source * src)
{
    struct lurk_accept * ref = lurk_message_cast(lurk_accept, self);
    ref->action_type = lurk_data_source_read_u8(src);
}
