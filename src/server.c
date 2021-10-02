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
#include "server.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "gameloop.h"
#include "level.h"
#include "client_io.h"

static void on_interrupt(int arg) {
    puts("Shutting the server\n");

    // TODO destroy everything

    exit(0);
}

static int open_server(u16 port, int *server_socket) {
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };

    if(bind(
        *server_socket, (struct sockaddr *) &server_addr,
        sizeof(struct sockaddr_in)
    )) {
        fputs("Error: cannot bind\n", stderr);
        return -1;
    }

    if(listen(*server_socket, 16)) {
        fputs("Error: cannot listen\n", stderr);
        return -1;
    }
    return 0;
}

int main(int argc, const char *argv[]) {
    signal(SIGINT, on_interrupt);

    u16 port = 0;

    // parse arguments
    for(u32 i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--port")) {
            // if this is the last argument, make the Usage message print
            if(i == argc - 1)
                break;

            // if atoi fails, port will be 0
            // causing the Usage message to print
            port = atoi(argv[i + 1]);
       }
    }

    // check if port is set and print a "Usage..."
    // message in case it is not
    if(port == 0) {
        printf("Usage: %s -p PORT\n", argv[0]);
        return -1;
    }

    int server_socket;
    if(open_server(port, &server_socket))
        return -1;

    level_init();

    pthread_t gameloop_thread;
    pthread_create(&gameloop_thread, NULL, gameloop, NULL);

    // accept clients
    while(true)
        client_accept(server_socket);

    return 0;
}

u64 nanotime(void) {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * (1000 * 1000 * 1000) + time.tv_nsec;
}
