#ifndef MOVE_HH
#define MOVE_HH

#include "geometry.hh"
#include <cmath>
using namespace pro2;

/**
     * @brief Calcula el següent punt de l'objecte en un moviment romboide
     *
     * @param p Punt actual de l'objecte
     * @param radio Fem una copia del radi de moviment de l'objecte
     * @param posi Posició inicial de l'objecte per referencia
     *
     * @return Retorna el nou punt del objecte
     */
Pt nextpointromboide(const Pt& p, int radio, const Pt& posi);


/**
     * @brief Calcula el següent punt respecte un moviment circular
     *
     * @param p Punt actual de l'objecte
     * @param radio Fem una copia del radi de moviment de l'objecte
     * @param posi Posició inicial de l'objecte per referencia
     * @param current_angle Angle actual de l'objecte
     *
     *
     * @return Retorna el nou punt del objecte
     */
Pt nextpointcircular(const Pt& p, int radio, const Pt& posi, double& current_angle);

#endif