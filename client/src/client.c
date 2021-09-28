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
#include "client.h"

#include <stdio.h>
#include <string.h>

#include "server_io.h"

static void print_usage(const char *executable_name) {
    printf("Usage: %s ROLE STARSHIP_ID\n", executable_name);
}

int main(int argc, const char *argv[]) {
    // determine what the user's role is
    if(argc < 3) {
        print_usage(argv[0]);
        return -1;
    }

    const char *role_str = argv[1];
    if(!strcmp(role_str, "captain")) {
        // TODO ...
    } // else if.....
    // ...

    int starship_id = atoi(argv[2]);

    // connect to server
    if(server_connect())
        return -1;

    return 0;
}
