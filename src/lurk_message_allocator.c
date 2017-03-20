//
// Created by reaver on 3/20/17.
//

#include"lurk_message_allocator.h"
#include<stdlib.h>

struct lurk_protocol_message * lurk_allocate_message(int type)
{
    if(type == LURK_ACCEPT)
    {
        return lurk_accept_create()->protocol;
    }
    else if(type == LURK_CHANGEROOM)
    {
        return lurk_changeroom_create()->protocol;
    }
    else if(type == LURK_CHARACTER)
    {
        return lurk_character_create()->protocol;
    }
    else if(type == LURK_CONNECTION)
    {
        return lurk_connection_create()->protocol;
    }
    else if(type == LURK_ERROR)
    {
        return lurk_error_create()->protocol;
    }
    else if(type == LURK_FIGHT)
    {
        return lurk_fight_create()->protocol;
    }
    else if(type == LURK_GAME)
    {
        return lurk_game_create()->protocol;
    }
    else if(type == LURK_LEAVE)
    {
        return lurk_leave_create()->protocol;
    }
    else if(type == LURK_LOOT)
    {
        return lurk_loot_create()->protocol;
    }
    else if(type == LURK_MESSAGE)
    {
        return lurk_message_create()->protocol;
    }
    else if(type == LURK_PVPFIGHT)
    {
        return lurk_pvpfight_create()->protocol;
    }
    else if(type == LURK_ROOM)
    {
        return lurk_room_create()->protocol;
    }
    else if(type == LURK_START)
    {
        return lurk_start_create()->protocol;
    }
    else
    {
        return NULL;
    }
}
