#include "physics.h"
#include <man/entity.h>

/* Funciones privadas */

void _sys_physics_updateSingleEntity(Entity_t* entity)
{
    // Creamos una copia en una variable local para facilitar la comparación
    u8 newX = entity->x + entity->vx;
    if (newX > entity->x) {
        man_entity_markForDestruction(entity);
    }
    entity->x = newX;
}

/* Funciones públicas */

void sys_physics_update()
{
    // Inversión de control, un patrón muy claro y útil, una vez se entiende
    man_entity_forAll(_sys_physics_updateSingleEntity);
}
