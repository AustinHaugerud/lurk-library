//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_LOOT_H
#define LURK_LURK_LOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_LOOT_TARGET_PLAYER_LENGTH 32

struct lurk_loot
{
    struct lurk_protocol_message * protocol;
    ftr_u8 target_player[32];
};

struct lurk_loot * lurk_loot_allocate();

struct lurk_loot * lurk_loot_create();

void lurk_loot_head_free(struct lurk_protocol_message * msg);

void lurk_loot_free(struct lurk_loot *);

void lurk_loot_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_loot_blob_size(struct lurk_protocol_message *);

ftr_u8 * lurk_loot_blob(struct lurk_protocol_message *);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_LOOT_H
