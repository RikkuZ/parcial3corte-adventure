#ifndef JUEGO_H
#define JUEGO_H

#pragma once

struct Posicion {
    int x;
    int y;
};

struct Jugador {
    Posicion pos;
    char inventario;
    bool tieneLlave;
};

struct Enemigo {
    Posicion pos;
    bool activo;
};

struct Habitacion {
    char mapa[10][10];
    int norte, sur, este, oeste;
};

class Juego {
private:
    Habitacion habitaciones[6];
    Enemigo enemigos[2];
    Jugador jugador;
    int habitacionActual;
    bool juegoCorriendo;
    bool victoria;

    void inicializarMapa();
    void actualizarEnemigos();
    void verificarColisiones();

public:
    Juego();
    void inicializar();
    void procesarEntrada(char comando);
    void actualizar();
    void renderizar();
    bool estaCorriendo() const { return juegoCorriendo; }
    bool gano() const { return victoria; }
};

#endif
