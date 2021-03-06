#include "render.h"
#include <man/entity.h>

/* Atributos privados */

const u8 _palette[] = {
    HW_BLACK,           
    HW_BLUE,            // Color velocidad 1
    HW_SKY_BLUE,        // Color velocidad 2
    HW_BRIGHT_BLUE,     // Color velocidad 3
    HW_BRIGHT_CYAN,     // Color velocidad 4
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

/**
 * @precondition speed ha de tener un valor entre 1 y 4
 */
u8 _sys_render_getColourFromSpeed(u8 speed)
{
    switch (speed) {
        case 1:
            return 0x80;
        case 2:
            return 0x08;
        case 3:
            return 0x88;
        case 4:
            return 0x20;
        default:
            // No debería ocurrir, lo ponemos para evitar el warning del compilador
            return 0x00;
    }
}

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    // Borra la anterior (si existe)
    if (entity->prevPtr != 0) {
        *entity->prevPtr = 0;
    }

    // Dibuja la actual (si no está marcada para destruir)
    // Draw current (if it is not marked for destruction)
    if (!(entity->type & entityTypeDead)) {
        u8 x = entity->x;
        // x tiene la coordenada "real", pero en Modo 0, cada posición son 2 píxeles
        u8* pVideoMem = cpct_getScreenPtr(CPCT_VMEM_START, x >> 1, entity->y);

        u8 colour = _sys_render_getColourFromSpeed(entity->speed);
        // Movimiento al píxel
        // Si x es par, escribimos en el píxel de la izquierda. Si es impar, en el de la derecha
        if (x & 0x01) {
            colour = colour >> 1;
        }

        // Escribe colour en la celda de memoria a la que apunta pVideoMem
        *pVideoMem = colour; 
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