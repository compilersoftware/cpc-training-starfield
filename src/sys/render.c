#include "render.h"
#include <man/entity.h>

/**
 * Private members
 */

const u8 _palette[] = {
    HW_BLACK,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE
};

/**
 * Private functions
 */

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    // Delete previous (if exists)
    if (entity->prevPtr != 0) {
        *entity->prevPtr = 0;
    }

    // Draw current (if it is not marked for destruction)
    if (!(entity->type & entityTypeDead)) {
        u8* pVideoMem = cpct_getScreenPtr(CPCT_VMEM_START, entity->x, entity->y);
        *pVideoMem = entity->colour; // Writes entity->colour into mem address pVideoMem
        entity->prevPtr = pVideoMem;
    }
}

/**
 * Public functions
 */

void sys_render_init()
{
    cpct_setVideoMode(0);
    cpct_setVideoMode(HW_BLACK);
    cpct_setPalette(_palette, sizeof(_palette));
}

void sys_render_update()
{
    man_entity_forAll(_sys_render_updateSingleEntity);
}