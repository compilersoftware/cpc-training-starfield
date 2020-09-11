#pragma once
#include <cpctelera.h>

typedef struct te {
    u8 type;
    u8 x, y;
    i8 vx;
    u8 colour;
} Entity_t;

void man_entity_init();
Entity_t* man_entity_create();