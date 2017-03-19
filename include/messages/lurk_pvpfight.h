//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_PVPFIGHT_H
#define LURK_LURK_PVPFIGHT_H

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_PVPFIGHT_TARGET_NAME_LENGTH 32

struct lurk_pvpfight
{
    struct lurk_protocol_message * protocol;
    ftr_u8 target_name[LURK_PVPFIGHT_TARGET_NAME_LENGTH];
};

struct lurk_pvpfight * lurk_pvpfight_allocate();

struct lurk_pvpfight * lurk_pvpfight_create();

void lurk_pvpfight_head_free(struct lurk_protocol_message *);

void lurk_pvpfight_free(struct lurk_pvpfight *);

void lurk_pvpfight_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_pvpfight_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_pvpfight_blob(struct lurk_protocol_message * msg);

#endif //LURK_LURK_PVPFIGHT_H
