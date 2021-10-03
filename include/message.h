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
#ifndef VULC_STARSHIP_MESSAGE
#define VULC_STARSHIP_MESSAGE

#include "server.h"

struct message {
    u8    id;
    u32   size;
    void *content;
};

extern void message_add_socket    (int sock);
extern void message_remove_socket (int sock);

extern void message_sendto         (int sock, struct message *msg);
extern void message_sendall        (struct message *msg);

#endif // VULC_STARSHIP_MESSAGE
