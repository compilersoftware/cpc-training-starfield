#include "generator.h"
#include <man/entity.h>

/**
 * Private constants
 */
const Entity_t _initEntity = {
    entityTypeStar, // type
    79, 1,          // x, y
    -1,             // vx
    0x80,           // colour
    0x0000          // prevPtr
};

/**
 * Private functions
 */

/**
 * Creates and initializes new star entity
 * 
 * @precondition There must be memory space available for new entities
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