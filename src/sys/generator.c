#include "generator.h"
#include <man/entity.h>

/* Constantes privadas */
const Entity_t _initEntity = {
    entityTypeStar, // type
    79, 1,          // x, y
    -1,             // vx
    0x80,           // colour
    0x0000          // prevPtr
};

/* Funciones privadas */

/**
 * Crea e inicializa una nueva entidad estrella
 * 
 * @precondition Debe haber espacio en memoria disponible para nuevas entidades
 */
void _generateNewStar()
{
    Entity_t *entity = man_entity_create();
    cpct_memcpy(entity, &_initEntity, sizeof(Entity_t));
    entity->y = cpct_rand() % 200;
    entity->vx = -1 - (cpct_rand() & 0x03);
}

void sys_generator_update()
{
    u8 freeSpace = man_entity_freeSpace();
    if (freeSpace > 0) {
        _generateNewStar();
    }
}