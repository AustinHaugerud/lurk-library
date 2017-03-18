//
// Created by reaver on 3/17/17.
//

#include"messages/lurk_pvpfight.h"
#include<stdlib.h>
#include <string.h>

struct lurk_pvpfight * lurk_pvpfight_allocate()
{
    return malloc(sizeof(struct lurk_pvpfight));
}

struct lurk_pvpfight * lurk_pvpfight_create()
{
    struct lurk_pvpfight * result = lurk_pvpfight_allocate();
    result->protocol = lurk_head_create_pvpfight();
    lurk_head_bind_refs(result, lurk_pvpfight);
}

void lurk_pvpfight_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_pvpfight * ref = lurk_message_cast(lurk_pvpfight, msg);
    lurk_pvpfight_free(ref);
}

void lurk_pvpfight_free(struct lurk_pvpfight * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_pvpfight_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_pvpfight * ref = lurk_message_cast(lurk_pvpfight, msg);

    char * nameData = lurk_data_source_read(src, LURK_PVPFIGHT_TARGET_NAME_LENGTH);
    memcpy(ref->target_name, nameData, LURK_PVPFIGHT_TARGET_NAME_LENGTH);
    free(nameData);
}
