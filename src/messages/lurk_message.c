//
// Created by reaver on 3/17/17.
//

#include <stdlib.h>
#include <string.h>
#include <ftr_io_buffer.h>
#include <ftr_io_buffer_seeker.h>
#include <frothleikr.h>
#include"messages/lurk_message.h"

struct lurk_message * lurk_message_allocate()
{
    struct lurk_message * result = malloc(sizeof(struct lurk_message));
    return result;
}

struct lurk_message * lurk_message_create()
{
    struct lurk_message * result = lurk_message_allocate();
    result->protocol = lurk_head_create_message();
    lurk_head_bind_refs(result, lurk_message);
    return result;
}

void lurk_message_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_message * ref = lurk_message_cast(lurk_message, msg);
    lurk_message_free(ref);
}

void lurk_message_free(struct lurk_message * msg)
{
    lurk_free_head(msg);
    free(msg->message);
    free(msg);
}

void lurk_message_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_message * ref = lurk_message_cast(lurk_message, msg);

    ref->message_length = lurk_data_source_read_u16(src);

    char * recipientData = lurk_data_source_read(src, LURK_MESSAGE_RECIPIENT_NAME_LENGTH);
    memcpy(ref->recipient_name, recipientData, LURK_MESSAGE_RECIPIENT_NAME_LENGTH);
    free(recipientData);

    char * senderData = lurk_data_source_read(src, LURK_MESSAGE_SENDER_NAME_LENGTH);
    memcpy(ref->sender_name, senderData, LURK_MESSAGE_SENDER_NAME_LENGTH);
    free(senderData);

    ref->message = (ftr_u8*)lurk_data_source_read(src, ref->message_length);
}

ftr_u16 lurk_message_blob_size(struct lurk_protocol_message * msg)
{
    struct lurk_message * ref = lurk_message_cast(lurk_message, msg);
    return LURK_BASE_SIZE +
           sizeof(ftr_u16) + // message length
           LURK_MESSAGE_RECIPIENT_NAME_LENGTH +
           LURK_MESSAGE_SENDER_NAME_LENGTH +
           ref->message_length; // message
}

ftr_u8 * lurk_message_blob(struct lurk_protocol_message * msg)
{
    struct lurk_message * ref = lurk_message_cast(lurk_message, msg);
    ftr_u16 size = lurk_message_size(msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    lurk_protocol_message_type_write(msg, &seeker);

    struct ftr_brokeu16 b_message_length;
    ftr_break_u16l(ref->message_length, &b_message_length);

    ftr_swrite_u16(&seeker, &b_message_length);

    ftr_swrite_bytes(&seeker, ref->recipient_name, LURK_MESSAGE_RECIPIENT_NAME_LENGTH);
    ftr_swrite_bytes(&seeker, ref->sender_name, LURK_MESSAGE_SENDER_NAME_LENGTH);
    ftr_swrite_bytes(&seeker, ref->message, ref->message_length);

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);

    ftr_free_buffer(buffer);

    return data;
}
