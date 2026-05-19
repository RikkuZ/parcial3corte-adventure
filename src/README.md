# Adventure - Dungeon Crawler (Inspirado en Atari 2600)

Proyecto desarrollado para el examen del Tercer Corte. Consiste en un videojuego modular en C++ basado en el clásico juego 'Adventure' de Atari, implementando mapas interconectados, IA de persecución de enemigos y gestión de inventario sin el uso de memoria dinámica en el ciclo principal.

## Estructura del Proyecto
El proyecto sigue un diseño limpio y modular:
* CMakeLists.txt: Archivo de configuración de automatización para CMake.
* include/Juego.h: Definición de las estructuras clave (Jugador, Enemigo, Habitacion) y de la clase principal Juego (alojada en la Stack).
* src/Juego.cpp: Lógica del juego (WASD, colisiones, lógica de IA mediante punteros explícitos).
* src/main.cpp: Ciclo principal del juego (Game Loop).

## Instrucciones de Compilación y Ejecución
Para compilar este proyecto utilizando el CMD de Windows y CMake, ejecute los siguientes comandos en la raíz del proyecto:

```cmd
mkdir build
cd build
cmake ..
cmake --build .

Para ejecutar el juego una vez compilado:
.\AdventureGame.exe

Controles del Juego

W/A/S/D Movimiento del personaje por las habitaciones del mapa

Q para salir del juego

Objetivo: Encontrar la llave (K) en las primeras habitaciones y llevarlas hasta el destino final (D) para abrir la puerta de escape evitando ser atrapado por los enemigos (E y X)
