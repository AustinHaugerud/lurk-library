//
// Created by reaver on 3/17/17.
//

#include"messages/lurk_leave.h"
#include<stdlib.h>

struct lurk_leave * leave_leave_allocate()
{
    return malloc(sizeof(struct lurk_leave));
}

struct lurk_leave * lurk_leave_create()
{
    struct lurk_leave * result = lurk_leave_allocate();
    result->protocol = lurk_head_create_leave();
    lurk_head_bind_refs(result, lurk_leave);
    return result;
}

void lurk_leave_free(struct lurk_leave * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_leave_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    // Do nothing
}
