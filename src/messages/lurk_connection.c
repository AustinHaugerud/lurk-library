//
// Created by reaver on 3/17/17.
//

#include<stdlib.h>
#include <string.h>
#include"messages/lurk_connection.h"

struct lurk_connection * lurk_connection_allocate()
{
    return malloc(sizeof(struct lurk_connection));
}

struct lurk_connection * lurk_connection_create()
{
    struct lurk_connection * result = lurk_connection_allocate();
    result->protocol = lurk_head_create_connection();
    lurk_head_bind_refs(result, lurk_connection);
    return result;
}

void lurk_connection_head_free(struct lurk_protocol_message * msg)
{
    struct lurk_connection * ref = lurk_message_cast(lurk_connection, msg);
    lurk_connection_free(ref);
}

void lurk_connection_free(struct lurk_connection * msg)
{
    lurk_free_head(msg);
    free(msg->description);
    free(msg);
}

void lurk_connection_read(struct lurk_protocol_message * msg, struct lurk_data_source * src)
{
    struct lurk_connection * ref = lurk_message_cast(lurk_connection, msg);

    ref->room_number = lurk_data_source_read_u16(src);

    char * nameData = lurk_data_source_read(src, LURK_CONNECTION_ROOM_NAME_LENGTH);
    memcpy(ref->room_name, nameData, LURK_CONNECTION_ROOM_NAME_LENGTH);
    free(nameData);

    ref->description_length = lurk_data_source_read_u16(src);

    ref->description = (ftr_u8*)lurk_data_source_read(src, ref->description_length);
}
