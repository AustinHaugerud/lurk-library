//
// Created by reaver on 3/17/17.
//

#ifndef LURK_LURK_HEADER_H
#define LURK_LURK_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include<ftr_types.h>
#include"lurk_data_source.h"

#define LURK_MESSAGE 1
#define LURK_CHANGEROOM 2
#define LURK_FIGHT 3
#define LURK_PVPFIGHT 4
#define LURK_LOOT 5
#define LURK_START 6
#define LURK_ERROR 7
#define LURK_ACCEPT 8
#define LURK_ROOM 9
#define LURK_CHARACTER 10
#define LURK_GAME 11
#define LURK_LEAVE 12
#define LURK_CONNECTION 13

#define LURK_BASE_SIZE 1

#define lurk_message_cast(T,M) (struct T *)(M->derived)

#define lurk_message_upcast(C) (struct lurk_protocol_message *)(C->protocol)

#define lurk_read_message(M,S) M->read(M,S)

#define lurk_free_message(M) M->free(M)

#define lurk_head_create_message()    __alloc_lurk_message_head__(LURK_MESSAGE)
#define lurk_head_create_changeroom() __alloc_lurk_message_head__(LURK_CHANGEROOM)
#define lurk_head_create_fight()      __alloc_lurk_message_head__(LURK_FIGHT)
#define lurk_head_create_pvpfight()   __alloc_lurk_message_head__(LURK_PVPFIGHT)
#define lurk_head_create_loot()       __alloc_lurk_message_head__(LURK_LOOT)
#define lurk_head_create_start()      __alloc_lurk_message_head__(LURK_START)
#define lurk_head_create_error()      __alloc_lurk_message_head__(LURK_ERROR)
#define lurk_head_create_accept()     __alloc_lurk_message_head__(LURK_ACCEPT)
#define lurk_head_create_room()       __alloc_lurk_message_head__(LURK_ROOM)
#define lurk_head_create_character()  __alloc_lurk_message_head__(LURK_CHARACTER)
#define lurk_head_create_game()       __alloc_lurk_message_head__(LURK_GAME)
#define lurk_head_create_leave()      __alloc_lurk_message_head__(LURK_LEAVE)
#define lurk_head_create_connection() __alloc_lurk_message_head__(LURK_CONNECTION)

#define lurk_head_bind_refs(C,T) C->protocol->derived=C; \
                                 C->protocol->free = T ## _head_free; \
                                 C->protocol->read = T ## _read; \
                                 C->protocol->blob = T ## _blob; \
                                 C->protocol->blob_size = T ## _blob_size;

#define lurk_free_head(C) lurk_protocol_message_free(C->protocol)

#define lurk_message_size(M) M->blob_size(M)
#define lurk_protocol_message_blob(M) M->blob(M)

#define lurk_message_type(C) C->protocol->type

struct ftr_io_buffer_seeker;

struct lurk_protocol_message
{
    ftr_u8 type;
    void * derived;

    void (*read)(struct lurk_protocol_message * self, struct lurk_data_source * src);

    void (*free)(struct lurk_protocol_message * self);

    ftr_u8 * (*blob)(struct lurk_protocol_message *);

    ftr_u16 (*blob_size)(struct lurk_protocol_message *);
};

struct lurk_protocol_message * lurk_protocol_message_allocate();

void lurk_protocol_message_free(struct lurk_protocol_message * msg);

void lurk_protocol_message_type_write(struct lurk_protocol_message *, struct ftr_io_buffer_seeker *);

struct lurk_protocol_message * __alloc_lurk_message_head__(int type);

#ifdef __cplusplus
}
#endif

#endif //LURK_LURK_HEADER_H
