//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include"messages/lurk_game.h"

struct lurk_game * lurk_game_allocate()
{
    return malloc(sizeof(struct lurk_game));
}

struct lurk_game * lurk_game_create()
{
    struct lurk_game * result = lurk_game_allocate();
    result->protocol = lurk_head_create_game();
    lurk_head_bind_refs(result, lurk_game);
    return result;
}

void lurk_game_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_game * ref = lurk_message_cast(lurk_game, msg);
    lurk_game_free(ref);
}

void lurk_game_free(struct lurk_game * msg)
{
    lurk_free_head(msg);
    free(msg->description);
    free(msg);
}

void lurk_game_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_game * ref = lurk_message_cast(lurk_game, msg);

    ref->initial_points = lurk_data_source_read_u16(src);
    ref->stat_limit = lurk_data_source_read_u16(src);
    ref->description_length = lurk_data_source_read_u16(src);
    ref->description = (ftr_u8*)lurk_data_source_read(src, ref->description_length);
}
