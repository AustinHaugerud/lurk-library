//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <frothleikr.h>
#include <string.h>
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

ftr_u16 lurk_game_blob_size(struct lurk_protocol_message * msg)
{
    struct lurk_game * ref = lurk_message_cast(lurk_game, msg);
    return LURK_BASE_SIZE +
           sizeof(ftr_u16) + // initial points
           sizeof(ftr_u16) + // stat limit
           sizeof(ftr_u16) + // description length
           ref->description_length; // description
}

ftr_u8 * lurk_game_blob(struct lurk_protocol_message * msg)
{
    struct lurk_game * ref = lurk_message_cast(lurk_game, msg);

    ftr_u16 size = lurk_message_size(msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    lurk_protocol_message_type_write(msg, &seeker);

    struct ftr_brokeu16 b_initial_points, b_stat_limit, b_description_length;

    ftr_break_u16l(ref->initial_points, &b_initial_points);
    ftr_break_u16l(ref->stat_limit, &b_stat_limit);
    ftr_break_u16l(ref->description_length, &b_description_length);

    ftr_swrite_u16(&seeker, &b_initial_points);
    ftr_swrite_u16(&seeker, &b_stat_limit);
    ftr_swrite_u16(&seeker, &b_description_length);

    ftr_swrite_bytes(&seeker, ref->description, ref->description_length);

    ftr_u8 * data = malloc(size);

    memcpy(data, buffer->data, size);

    ftr_free_buffer(buffer);

    return data;
}
