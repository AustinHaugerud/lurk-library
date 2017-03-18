//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_CHARACTER_H
#define LURK_LURK_CHARACTER_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_CHARACTER_ALIVE       0
#define LURK_CHARACTER_JOIN_BATTLE 1
#define LURK_CHARACTER_MONSTER     3
#define LURK_CHARACTER_STARTED     4
#define LURK_CHARACTER_READY       5

#define LURK_CHARACTER_NAME_LENGTH 32

struct lurk_character
{
    struct lurk_protocol_message * protocol;

    ftr_u8 name[LURK_CHARACTER_NAME_LENGTH];

    ftr_u8 flags;

    ftr_u16 attack;
    ftr_u16 defense;
    ftr_u16 regen;

    ftr_s16 health;

    ftr_u16 gold;

    ftr_u16 current_room_number;

    ftr_u16 description_length;

    ftr_u8 * description;
};

struct lurk_character * lurk_character_allocate();

struct lurk_character * lurk_character_create();

void lurk_character_free(struct lurk_character *);

void lurk_character_head_free(struct lurk_protocol_message * msg);

int lurk_character_alive(struct lurk_character *);

int lurk_character_join_battle(struct lurk_character *);

int lurk_character_monster(struct lurk_character *);

int lurk_character_started(struct lurk_character *);

int lurk_character_ready(struct lurk_character *);

void lurk_character_read(struct lurk_protocol_message * self, struct lurk_data_source * src);

#endif //LURK_LURK_CHARACTER_H
