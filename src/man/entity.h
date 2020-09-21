#pragma once
#include <cpctelera.h>

/* Constantes */

// Tipos de entidades (en formato mapa de bits)
#define entityTypeInvalid 0x00
#define entityTypeStar 0x01
#define entityTypeDead 0x80
#define entityTypeDefault 0x7F

#define MAX_ENTITIES 45

/* Estructuras de datos */

typedef struct te {
    u8 type;
    u8 x, y;
    u8 speed;
    u8 colour;

    // Atributos dedicados a optimizaciones
    u8* prevPtr; // Puntero a la posición previa en pantalla
} Entity_t;

/* Interfaz pública */

void man_entity_init();
Entity_t* man_entity_create();
void man_entity_markForDestruction(Entity_t* entity);
void man_entity_forAll(void (*fnPtr)(Entity_t*));
void man_entity_update();
u8 man_entity_freeSpace();
