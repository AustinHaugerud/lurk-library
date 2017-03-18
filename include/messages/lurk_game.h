//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_GAME_H
#define LURK_LURK_GAME_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_STAT_LIMIT_MAX = 65535

struct lurk_game
{
    struct lurk_protocol_message * protocol;

    ftr_u16 initial_points;

    ftr_u16 stat_limit;

    ftr_u16 description_length;

    ftr_u8 * description;
};

struct lurk_game * lurk_game_allocate();

struct lurk_game * lurk_game_create();

void lurk_game_head_free(struct lurk_protocol_message * msg);

void lurk_game_free(struct lurk_game *);

void lurk_game_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

#endif //LURK_LURK_GAME_H
