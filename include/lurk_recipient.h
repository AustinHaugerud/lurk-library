//
// Created by reaver on 3/18/17.
//

#ifndef LURK_LURK_RECIPIENT_H
#define LURK_LURK_RECIPIENT_H

#ifdef __cplusplus
extern "C" {
#endif

struct lurk_server_connection;
struct lurk_client_connection;
struct lurk_protocol_message;

#include<ftr_types.h>

#define LURK_RECIPIENT_SERVER 0
#define LURK_RECIPIENT_CLIENT 1

struct lurk_recipient
{
    int type;
    union
    {
        struct lurk_server_connection * server_connection;
        struct lurk_client_connection * client_connection;
    };
};

struct lurk_recipient * lurk_recipient_allocate();

void lurk_recipient_free(struct lurk_recipient *);

struct lurk_recipient * lurk_recipient_make_to_server(struct lurk_server_connection *);

struct lurk_recipient * lurk_recipient_make_to_client(struct lurk_client_connection *);

void lurk_recipient_write(struct lurk_recipient * recipient, ftr_u8 * data, ftr_u16 len);

void lurk_recipient_write_u8(struct lurk_recipient * recipient, ftr_u8 val);

void lurk_recipient_write_u16(struct lurk_recipient * recipient, ftr_u16 val);

void lurk_recipient_write_s16(struct lurk_recipient * recipient, ftr_s16 val);

void lurk_recipient_write_protocol_message(struct lurk_recipient *, struct lurk_protocol_message *);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_RECIPIENT_H
