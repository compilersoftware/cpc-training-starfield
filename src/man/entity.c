#include "entity.h";

/**
 * Private data members
 */

// Will store all valid entities from first place of the array, without gaps between them
Entity_t _entities[10];
Entity_t* _nextFreeEntity;

/**
 * Private functions
 */

/**
 * Destroys deadEntity and frees its assigned memory
 * 
 * @param deadEntity Pointer to entity to be destroyed
 * 
 * @precondition deadEntity must point to valid entity
 */
void _man_entity_destroy(Entity_t* entity)
{
    // Better work with function local variables
    Entity_t* deadEntity = entity; 
    Entity_t* lastEntity = _nextFreeEntity;

    --lastEntity;
    if (deadEntity != lastEntity) {
        cpct_memcpy(deadEntity, lastEntity, sizeof(Entity_t));
    }
    lastEntity->type = entityTypeInvalid;
    _nextFreeEntity = lastEntity;
}

/**
 * Public functions
 */

void man_entity_init()
{
    cpct_memset(_entities, 0, sizeof(_entities));
    _nextFreeEntity = _entities;
}

Entity_t* man_entity_create()
{
    Entity_t* entity = _nextFreeEntity;
    _nextFreeEntity = entity + 1;
    entity->type = entityTypeDefault;
    return entity;
}

void man_entity_markForDestruction(Entity_t* entity)
{
    entity->type = entity->type | entityTypeDead;
}

// updateFunctionPtr is a pointer to a function with one parameter of type Entity_t pointer
void man_entity_forAll(void (*updateFunctionPtr)(Entity_t*))
{
    Entity_t* entity = _entities;
    while (entity->type != entityTypeInvalid) {
        updateFunctionPtr(entity);
        ++entity;
    }
}

void man_entity_update()
{
    Entity_t* entity = _entities;
    while (entity->type != entityTypeInvalid) {
        if (entity->type & entityTypeDead) {
            _man_entity_destroy(entity);
        } else {
            ++entity;    
        }
    }
}