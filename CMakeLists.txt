cmake_minimum_required(VERSION 3.6)
project(lurk)

set(CMAKE_C_STANDARD 99)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

add_subdirectory(Frothleikr)

include_directories(${CMAKE_SOURCE_DIR}/Frothleikr/include)
include_directories(include)

set(SOURCE_FILES
        include/lurk.h
        include/lurk_protocol_message.h
        include/messages/lurk_message.h
        include/messages/lurk_changeroom.h
        include/messages/lurk_fight.h
        include/messages/lurk_pvpfight.h
        include/messages/lurk_loot.h
        include/messages/lurk_start.h
        include/messages/lurk_error.h
        include/messages/lurk_accept.h
        include/messages/lurk_room.h
        include/messages/lurk_character.h
        include/messages/lurk_game.h
        include/messages/lurk_leave.h
        include/messages/lurk_connection.h
        src/messages/lurk_message.c
        src/messages/lurk_changeroom.c
        src/messages/lurk_fight.c
        src/messages/lurk_pvpfight.c
        src/messages/lurk_loot.c
        src/messages/lurk_start.c
        src/messages/lurk_error.c
        src/messages/lurk_accept.c
        src/messages/lurk_room.c
        src/messages/lurk_character.c
        src/messages/lurk_game.c
        src/messages/lurk_leave.c
        src/messages/lurk_connection.c
        include/lurk_server_connection.h
        src/lurk_server_connection.c
        include/lurk_data_source.h
        src/lurk_data_source.c
        src/lurk_protocol_message.c
        include/lurk_client_connection.h
        include/lurk_listener.h
        include/lurk_recipient.h
        src/lurk_client_connection.c
        src/lurk_listener.c
        src/lurk_recipient.c
        include/lurk_message_allocator.h
        src/lurk_message_allocator.c
        include/messages/lurk_messages.h
        include/lurk.hpp)

add_library(lurk ${SOURCE_FILES})

target_link_libraries(lurk Frothleikr)
