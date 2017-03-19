//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <frothleikr.h>
#include <string.h>
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

ftr_u16 lurk_accept_blob_size(struct lurk_protocol_message * msg)
{
    return LURK_BASE_SIZE +
            sizeof(ftr_u8); // action type
}

ftr_u8 * lurk_accept_blob(struct lurk_protocol_message * msg)
{
    ftr_u16 size = lurk_message_size(msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct lurk_accept * ref = lurk_message_cast(lurk_accept, msg);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");
    lurk_protocol_message_type_write(msg, &seeker);
    ftr_swrite_bytes(&seeker, &ref->action_type, sizeof(ftr_u8));

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);

    ftr_free_buffer(buffer);

    return data;
}
