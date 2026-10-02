#include "movimientos.hh"
#include "geometry.hh"
#include <cmath>
using namespace pro2;
/**
     * @brief Calcula si la x s'ha d'incrementar en 1 o decrementar en 1 en un moviment romboide
     *
     * @param p Passem per referència constant el punt on es trova l'objecte
     * @param radio Fem una copia del radi de moviment del objecte
     *
     * @return Retorna l'increment o decrement de x
     */
int nextx(const Pt& p, int radio) {
    if (p.y > 0 || (p.y == 0 && p.x == radio)) {
        return -1;
    }
    else {
        return 1;
    }
}

/**
     * @brief Calcula si la y s'ha d'incrementar en 1 o decrementar en 1 en un moviment romboide
     *
     * @param p Passem per referència constant el punt on es trova l'objecte
     * @param radio Fem una copia del radi de moviment del objecte
     *
     * @return Retorna l'increment o decrement de y
     */
int nexty(const Pt& p, int radio) {
    if (p.x > 0 || (p.x == 0 && p.y == radio)) {
        return 1;
    }
    else {
        return -1;
    }
}

Pt nextpointromboide(const Pt& p, int radio, const Pt& posi) {
    int x = p.x - posi.x;
    int y = p.y - (posi.y - radio);
    int nuevay, nuevax;
    nuevay = p.y + nexty({ x,y }, radio);
    nuevax = p.x + nextx({ x,y }, radio);
    return { nuevax,nuevay };
}

/**
     * @brief Calcula el següent angle respecte l'angle actual de l'objecte en un moviment circular
     *
     * @param current_angle Fem una copia de l'angle actual de l'objecte
     * @param radio Fem una copia del radi de moviment de l'objecte
     *
     * @return Retorna el nou angle del objecte
     */
double next_angle(int radio, double current_angle) {
    current_angle += (2 * M_PI) / (radio * 8);
    if (current_angle >= 2 * M_PI) {
        current_angle = 0;
    }
    return current_angle;
}

Pt nextpointcircular(const Pt& p, int radio, const Pt& posi, double& current_angle) {
    current_angle = next_angle(radio, current_angle);
    int x = round(cos(current_angle) * radio) + posi.x;
    int y = round(sin(current_angle) * radio) + posi.y;
    // Per a que tingui un moviment més fluid, incrementem l'angle fins que hi hagui un canvi de posició real
    while (p.x == x && p.y == y) {
        current_angle = next_angle(radio, current_angle);
        x = round(cos(current_angle) * radio) + posi.x;
        y = round(sin(current_angle) * radio) + posi.y;
    }
    return { x,y };
}
