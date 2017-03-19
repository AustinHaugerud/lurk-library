//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <string.h>
#include <frothleikr.h>
#include"messages/lurk_room.h"

struct lurk_room * lurk_room_allocate()
{
    return malloc(sizeof(struct lurk_room));
}

struct lurk_room * lurk_room_create()
{
    struct lurk_room * result = lurk_room_allocate();
    result->protocol = lurk_head_create_room();
    lurk_head_bind_refs(result, lurk_room);
    return result;
}

void lurk_room_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_room * ref = lurk_message_cast(lurk_room, msg);
    lurk_room_free(ref);
}

void lurk_room_free(struct lurk_room * msg)
{
    lurk_free_head(msg);
    free(msg->room_description);
    free(msg);
}

void lurk_room_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_room * ref = lurk_message_cast(lurk_room, msg);

    ref->room_number = lurk_data_source_read_u16(src);

    char * nameData = lurk_data_source_read(src, LURK_ROOM_NAME_LENGTH);
    memcpy(ref->room_name, nameData, LURK_ROOM_NAME_LENGTH);
    free(nameData);

    ref->room_description_length = lurk_data_source_read_u16(src);

    ref->room_description = (ftr_u8*)lurk_data_source_read(src, ref->room_description_length);
}

ftr_u16 lurk_room_blob_size(struct lurk_protocol_message * msg)
{
    struct lurk_room * ref = lurk_message_cast(lurk_room, msg);
    return LURK_BASE_SIZE +
           sizeof(ftr_u16) +
           LURK_ROOM_NAME_LENGTH +
           sizeof(ftr_u16) +
           ref->room_description_length;
}

ftr_u8 * lurk_room_blob(struct lurk_protocol_message * msg)
{
    ftr_u16 size = lurk_message_size(msg);
    struct lurk_room * ref = lurk_message_cast(lurk_room, msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    lurk_protocol_message_type_write(msg, &seeker);

    struct ftr_brokeu16 b_room_number, b_room_description_length;

    ftr_break_u16l(ref->room_number, &b_room_number);
    ftr_break_u16l(ref->room_description_length, &b_room_description_length);

    ftr_swrite_u16(&seeker, &b_room_number);
    ftr_swrite_bytes(&seeker, ref->room_name, LURK_ROOM_NAME_LENGTH);
    ftr_swrite_u16(&seeker, &b_room_description_length);
    ftr_swrite_bytes(&seeker, ref->room_description, ref->room_description_length);

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);
    ftr_free_buffer(buffer);

    return data;
}
