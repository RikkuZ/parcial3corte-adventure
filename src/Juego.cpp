#include "Juego.h"
#include <iostream>

Juego::Juego() {
    inicializar();
}

void Juego::inicializar() {
    jugador.pos = {4, 4};
    jugador.inventario = ' ';
    jugador.tieneLlave = false;
    habitacionActual = 0;
    juegoCorriendo = true;
    victoria = false;

    enemigos[0] = {{2, 2}, true};
    enemigos[1] = {{7, 7}, true};

    inicializarMapa();
}

void Juego::inicializarMapa() {
    for (int i = 0; i < 6; ++i) {
        for (int r = 0; r < 10; ++r) {
            for (int c = 0; c < 10; ++c) {
                if (r == 0 || r == 9 || c == 0 || c == 9) {
                    habitaciones[i].mapa[r][c] = '#';
                } else {
                    habitaciones[i].mapa[r][c] = ' ';
                }
            }
        }
        habitaciones[i].norte = -1;
        habitaciones[i].sur = -1;
        habitaciones[i].este = -1;
        habitaciones[i].oeste = -1;
    }

    // Configuración de las 6 habitaciones interconectadas
    habitaciones[0].este = 1;
    habitaciones[0].mapa[4][9] = ' '; 
    habitaciones[0].mapa[3][3] = 'K'; // Aquí está la Llave 'K'

    habitaciones[1].oeste = 0;
    habitaciones[1].este = 2;
    habitaciones[1].mapa[4][0] = ' ';
    habitaciones[1].mapa[4][9] = ' ';

    habitaciones[2].oeste = 1;
    habitaciones[2].sur = 3;
    habitaciones[2].mapa[4][0] = ' ';
    habitaciones[2].mapa[9][4] = ' ';

    habitaciones[3].norte = 2;
    habitaciones[3].este = 4;
    habitaciones[3].mapa[0][4] = ' ';
    habitaciones[3].mapa[4][9] = ' ';

    habitaciones[4].oeste = 3;
    habitaciones[4].norte = 5;
    habitaciones[4].mapa[4][0] = ' ';
    habitaciones[4].mapa[0][4] = ' ';

    habitaciones[5].sur = 4;
    habitaciones[5].mapa[9][4] = ' ';
    habitaciones[5].mapa[4][5] = 'D'; // Aquí está el Destino final 'D'
}

void Juego::procesarEntrada(char comando) {
    int proxX = jugador.pos.x;
    int proxY = jugador.pos.y;

    if (comando == 'w' || comando == 'W') proxY--;
    if (comando == 's' || comando == 'S') proxY++;
    if (comando == 'a' || comando == 'A') proxX--;
    if (comando == 'd' || comando == 'D') proxX++;
    if (comando == 'q' || comando == 'Q') juegoCorriendo = false;

    // Cambios de habitación al cruzar los bordes abiertos
    if (proxY < 0 && habitaciones[habitacionActual].norte != -1) {
        habitacionActual = habitaciones[habitacionActual].norte;
        jugador.pos.y = 8;
        return;
    }
    if (proxY > 9 && habitaciones[habitacionActual].sur != -1) {
        habitacionActual = habitaciones[habitacionActual].sur;
        jugador.pos.y = 1;
        return;
    }
    if (proxX < 0 && habitaciones[habitacionActual].oeste != -1) {
        habitacionActual = habitaciones[habitacionActual].oeste;
        jugador.pos.x = 8;
        return;
    }
    if (proxX > 9 && habitaciones[habitacionActual].este != -1) {
        habitacionActual = habitaciones[habitacionActual].este;
        jugador.pos.x = 1;
        return;
    }

    // Colisión con paredes fijas '#'
    if (habitaciones[habitacionActual].mapa[proxY][proxX] != '#') {
        jugador.pos.x = proxX;
        jugador.pos.y = proxY;
    }
}

void Juego::actualizarEnemigos() {
    for (int i = 0; i < 2; ++i) {
        if (!enemigos[i].activo) continue;

        // PUNTEROS: Uso explícito para modificar las coordenadas del enemigo en memoria
        Enemigo* e = &enemigos[i];

        if (e->pos.x < jugador.pos.x) e->pos.x++;
        else if (e->pos.x > jugador.pos.x) e->pos.x--;

        if (e->pos.y < jugador.pos.y) e->pos.y++;
        else if (e->pos.y > jugador.pos.y) e->pos.y--;
    }
}

void Juego::verificarColisiones() {
    Habitacion* hab = &habitaciones[habitacionActual];

    // Agarrar la llave
    if (hab->mapa[jugador.pos.y][jugador.pos.x] == 'K') {
        jugador.tieneLlave = true;
        jugador.inventario = 'K';
        hab->mapa[jugador.pos.y][jugador.pos.x] = ' ';
    }

    // Llegar al destino final
    if (hab->mapa[jugador.pos.y][jugador.pos.x] == 'D') {
        if (jugador.tieneLlave) {
            victoria = true;
            juegoCorriendo = false;
        } else {
            std::cout << "\n[Sistema] Necesitas la llave 'K' para abrir esta puerta.\n";
        }
    }

    // Colisión con enemigos
    for (int i = 0; i < 2; ++i) {
        if (enemigos[i].activo && enemigos[i].pos.x == jugador.pos.x && enemigos[i].pos.y == jugador.pos.y) {
            juegoCorriendo = false;
        }
    }
}

void Juego::actualizar() {
    actualizarEnemigos();
    verificarColisiones();
}

void Juego::renderizar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "=== ADVENTURE (ATARI 2600 INSPIRED) ===" << std::endl;
    std::cout << "Habitacion actual: " << habitacionActual + 1 << " / 6" << std::endl;
    std::cout << "Inventario: [" << jugador.inventario << "]" << std::endl;
    std::cout << "Controles: WASD + Enter | Q para salir\n" << std::endl;

    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            if (jugador.pos.x == c && jugador.pos.y == r) {
                std::cout << 'P'; // Jugador
            } else {
                bool enemigoImpreso = false;
                for (int i = 0; i < 2; ++i) {
                    if (enemigos[i].activo && enemigos[i].pos.x == c && enemigos[i].pos.y == r) {
                        std::cout << (i == 0 ? 'E' : 'X'); // Enemigos
                        enemigoImpreso = true;
                        break;
                    }
                }
                if (!enemigoImpreso) {
                    std::cout << habitaciones[habitacionActual].mapa[r][c];
                }
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}
