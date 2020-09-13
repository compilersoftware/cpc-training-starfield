#pragma once
#include <cpctelera.h>

/**
 * Public constants
 */

#define entityTypeInvalid 0x00
#define entityTypeStar 0x01
#define entityTypeDead 0x80
#define entityTypeDefault 0x7F

#define MAX_ENTITIES 40

/**
 * Public data structures
 */

typedef struct te {
    u8 type;
    u8 x, y;
    i8 vx;
    u8 colour;

    // Attributes for optimizations
    u8* prevPtr; // Pointer to previous screen position
} Entity_t;

/**
 * Public interface
 */

void man_entity_init();
Entity_t* man_entity_create();
/**
 * Marks entity for later destruction
 */
void man_entity_markForDestruction(Entity_t* entity);
void man_entity_forAll(void (*fnPtr)(Entity_t*));
/**
 * Updates entity manager by destroying all marked entities
 */
void man_entity_update();
/**
 * Returns number of free entities available
 */
u8 man_entity_freeSpace();
