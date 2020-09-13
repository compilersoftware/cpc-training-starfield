//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"

// Init entity
const Entity_t initEntity = {
    entityTypeStar, // type
    79, 1,          // x, y
    -1,             // vx
    0xFF,           // colour
    0x0000          // prevPtr
};

void _createEntity()
{
    Entity_t *entity = man_entity_create();
    cpct_memcpy(entity, &initEntity, sizeof(Entity_t));
    entity->y = cpct_rand() % 200;
    entity->vx = -1 - (cpct_rand() & 0x03);
}

void _wait(u8 n)
{
    do {
        // cpct_waitHalts() does not exist
        // Wait loop
        for (u16 i = 0; i < 500; i++) {
        }
        cpct_waitVSYNC();
    } while (n--);
}

void main(void)
{
    u8 numEntities = 5;

    // Init video mode
    cpct_disableFirmware();
    cpct_setVideoMode(0);
    cpct_setVideoMode(HW_BLACK);
    cpct_setPALColour(0, HW_BLACK);

    // Init entity manager and create entities
    man_entity_init();
    for (u8 i = numEntities; i > 0; i--) {
        _createEntity();
    }

    // Loop forever
    while(1) {

        // Update systems
        sys_physics_update();
        sys_render_update();
        // Update manager
        man_entity_update();

        _wait(10);
    }
}
