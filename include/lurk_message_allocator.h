//
// Created by reaver on 3/20/17.
//

#ifndef LURK_LURK_MESSAGE_ALLOCATOR_H
#define LURK_LURK_MESSAGE_ALLOCATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include"lurk_protocol_message.h"
#include"messages/lurk_accept.h"
#include"messages/lurk_changeroom.h"
#include"messages/lurk_character.h"
#include"messages/lurk_connection.h"
#include"messages/lurk_error.h"
#include"messages/lurk_fight.h"
#include"messages/lurk_game.h"
#include"messages/lurk_leave.h"
#include"messages/lurk_loot.h"
#include"messages/lurk_message.h"
#include"messages/lurk_pvpfight.h"
#include"messages/lurk_room.h"
#include"messages/lurk_start.h"

struct lurk_protocol_message * lurk_allocate_message(int type);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_MESSAGE_ALLOCATOR_H
