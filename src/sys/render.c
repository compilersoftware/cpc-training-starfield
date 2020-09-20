#include "render.h"
#include <man/entity.h>

/* Atributos privados */

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

/* Funciones privadas */

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    // Borra la anterior (si existe)
    if (entity->prevPtr != 0) {
        *entity->prevPtr = 0;
    }

    // Dibuja la actual (si no está marcada para destruir)
    // Draw current (if it is not marked for destruction)
    if (!(entity->type & entityTypeDead)) {
        u8* pVideoMem = cpct_getScreenPtr(CPCT_VMEM_START, entity->x, entity->y);
        // Escribe entity->colour en la celda de memoria a la que apunta pVideoMem
        *pVideoMem = entity->colour; 
        entity->prevPtr = pVideoMem;
    }
}

/* Funciones públicas */

void sys_render_init()
{
    cpct_setVideoMode(0);
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(_palette, sizeof(_palette));
}

void sys_render_update()
{
    man_entity_forAll(_sys_render_updateSingleEntity);
}