#include "generator.h"
#include <man/entity.h>
#include <sys/starfield.h>

/* Constantes privadas */
const Entity_t _initEntity = {
    entityTypeStar, // type
    159, 1,         // x, y
    1,              // speed
    0x80,           // colour
    0x0000          // prevPtr
};

/* Funciones privadas */

void _sys_generator_setEntityStartPositionFromOrientation(Entity_t* entity, Orientation_t* orientation)
{
    if (orientation->x < 0) {
        entity->x = 159;
        entity->y = cpct_rand() % 200;
        return;
    }
    if (orientation->x > 0) {
        entity->x = 0;
        entity->y = cpct_rand() % 200;
        return;
    }
    if (orientation->y < 0) {
        entity->x = cpct_rand() % 160;
        entity->y = 199;
        return;
    }
    if (orientation->y > 0) {
        entity->x = cpct_rand() % 160;
        entity->y = 0;
        return;
    }
}

/**
 * Crea e inicializa una nueva entidad estrella
 * 
 * @precondition Debe haber espacio en memoria disponible para nuevas entidades
 */
void _sys_generator_generateNewStar()
{
    Orientation_t* orientation = sys_starfield_getOrientation();
    Entity_t *entity = man_entity_create();
    cpct_memcpy(entity, &_initEntity, sizeof(Entity_t));
    
    _sys_generator_setEntityStartPositionFromOrientation(entity, orientation);
    entity->speed = 1 + (cpct_rand() & 0x03); // Genera valores entre 1 y 4
}

/* Funciones públicas */

void sys_generator_update()
{
    u8 freeSpace = man_entity_freeSpace();
    if (freeSpace > 0) {
        _sys_generator_generateNewStar();
    }
}
