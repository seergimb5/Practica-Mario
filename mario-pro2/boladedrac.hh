#ifndef BOLADEDRAC_HH
#define BOLADEDRAC_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"



class BolaDeDrac {
private:
    pro2::Pt pos_, posini_;
    pro2::Pt speed_ = { 0, 0 };

    int radio_; // radi del moviment
    bool rombomovement_; // si es cert es mou en rombo, sino es mou circularment
    double current_angle_ = 0; // últim angle en el que esta l'objecte respecte l'angle 0

    static const std::vector<std::vector<int>> boladedrac_sprite_;
    static const int puntuacionxamp_ = 1; // defineix la puntuacio dels xampinyons
    void rombomovement();
    void circularmovement();

public:
    BolaDeDrac()
        : pos_({ 0,0 }), posini_({ 0,0 }), radio_(0), rombomovement_(false) {
    }
    /**
     * @brief Constructor de la bola de drac
     *
     * @param pos la posició on volem insertar la bola de drac
     * @param radio el radi de moviment de la bola de drac
     * @param rombomovement bool que determina si es mou en rombo(true) o en circular(false), per defecte true
     *
     */
    BolaDeDrac(pro2::Pt pos, int radio, bool rombomovement = true)
        : pos_(pos), posini_(pos), radio_(radio), rombomovement_(rombomovement) {
    }

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }


    void set_y(int y) {
        pos_.y = y;
    }
    /**
     * @brief Retorna la puntuació de la bola de drac (pensat per a que la puntuació no sigui obligatoriament 1)
     *
     */
    static int get_puntuacion() {
        return puntuacionxamp_;
    }

    /**
     * @brief Calcula el rectangle de hitbox de la bola de drac
     *
     */
    pro2::Rect get_rect() const;


    void update();

};

#endif