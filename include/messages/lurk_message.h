//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_MESSAGE_H
#define LURK_LURK_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include"lurk_protocol_message.h"
#include"lurk_data_source.h"

#define LURK_MESSAGE_RECIPIENT_NAME_LENGTH 32
#define LURK_MESSAGE_SENDER_NAME_LENGTH 32

struct lurk_message
{

    struct lurk_protocol_message * protocol;

    ftr_u16 message_length;

    ftr_u8 recipient_name[LURK_MESSAGE_RECIPIENT_NAME_LENGTH];

    ftr_u8  sender_name[LURK_MESSAGE_SENDER_NAME_LENGTH];

    ftr_u8 * message;
};

struct lurk_message * lurk_message_allocate();

struct lurk_message * lurk_message_create();

void lurk_message_head_free(struct lurk_protocol_message * msg);

void lurk_message_free(struct lurk_message * );

void lurk_message_read(struct lurk_protocol_message * msg, struct lurk_data_source * src);

ftr_u16 lurk_message_blob_size(struct lurk_protocol_message * msg);

ftr_u8 * lurk_message_blob(struct lurk_protocol_message * msg);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_MESSAGE_H
