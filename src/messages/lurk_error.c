//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <frothleikr.h>
#include <string.h>
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

ftr_u16 lurk_error_blob_size(struct lurk_protocol_message * msg)
{
    struct lurk_error * ref = lurk_message_cast(lurk_error, msg);
    return LURK_BASE_SIZE +
           sizeof(ftr_u8) + // error code
           sizeof(ftr_u16) + // error message length
           ref->error_message_length; // error message
}

ftr_u8 * lurk_error_blob(struct lurk_protocol_message * msg)
{
    ftr_u16 size = lurk_message_size(msg);
    struct lurk_error * ref = lurk_message_cast(lurk_error, msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    lurk_protocol_message_type_write(msg, &seeker);

    // write error_code
    ftr_swrite_bytes(&seeker, &ref->error_code, sizeof(ftr_u8));

    struct ftr_brokeu16 b_error_message_length;
    ftr_break_u16l(ref->error_message_length, &b_error_message_length);

    // write error message length
    ftr_swrite_u16(&seeker, &b_error_message_length);

    // write error message
    ftr_swrite_bytes(&seeker, ref->error_message, ref->error_message_length);

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);
    ftr_free_buffer(buffer);

    return data;
}
