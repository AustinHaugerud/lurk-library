//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <string.h>
#include"messages/lurk_loot.h"

struct lurk_loot * lurk_loot_allocate()
{
    return malloc(sizeof(struct lurk_loot));
}

struct lurk_loot * lurk_loot_create()
{
    struct lurk_loot * result = lurk_loot_allocate();
    result->protocol = lurk_head_create_loot();
    lurk_head_bind_refs(result, lurk_loot);
    return result;
}

void lurk_loot_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_loot * ref = lurk_message_cast(lurk_loot, msg);
    lurk_loot_free(ref);
}

void lurk_loot_free(struct lurk_loot * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_loot_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_loot * ref = lurk_message_cast(lurk_loot, msg);
    char * data = lurk_data_source_read(src, LURK_LOOT_TARGET_PLAYER_LENGTH);
    memcpy(ref->target_player, data, LURK_LOOT_TARGET_PLAYER_LENGTH);
    free(data);
}
