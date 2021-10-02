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
#include "client_io.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "player.h"
#include "level.h"

#define MAGIC_NUMBER ((u64) 0x6a24d479)

static int handshake(int client_socket) {
    u64 read_number;
    read(client_socket, &read_number, sizeof(u64));

    if(read_number != MAGIC_NUMBER)
        return -1;

    return 0;
}

static void *client_thread(void *client_socket_ptr) {
    int client_socket = *((int *) client_socket_ptr);
    free(client_socket_ptr);

    if(!handshake(client_socket)) {
        level_add_ship();
        level_send_init_data(client_socket);
    }

    close(client_socket);
    return NULL;
}

void client_accept(int server_socket) {
    struct sockaddr_in client_addr;
    socklen_t socket_len = sizeof(struct sockaddr_in);

    int *client_socket = malloc(sizeof(int));
    *client_socket = accept(
        server_socket, (struct sockaddr *) &client_addr,
        &socket_len
    );

    // this value will be deallocated
    // soon after creating the thread
    pthread_t thread;

    pthread_create(&thread, NULL, client_thread, client_socket);
}
