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
#include "gameloop.h"

#include <time.h>

#include "level.h"
#include "player_screen.h"

#define NANOS_PER_TICK ((1000 * 1000 * 1000) / GAME_TPS)

bool gameloop_running = false;

void gameloop(void) {
    u64 last_time = nanotime();
    u64 unprocessed_time = NANOS_PER_TICK;

    gameloop_running = true;
    while(gameloop_running) {
        u64 now = nanotime();
        u64 passed_time = now - last_time;
        last_time = now;

        if(passed_time >= (1000 * 1000 * 1000))
            passed_time = (1000 * 1000 * 1000);

        unprocessed_time += passed_time;

        bool ticked = false;
        while(unprocessed_time >= NANOS_PER_TICK) {
            unprocessed_time -= NANOS_PER_TICK;

            level_tick();
            ticked = true;
        }

        if(ticked)
            player_screen_render();

        // sleep for 2ms
        struct timespec sleep_time = { 0, 2 * 1000 * 1000 };
        nanosleep(&sleep_time, NULL);
    }
}
