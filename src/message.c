/* Copyright 2021 Vulcalien
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 only.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "message.h"

#include <unistd.h>
#include <pthread.h>

// TODO to destroy or not to destroy?
static pthread_mutex_t socket_list_mutex = PTHREAD_MUTEX_INITIALIZER;

static u32 socket_list_size = 0;
static int *socket_list = NULL;

void message_add_socket(int sock) {
    pthread_mutex_lock(&socket_list_mutex);

    if(socket_list_size % 8 == 0)
        socket_list = realloc(
            socket_list,
            (socket_list_size + 8) * sizeof(int)
        );

    socket_list[socket_list_size] = sock;
    socket_list_size++;

    pthread_mutex_unlock(&socket_list_mutex);
}

void message_remove_socket(int sock) {
    pthread_mutex_lock(&socket_list_mutex);

    for(u32 i = 0; i < socket_list_size; i++) {
        if(socket_list[i] == sock) {
            // just copy the last item to the position
            // of the item being removed and decrement
            // the list size
            socket_list[i] = socket_list[socket_list_size - 1];
            socket_list_size--;

            break;
        }
    }

    pthread_mutex_unlock(&socket_list_mutex);
}

static void write_message(int sock, struct message *msg) {
    write(sock, &msg->id, sizeof(msg->id));
    write(sock, msg->content, msg->size);
}

void message_sendto(int sock, struct message *msg) {
    write_message(sock, msg);
}

void message_sendall(struct message *msg) {
    pthread_mutex_lock(&socket_list_mutex);

    for(u32 i = 0; i < socket_list_size; i++) {
        int sock = socket_list[i];
        write_message(sock, msg);
    }

    pthread_mutex_unlock(&socket_list_mutex);
}

/*
 * Maybe this is unnecessary
 * This was already removed in message.h
 *
void message_sendall_except(int except_sock, struct message *msg) {
    pthread_mutex_lock(&socket_list_mutex);

    for(u32 i = 0; i < socket_list_size; i++) {
        int sock = socket_list[i];
        if(sock != except_sock)
            write_message(sock, msg);
    }

    pthread_mutex_unlock(&socket_list_mutex);
}
*/
