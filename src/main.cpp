#include "Juego.h"
#include <iostream>

int main() {
    Juego juego;
    char entrada;

    // Game Loop Principal
    while (juego.estaCorriendo()) {
        juego.renderizar();
        std::cout << "Ingresa accion: ";
        std::cin >> entrada;
        
        juego.procesarEntrada(entrada);
        juego.actualizar();
    }

    if (juego.gano()) {
        std::cout << "\n===================================" << std::endl;
        std::cout << " ¡VICTORIA! LOGRASTE ESCAPAR " << std::endl;
        std::cout << "===================================\n" << std::endl;
    } else {
        std::cout << "\n===================================" << std::endl;
        std::cout << " GAME OVER - Fin de la partida " << std::endl;
        std::cout << "===================================\n" << std::endl;
    }

    return 0;
}
