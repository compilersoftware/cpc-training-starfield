#include "entity.h";

Entity_t _entities[10];
u8 reservedEntities;

void  man_entity_init() {
    reservedEntities = 0;
}

Entity_t* man_entity_create() {
    Entity_t* e = &_entities[reservedEntities];
    ++reservedEntities;
    return e;
}