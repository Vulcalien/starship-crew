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
#include "level.h"

#include <unistd.h>

static u32 ship_count = 0;
static u32 ship_array_size = 0;
static struct starship *ships = NULL;

void level_init(void) {
    ship_array_size = 8;
    ships = malloc(sizeof(struct starship) * ship_array_size);

    // DEBUG
    ship_count = 1;
    ships[0] = (struct starship) {
        .location = {
            .x = 5.5,
            .y = 7.0,

            .angle = 0
        },
        .speed = 2
    };
}

void level_tick(void) {
    for(u32 i = 0; i < ship_count; i++) {
        struct starship *ship = &ships[i];

        // movement
        ship->location.x += (ship->speed / GAME_TPS)
                            * cos(ship->location.angle);
        ship->location.y += (ship->speed / GAME_TPS)
                            * sin(ship->location.angle);
    }
}

void level_send_init_data(int client_socket) {
    write(client_socket, &ship_count, sizeof(u32));
    write(client_socket, ships, ship_count * sizeof(struct starship));
}
