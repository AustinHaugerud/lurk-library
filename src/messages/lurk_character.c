//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include<string.h>
#include <frothleikr.h>
#include"messages/lurk_character.h"

int get_bit(struct lurk_character * msg, char index)
{
    return (msg->flags & (1 << index)) >> index;
}

void set_bit(struct lurk_character * msg, char index)
{
    msg->flags |= 1 << index;
}

void clear_bit(struct lurk_character * msg, char index)
{
    msg->flags &= ~(1 << index);
}

void config_bit(struct lurk_character * msg, int status, char index)
{
    if(status)
    {
        set_bit(msg, index);
    }
    else
    {
        clear_bit(msg, index);
    }
}

struct lurk_character * lurk_character_allocate()
{
    return malloc(sizeof(struct lurk_character));
}

struct lurk_character * lurk_character_create()
{
    struct lurk_character * result = lurk_character_allocate();
    result->protocol = lurk_head_create_character();
    lurk_head_bind_refs(result, lurk_character);
    return result;
}

void lurk_character_free(struct lurk_character * msg)
{
    lurk_free_head(msg);
    free(msg->description);
    free(msg);
}

void lurk_character_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_character * ref = lurk_message_cast(lurk_character, msg);
    lurk_character_free(ref);
}

int lurk_character_alive(struct lurk_character * msg)
{
    return get_bit(msg, LURK_CHARACTER_ALIVE);
}

int lurk_character_join_battle(struct lurk_character * msg)
{
    return get_bit(msg, LURK_CHARACTER_JOIN_BATTLE);
}

int lurk_character_monster(struct lurk_character * msg)
{
    return get_bit(msg, LURK_CHARACTER_MONSTER);
}

int lurk_character_started(struct lurk_character * msg)
{
    return get_bit(msg, LURK_CHARACTER_STARTED);
}

int lurk_character_ready(struct lurk_character * msg)
{
    return get_bit(msg, LURK_CHARACTER_READY);
}

void lurk_character_set_alive(struct lurk_character * msg, int status)
{
    config_bit(msg, status, LURK_CHARACTER_ALIVE);
}

void lurk_character_set_join_battle(struct lurk_character * msg, int status)
{
    config_bit(msg, status, LURK_CHARACTER_JOIN_BATTLE);
}

void lurk_character_set_monster(struct lurk_character * msg, int status)
{
    config_bit(msg, status, LURK_CHARACTER_MONSTER);
}

void lurk_character_set_started(struct lurk_character * msg, int status)
{
    config_bit(msg, status, LURK_CHARACTER_STARTED);
}

void lurk_character_set_ready(struct lurk_character * msg, int status)
{
    config_bit(msg, status, LURK_CHARACTER_READY);
}

void lurk_character_read(struct lurk_protocol_message * self, struct lurk_data_source * src)
{
    struct lurk_character * ref = lurk_message_cast(lurk_character, self);

    char * nameData = lurk_data_source_read(src, LURK_CHARACTER_NAME_LENGTH);
    memcpy(ref->name, nameData, LURK_CHARACTER_NAME_LENGTH);
    free(nameData);

    ref->flags = lurk_data_source_read_u8(src);

    ref->attack = lurk_data_source_read_u16(src);
    ref->defense = lurk_data_source_read_u16(src);
    ref->regen = lurk_data_source_read_u16(src);

    ref->health = lurk_data_source_read_s16(src);

    ref->gold = lurk_data_source_read_u16(src);

    ref->current_room_number = lurk_data_source_read_u16(src);

    ref->description_length = lurk_data_source_read_u16(src);

    ref->description = (ftr_u8*)lurk_data_source_read(src, ref->description_length);
}

ftr_u16 lurk_character_blob_size(struct lurk_protocol_message * msg)
{
    struct lurk_character * ref = lurk_message_cast(lurk_character, msg);
    return LURK_BASE_SIZE +
           LURK_CHARACTER_NAME_LENGTH +
           sizeof(ftr_u8) + // flags
            (3 * sizeof(ftr_u16)) + // stats
            sizeof(ftr_s16) + // health
            sizeof(ftr_u16) + // gold
            sizeof(ftr_u16) + // room number
            sizeof(ftr_u16) + // description length
            + ref->description_length; // description
}

ftr_u8 * lurk_character_blob(struct lurk_protocol_message * msg)
{
    ftr_u16 size = lurk_message_size(msg);
    struct lurk_character * ref = lurk_message_cast(lurk_character, msg);

    struct ftr_io_buffer * buffer = ftr_create_buffer(size);
    struct ftr_io_buffer_seeker seeker;
    ftr_init_seeker(buffer, &seeker, "w");

    // Write type
    lurk_protocol_message_type_write(msg, &seeker);

    // Write name
    ftr_swrite_bytes(&seeker, ref->name, LURK_CHARACTER_NAME_LENGTH);

    // Write flags
    ftr_swrite_bytes(&seeker, &ref->flags, sizeof(ftr_u8));

    struct ftr_brokeu16 b_attack, b_defense, b_regen;

    // Write stats
    ftr_break_u16l(ref->attack, &b_attack);
    ftr_break_u16l(ref->defense, &b_defense);
    ftr_break_u16l(ref->regen, &b_regen);

    ftr_swrite_u16(&seeker, &b_attack);
    ftr_swrite_u16(&seeker, &b_defense);
    ftr_swrite_u16(&seeker, &b_regen);

    struct ftr_brokes16 b_health;

    ftr_break_s16l(ref->health, &b_health);

    // Write health
    ftr_swrite_s16(&seeker, &b_health);

    struct ftr_brokeu16 b_gold, b_current_room_number, b_description_length;

    ftr_break_u16l(ref->gold, &b_gold);
    ftr_break_u16l(ref->current_room_number, &b_current_room_number);
    ftr_break_u16l(ref->description_length, &b_description_length);

    // Write gold, room number, and description length
    ftr_swrite_u16(&seeker, &b_gold);
    ftr_swrite_u16(&seeker, &b_current_room_number);
    ftr_swrite_u16(&seeker, &b_description_length);

    // Write description
    ftr_swrite_bytes(&seeker, ref->description, ref->description_length);

    ftr_u8 * data = malloc(size);
    memcpy(data, buffer->data, size);
    ftr_free_buffer(buffer);

    return data;
}
