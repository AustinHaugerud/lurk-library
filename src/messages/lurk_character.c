//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include<string.h>
#include"messages/lurk_character.h"

int get_bit(struct lurk_character * msg, char index)
{
    return (msg->flags & (1 << index)) >> index;
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
