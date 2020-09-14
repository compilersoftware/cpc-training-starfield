#include "entity.h";

/* Atributos privados */

// Vamos a almacenar todas las entidades válidas a partir de la primera posición
// del array, sin huecos entre ellas
Entity_t _entities[MAX_ENTITIES];
// Usamos este "hack" para añadir siempre una entidad inválida al final de nuestro
// array de entidades
// Sólo funciona si el compilador coloca estas variables en memoria de forma consecutiva
// y ordenadas según el orden de declaración
u8 _zeroByteAtTheEnd;
// Puntero a la siguiente entidad libre
Entity_t* _nextFreeEntity;
// Número de entidades asignadas
u8 _numEntities;

/* Funciones privadas */

/**
 * Destruye la entidad entity y libera la memoria asignada
 * 
 * @param entity Puntero a la entidad que va a ser destruida
 * 
 * @precondition entity debe ser un puntero a una entidad válida
 */
void _man_entity_destroy(Entity_t* entity)
{
    // El compilador genera mejor código si usamos variables locales
    Entity_t* deadEntity = entity; 
    Entity_t* lastEntity = _nextFreeEntity;

    --lastEntity;
    if (deadEntity != lastEntity) {
        cpct_memcpy(deadEntity, lastEntity, sizeof(Entity_t));
    }
    lastEntity->type = entityTypeInvalid;
    _nextFreeEntity = lastEntity;

    --_numEntities;
}

/* Funciones públicas */

void man_entity_init()
{
    cpct_memset(_entities, 0, sizeof(_entities));
    _nextFreeEntity = _entities;
    _numEntities = 0;
    _zeroByteAtTheEnd = entityTypeInvalid;
}

Entity_t* man_entity_create()
{
    Entity_t* entity = _nextFreeEntity;
    _nextFreeEntity = entity + 1;
    entity->type = entityTypeDefault;
    ++_numEntities;
    return entity;
}

/**
 * Marca la entidad entity para ser destruida
 */
void man_entity_markForDestruction(Entity_t* entity)
{
    entity->type = entity->type | entityTypeDead;
}

/**
 * Mediante el patrón "inversión de control", recorre el array de entidades y llama con cada
 * una de ellas a la función updateFunctionPtr
 * 
 * @param updateFunctionPtr es un puntero a una función con un parámetro de tipo puntero a Entity_t
 */
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

u8 man_entity_freeSpace()
{
    return MAX_ENTITIES - _numEntities;
}
