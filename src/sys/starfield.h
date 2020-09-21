#pragma once
#include <cpctelera.h>

/* Estructuras de datos */

typedef struct typeOrientation {
    i8 x;
    i8 y;
} Orientation_t;

/* Interfaz pública */

void sys_starfield_init();
void sys_starfield_update();
Orientation_t *sys_starfield_getOrientation();
