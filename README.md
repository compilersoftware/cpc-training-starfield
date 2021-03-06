# Starfield - CPCtelera - Amstrad CPC

Este programa de ejemplo está basado en esta serie de vídeos de [Fran Gallego](https://twitter.com/frangallegobr), también conocido como [Profesor Retroman](https://www.youtube.com/channel/UCSdIAKvPxlB3VlFDCBvI46A) en Youtube:

* [GameEngine ECS: Starfield Effect - part 1](https://www.youtube.com/watch?v=ighkMUM9-Ww).
* [GameEngine ECS: Starfield Effect - part 2](https://www.youtube.com/watch?v=MgmCjcVOc44).

Este proyecto se ha desarrollado en macOS, pero se supone que en Linux o Windows funcionará de forma similar.

Para construir el proyecto desde cero, teniendo instalada la [CPCtelera](https://github.com/lronaldo/cpctelera) correctamente, tecleamos `make clean && make`.

Para lanzarlo en el emulador [WinApe](http://winape.net/), tecleamos `cpct_winape -a`.

![Starfield Amstrad CPC](video/starfield-cpc.gif)

## Consideraciones acerca del código

A continuación se citan las más relevantes (bajo nuestro criterio) de lo explicado en los vídeos, más lo que se ha intentado aportar por mi parte.

* El ejemplo es un tutorial de introducción a la [arquitectura ECS](https://en.wikipedia.org/wiki/Entity_component_system) (Entidad - Componente - Sistema). En realidad no necesitaríamos montar esta arquitectura para un caso de uso tan sencillo, pero precisamente la sencillez es la que permite centrarnos en aprender los conceptos que nos serán útiles en otros desarrollos más complejos.

* El ejemplo usa el framework CPCtelera, que se apoya en el [compilador sdcc](http://sdcc.sourceforge.net/) y que genera ejecutables para ordenadores Amstrad CPC. El compilador y el hardware de destino condicionan notablemente el tipo de código que vamos a escribir. Por ejemplo, daremos por hecho que las llamadas a las funciones cumplen las precondiciones, las ejecución de las mismas cumple las postcondiciones y no haremos control de errores de ningún tipo. En caso contrario, simplemente se producirá un comportamiento inesperado.

* Sabiendo que la plataforma objeto es Amstrad CPC, y que vamos a usar el Modo 0 para pintar los gráficos, daremos bastantes cosas por supuestas (por ejemplo, las dimensiones de la pantalla). No queremos hacer un motor gráfico multiplataforma y multi modo de vídeo.

* Es importante estar atentos a la manera que tiene el compilador de generar el código ensamblador. Por ejemplo, en este caso vermos que hemos usado funciones de inicialización en vez de inicializar las variables globales en la declaración.

* Siendo C el lenguaje fuente, se utiliza una nomenclatura para nombrar variables y funciones que quiere asemejarse a cómo lo haríamos en lenguajes orientados a objetos, como C++. Por ejemplo, usamos algo similar a _namespaces_ (separados por guión bajo `_`) o añadimos el prefijo guión bajo `_` a las funciones (métodos) y variables (atributos) privadas. Si bien no tenemos disponible toda la potencia de la orientación a objetos, sí que nos ayuda a estructurar mejor nuestro código. Y portarlo a C++ a partir de esta base no debería ser complicado. 

* La depuración es una tarea muy ardua en principio, hasta que cogemos práctica. Si bien el código está escrito en C, el depurador que nos ofrece el emulador WinApe (o cualquier otro que usemos) nos mostrará las instrucciones en lenguaje ensamblador. Así que tendremos que hacer uso de los ficheros intermedios que se generan durante la compilación para saber dónde se aloja el código y qué instrucciones en ensamblador se corresponden con una línea del fuente en C. También tendremos que inspeccionar la memoria para determinar si el código se comporta como debería o hay errores.

* Tanto la documentación como los comentarios de código están escritos en español. En principio el objetivo es dirigirnos a un público hispanoparlante, ya que en inglés suele haber mucha más documentación en general.

* Hasta la versión 1.0, el código es básicamente el que se explica en los vídeos, adaptando un poco el estilo y los nombres de las variables y funciones. Las siguientes versiones son cosecha propia, y el código no está tan optimizado, ya que el objetivo era implementarlas de manera rápida y que se entienda.

## Versiones

* 1.0. Se implementan las mismas funcionalidades explicadas en los vídeos. Las estrellas se mueven de derecha a izquierda. Todas son del mismo color. En Modo 0 cada byte representa 2 píxeles y sólo iluminamos uno, por tanto,  el movimiento es de un mínimo de 2 píxeles horizontales.

* 1.1. Se usan diferentes colores según la velocidad de la estrella (más oscuro, más lenta).

* 1.2. Se implementa movimiento al píxel.

* 1.3. El movimiento del campo de estrellas cambia aleatoriamente de dirección cada 2 segundos.

## Limitaciones conocidas (posibles mejoras)

* En Modo 0 los píxeles tienen una relación de aspecto de 2:1. Si pintásemos estrellas de 1x2 píxeles, se verían cuadradas (de 2x2 píxeles).

* No se tienen en cuenta las reglas de la perspectiva. Las estrellas se pintan en el orden que se crean. Por tanto, puede darse el caso de que una estrella más lenta (que, en teoría, está por detrás) se pinte por encima de una estrella más rápida (que debería estar por delante).
