#include "render.h"
#include <man/entity.h>

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    u8* pVideoMem = cpct_getScreenPtr(CPCT_VMEM_START, entity->x, entity->y);
    *pVideoMem = entity->colour; // Writes entity->colour into mem address pVideoMem
}

void sys_render_update()
{
    man_entity_forAll(_sys_render_updateSingleEntity);
}