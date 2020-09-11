#include "entity.h";

Entity_t _entities[10];
Entity_t* _nextFreeEntity;

void man_entity_init() {
    cpct_memset(_entities, 0, sizeof(_entities));
    _nextFreeEntity = _entities;
}

Entity_t* man_entity_create() {
    Entity_t* e = _nextFreeEntity;
    _nextFreeEntity = e + 1;
    return e;
}