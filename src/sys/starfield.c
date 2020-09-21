#include "starfield.h"

/* Constantes privadas */

#define MAX_FRAMES 50
#define MAX_SECONDS_BEFORE_CHANGE 2

/* Atributos privados */

Orientation_t _orientation;

u8 _framesCounter;
u8 _secondsCounter;

/* Funciones privadas */

void _sys_starfield_changeOrientation()
{
    u8 orientation = cpct_rand() & 0x03;
    switch (orientation) {
        case 0:
            _orientation.x = -1;
            _orientation.y = 0;
            break;
        case 1:
            _orientation.x = 1;
            _orientation.y = 0;
            break;
        case 2:
            _orientation.x = 0;
            _orientation.y = -1;
            break;
        case 3:
            _orientation.x = 0;
            _orientation.y = 1;
            break;
    }
}

/* Funciones públicas */

void sys_starfield_init()
{
    _orientation.x = -1;
    _orientation.y = 0;
    _framesCounter = 0;
    _secondsCounter = 0;
}

void sys_starfield_update()
{
    ++_framesCounter;
    if (_framesCounter == MAX_FRAMES) {
        ++_secondsCounter;
        if (_secondsCounter == MAX_SECONDS_BEFORE_CHANGE) {
            _sys_starfield_changeOrientation();
            _secondsCounter = 0;
        }
        _framesCounter = 0;
    }
}

Orientation_t *sys_starfield_getOrientation()
{
    // @TODO ¿deberíamos devolver una copia para que no se pueda modificar desde fuera?
    return &_orientation;
}
