#include "entity.h";

/**
 * Private data members
 */

// Will store all valid entities from first place of the array, without gaps between them
Entity_t _entities[10];
Entity_t* _nextFreeEntity;

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

void man_entity_destroy(Entity_t* entity)
{
    entity->type = entityTypeInvalid;
}

// fnPtr is a pointer to a function with one parameter of type Entity_t pointer
void man_entity_forAll(void (*updateFunctionPtr)(Entity_t*))
{
    Entity_t* entity = _entities;
    while (entity->type != entityTypeInvalid) {
        updateFunctionPtr(entity);
        ++entity;
    }
}