#include "physics.h"
#include <man/entity.h>
#include <sys/starfield.h>

/* Funciones privadas */

u8 _sys_physics_isEntityOutOfBoundsBasedOnOrientation(Entity_t* entity, u8 newX, u8 newY, Orientation_t* orientation)
{
    if ((orientation->x < 0) 
        && (newX > entity->x)
    ) {
        return 1;
    }
    if ((orientation->x > 0)
        && (newX > 159)
    ) {
        return 1;
    }
    if ((orientation->y < 0)
        && (newY > entity->y)
    ) {
        return 1;
    }
    if ((orientation->y > 0)
        && (newY > 199)
    ) {
        return 1;
    }
    return 0;
}

void _sys_physics_updateSingleEntity(Entity_t* entity)
{
    Orientation_t* orientation = sys_starfield_getOrientation();
    
    u8 newX = entity->x + (orientation->x * entity->speed);
    // Como en Modo 0 los píxeles son el doble de ancho que de alto, en el eje vertical duplicamos la velocidad
    u8 newY = entity->y + (orientation->y * entity->speed * 2);
    if (_sys_physics_isEntityOutOfBoundsBasedOnOrientation(entity, newX, newY, orientation) == 1) {
        man_entity_markForDestruction(entity);
    }
    entity->x = newX;
    entity->y = newY;
}

/* Funciones públicas */

void sys_physics_update()
{
    // Inversión de control, un patrón muy claro y útil, una vez se entiende
    man_entity_forAll(_sys_physics_updateSingleEntity);
}
