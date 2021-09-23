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
#ifndef VULC_STARSHIP_LEVEL
#define VULC_STARSHIP_LEVEL

#include "server.h"

#include <math.h>

#define ROTATION_UNIT (M_PI / 4 / 8)

struct location {
    double x;
    double y;

    float angle;
};

struct starship {
    struct location location;

    float speed;
    // TODO energy, fuel (?), shield level...
};

extern void tick(void);

#endif // VULC_STARSHIP_LEVEL