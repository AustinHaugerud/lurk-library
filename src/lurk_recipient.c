//
// Created by reaver on 3/18/17.
//

#include<stdlib.h>
#include"lurk_recipient.h"
#include"lurk_server_connection.h"
#include"lurk_client_connection.h"
#include<ftr_broke_types.h>
#include<unistd.h>
#include <frothleikr.h>
#include"lurk_protocol_message.h"

struct lurk_recipient * lurk_recipient_allocate()
{
    return malloc(sizeof(struct lurk_recipient));
}

void lurk_recipient_free(struct lurk_recipient * recipient)
{
    free(recipient);
}

struct lurk_recipient * lurk_recipient_make_to_server(struct lurk_server_connection * server_connection)
{
    struct lurk_recipient * recipient = lurk_recipient_allocate();

    recipient->type = LURK_RECIPIENT_SERVER;

    recipient->server_connection = server_connection;

    return recipient;
}

struct lurk_recipient * lurk_recipient_make_to_client(struct lurk_client_connection * client_connection)
{
    struct lurk_recipient * recipient = lurk_recipient_allocate();

    recipient->type = LURK_RECIPIENT_CLIENT;

    recipient->client_connection = client_connection;

    return recipient;
}

void lurk_recipient_write(struct lurk_recipient * recipient, ftr_u8 * data, ftr_u16 len)
{
    if(recipient->type == LURK_RECIPIENT_SERVER)
    {
        write(recipient->server_connection->socket, data, len);
    }
    else if(recipient->type == LURK_RECIPIENT_CLIENT)
    {
        write(recipient->client_connection->socket, data, len);
    }
}

void lurk_recipient_write_u8(struct lurk_recipient * recipient, ftr_u8 val)
{
    // 1 byte can't have wrong endian order
    lurk_recipient_write(recipient, &val, sizeof(ftr_u8));
}

void lurk_recipient_write_u16(struct lurk_recipient * recipient, ftr_u16 val)
{
    struct ftr_brokeu16 broke;
    ftr_break_u16l(val, &broke);
    lurk_recipient_write(recipient, broke.bytes, sizeof(ftr_u16));
}

void lurk_recipient_write_s16(struct lurk_recipient * recipient, ftr_s16 val)
{
    struct ftr_brokes16 broke;
    ftr_break_s16l(val, &broke);
    lurk_recipient_write(recipient, broke.bytes, sizeof(ftr_s16));
}

void lurk_recipient_write_protocol_message(struct lurk_recipient * recipient, struct lurk_protocol_message * msg)
{
    ftr_u16 blob_size = msg->blob_size(msg);
    ftr_u8 * data = msg->blob(msg);
    lurk_recipient_write(recipient, data, blob_size);
    free(data);
}
