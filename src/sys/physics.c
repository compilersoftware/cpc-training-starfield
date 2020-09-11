#include "physics.h"
#include <man/entity.h>

void _sys_physics_updateSingleEntity(Entity_t* e)
{
    // Copy into a variable just for comparison
    u8 newX = e->x + e->vx;
    if (newX > e->x) {
        man_entity_destroy(e);
        // Better do man_entity_markForDestruction(e);
    } else {
        e->x = newX;
    }
}

void sys_physics_update()
{
    // Inversion of control - Very clear and useful
    man_entity_forAll(_sys_physics_updateSingleEntity);
}
