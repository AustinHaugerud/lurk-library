//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_ERROR_H
#define LURK_LURK_ERROR_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_ERROR_OTHER 0
#define LURK_ERROR_BAD_ROOM 1
#define LURK_ERROR_PLAYER_EXISTS 2
#define LURK_ERROR_BAD_MONSTER 3
#define LURK_ERROR_STAT_ERROR 4
#define LURK_ERROR_NOT_READY 5
#define LURK_ERROR_NO_TARGET 6
#define LURK_ERROR_NO_FIGHT 7
#define LURK_ERROR_NO_PVP 8

struct lurk_error
{
    struct lurk_protocol_message * protocol;

    ftr_u8 error_code;

    ftr_u16 error_message_length;

    ftr_u8 * error_message;
};

struct lurk_error * lurk_error_allocate();

struct lurk_error * lurk_error_create();

void lurk_error_head_free(struct lurk_protocol_message * msg);

void lurk_error_free(struct lurk_error *);

void lurk_error_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

#endif //LURK_LURK_ERROR_H
