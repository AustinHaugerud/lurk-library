//
// Created by reaver on 3/17/17.
//

#include <stdlib.h>
#include"messages/lurk_changeroom.h"
#include<ftr_broke_types.h>
#include<ftr_io_operations.h>
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
