//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"messages/lurk_start.h"

struct lurk_start * lurk_start_allocate()
{
    return malloc(sizeof(struct lurk_start));
}

struct lurk_start * lurk_start_create()
{
    struct lurk_start * result = lurk_start_allocate();
    result->protocol = lurk_head_create_start();
    lurk_head_bind_refs(result, lurk_start);
    return result;
}

void lurk_start_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_start * ref = lurk_message_cast(lurk_start, msg);
    lurk_start_free(ref);
}

void lurk_start_free(struct lurk_start * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_start_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    // Do nothing
}
