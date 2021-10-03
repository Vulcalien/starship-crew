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
#include <pthread.h>

pthread_mutex_t level_mutex = PTHREAD_MUTEX_INITIALIZER;

static u32 ship_count = 0;
static u32 ship_array_size = 0;
static struct starship *ships = NULL;

void level_init(void) {
    ship_array_size = 8;
    ships = malloc(ship_array_size * sizeof(struct starship));
}

void level_destroy(void) {
    // FIXME the mutex is statically allocated,
    // is this really necessary?
    pthread_mutex_destroy(&level_mutex);
}

void level_tick(void) {
    pthread_mutex_lock(&level_mutex);

    for(u32 i = 0; i < ship_count; i++) {
        struct starship *ship = &ships[i];

        // movement
        ship->location.x += (ship->speed / GAME_TPS)
                            * cos(ship->location.angle);
        ship->location.y += (ship->speed / GAME_TPS)
                            * sin(ship->location.angle);
    }

    pthread_mutex_unlock(&level_mutex);
}

void level_add_ship(void) {
    pthread_mutex_lock(&level_mutex);

    if(ship_count == ship_array_size) {
        ship_array_size += 8;
        ships = realloc(ships, ship_array_size * sizeof(struct starship));
    }

    // DEBUG use random data (?)
    ships[ship_count] = (struct starship) {
        .location = {
            .x = 5.5,
            .y = 7.0,

            .angle = 0
        },
        .speed = 2
    };
    ship_count++;

    pthread_mutex_unlock(&level_mutex);
}

void level_send_init_data(int client_socket) {
    write(client_socket, &ship_count, sizeof(u32));
    write(client_socket, ships, ship_count * sizeof(struct starship));
}
