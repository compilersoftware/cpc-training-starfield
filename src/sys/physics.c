#include "physics.h"
#include <man/entity.h>

/**
 * Private functions
 */

void _sys_physics_updateSingleEntity(Entity_t* entity)
{
    // Copy into a variable just for comparison
    u8 newX = entity->x + entity->vx;
    if (newX > entity->x) {
        man_entity_destroy(entity);
        // Better do man_entity_markForDestruction(e);
    } else {
        entity->x = newX;
    }
}

/**
 * Public functions
 */

void sys_physics_update()
{
    // Inversion of control - Very clear and useful
    man_entity_forAll(_sys_physics_updateSingleEntity);
}
