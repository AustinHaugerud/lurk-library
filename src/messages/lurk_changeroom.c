//
// Created by reaver on 3/17/17.
//

#include <stdlib.h>
#include"messages/lurk_changeroom.h"
#include<frothleikr.h>
#include <string.h>

struct lurk_changeroom * lurk_changeroom_allocate()
{
    return malloc(sizeof(struct lurk_changeroom));
}

struct lurk_changeroom * lurk_changeroom_create()
{
    struct lurk_changeroom * result = lurk_changeroom_allocate();
    result->protocol = lurk_head_create_changeroom();
    lurk_head_bind_refs(result, lurk_changeroom);
    return result;
}

void lurk_changeroom_free(struct lurk_changeroom * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_changeroom_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_changeroom * ref = lurk_message_cast(lurk_changeroom, msg);
    lurk_changeroom_free(ref);
}

void lurk_changeroom_read(struct lurk_protocol_message * self, struct lurk_data_source * src)
{
    struct lurk_changeroom * ref = lurk_message_cast(lurk_changeroom, self);
    char * data = lurk_data_source_read(src, sizeof(ftr_u16));

    struct ftr_brokeu16 brokeu16;
    memcpy(brokeu16.bytes, data, sizeof(ftr_u16));

    free(data);

    ref->room_number = ftr_assemble_u16b(&brokeu16);
}

ftr_u16 lurk_changeroom_blob_size(struct lurk_protocol_message * msg)
{
    return LURK_BASE_SIZE +
           sizeof(ftr_u16); // room_number
}

ftr_u8 * lurk_changeroom_blob(struct lurk_protocol_message * msg)
{
    struct lurk_changeroom * ref = lurk_message_cast(lurk_changeroom, msg);

    ftr_u16 size = lurk_message_size(msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    lurk_protocol_message_type_write(msg, &seeker);

    struct ftr_brokeu16 broke_room_number;

    ftr_break_u16l(ref->room_number, &broke_room_number);

    ftr_swrite_u16(&seeker, &broke_room_number);

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);
    ftr_free_buffer(buffer);

    return data;
}
