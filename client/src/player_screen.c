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
#include "player_screen.h"

#include "vulcalien/screen.h"

#include "level.h"

void player_screen_init(void) {
    screen_terminal_prepare();

    screen_create();
    screen_setsize(80, 24);
}

void player_screen_destroy(void) {
    screen_destroy();

    screen_terminal_reset();
}

void player_screen_render(void) {
    screen_clear(' ', NULL);

    level_render();

    screen_render();
}
