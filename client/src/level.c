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

#include "vulcalien/screen.h"

#include "common/player_types.h"

static u32 ship_count = 0;
static u32 ship_array_size = 0;
static struct starship *ships = NULL;

void level_init(void) {
    ship_array_size = 8;
    ships = malloc(sizeof(struct starship) * ship_array_size);
}

void level_tick(void) {
    for(u32 i = 0; i < ship_count; i++) {
        struct starship ship = ships[i];

        // movement
        ship.location.x += ship.speed * cos(ship.location.angle);
        ship.location.y += ship.speed * sin(ship.location.angle);
    }
}

void level_render(void) {
    for(u32 i = 0; i < ship_count; i++) {
        struct starship ship = ships[i];

        screen_setchar(
            ship.location.x, ship.location.y,
            '#', NULL
        );
    }
}
