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

#define WRITE(fd, string) write(fd, string, sizeof(string))

#define MAGIC_NUMBER ((u64) 0x6a24d479)

static int handshake(int client_socket) {
    u64 read_number;
    read(client_socket, &read_number, sizeof(u64));

    if(read_number != MAGIC_NUMBER) {
        WRITE(client_socket, "Wrong magic number");
        return -1;
    } else {
        WRITE(client_socket, "OK");
    }

    return 0;
}

void client_accept(int server_socket) {
    struct sockaddr_in client_addr;
    socklen_t socket_len = sizeof(struct sockaddr_in);

    int client_socket = accept(
        server_socket, (struct sockaddr *) &client_addr,
        &socket_len
    );

    // TODO transfer control to another thread
    // because handshake could block execution

    if(handshake(client_socket)) {
        close(client_socket);
        return;
    }

    // TODO ...
}
