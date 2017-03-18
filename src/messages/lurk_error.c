//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"messages/lurk_error.h"

struct lurk_error * lurk_error_allocate()
{
    return malloc(sizeof(struct lurk_error));
}

struct lurk_error * lurk_error_create()
{
    struct lurk_error * result = lurk_error_allocate();
    result->protocol = lurk_head_create_error();
    lurk_head_bind_refs(result, lurk_error);
    return result;
}

void lurk_error_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_error * ref = lurk_message_cast(lurk_error, msg);
    lurk_error_free(ref);
}

void lurk_error_free(struct lurk_error * msg)
{
    lurk_free_head(msg);
    free(msg->error_message);
    free(msg);
}

void lurk_error_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_error * ref = lurk_message_cast(lurk_error, msg);

    ref->error_code = lurk_data_source_read_u8(src);

    ref->error_message_length = lurk_data_source_read_u16(src);

    ref->error_message = (ftr_u8*)lurk_data_source_read(src, ref->error_message_length);
}
