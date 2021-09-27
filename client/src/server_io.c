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
#include "server_io.h"

#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define WRITE(fd, string) write(fd, string, sizeof(string))

#define MAGIC_NUMBER ((u64) 0x6a24d479)

static int client_socket;

static int handshake(int starship_id) {
    u64 number = MAGIC_NUMBER;
    write(client_socket, &number, sizeof(u64));
    return 0;
}

int server_connect(int starship_id) {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // TODO get the server address from somewhere
    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_family = AF_INET,
        .sin_port = htons(1272)
    };

    if(connect(
        client_socket, (struct sockaddr *) &server_addr,
        sizeof(struct sockaddr_in)
     )) {
        fputs("Error: cannot connect\n", stderr);
        return -1;
    }

    if(handshake(starship_id)) {
        close(client_socket);
        return -1;
    }

    // TODO ...

    return 0;
}
