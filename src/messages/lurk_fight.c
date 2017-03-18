//
// Created by reaver on 3/17/17.
//

#include"messages/lurk_fight.h"
#include <malloc.h>

struct lurk_fight * lurk_fight_allocate()
{
    return malloc(sizeof(struct lurk_fight));
}

struct lurk_fight * lurk_fight_create()
{
    struct lurk_fight * result = lurk_fight_allocate();
    result->protocol = lurk_head_create_fight();
    lurk_head_bind_refs(result, lurk_fight);
    return result;
}

void lurk_fight_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_fight * ref = lurk_message_cast(lurk_fight, msg);
    lurk_fight_free(ref);
}

void lurk_fight_free(struct lurk_fight * msg)
{
    lurk_free_head(msg);
    free(msg);
}

void lurk_fight_read(struct lurk_protocol_message * msg, struct lurk_data_source *src)
{
    // Do nothing, the fight message has no contents
    // This function is just here so protocol:read has something to point at
}
