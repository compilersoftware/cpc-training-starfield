#pragma once
#include <cpctelera.h>

/**
 * Public constants
 */

#define entityTypeInvalid 0x00
#define entityTypeStar 0x01
#define entityTypeDead 0x80
#define entityTypeDefault 0x7F

/**
 * Public data structures
 */

typedef struct te {
    u8 type;
    u8 x, y;
    i8 vx;
    u8 colour;
} Entity_t;

/**
 * Public interface
 */

void man_entity_init();
Entity_t* man_entity_create();
void man_entity_destroy(Entity_t* entity);
void man_entity_forAll(void (*fnPtr)(Entity_t*));