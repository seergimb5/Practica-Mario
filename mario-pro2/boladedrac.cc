#include "boladedrac.hh"
#include "utils.hh"
#include "movimientos.hh"
#include <cmath>
using namespace std;
#include "dragon_ball_final_sprite.hh"

// clang-format off
const vector<vector<int>> BolaDeDrac::boladedrac_sprite_ = dragonBall4Stars;

void BolaDeDrac::paint(pro2::Window& window) const {
    int anchura = boladedrac_sprite_[0].size();
    int altura = boladedrac_sprite_.size();
    const pro2::Pt top_left = { pos_.x - anchura / 2, pos_.y - altura + 1 };
    paint_sprite(window, top_left, boladedrac_sprite_, false);
}


/**
     * @brief Modifica la posició del objecte per a que es mogui en forma de rombo
     *
     */
void BolaDeDrac::rombomovement() {
    pos_ = nextpointromboide(pos_, radio_, posini_);
}


/**
     * @brief Modifica la posició del objecte per a que es mogui de forma circular
     *
     */
void BolaDeDrac::circularmovement() {
    pos_ = nextpointcircular(pos_, radio_, posini_, current_angle_);
}

/**
     * @brief Realitza el moviment de les boles de drac segons el valor de l'atribut rombomovement_
     *
     */
void BolaDeDrac::update() {
    if (rombomovement_) {
        rombomovement();
    }
    else {
        circularmovement();
    }
}

/**
     * @brief calcula el rectangle de hitbox de la bola de drac
     *
     */
pro2::Rect BolaDeDrac::get_rect() const {
    int altura = boladedrac_sprite_.size();
    int anchura = boladedrac_sprite_[0].size();
    // calcula el costat esquerra, el top, el dret i el bottom respectivament
    return { pos_.x - anchura / 2,pos_.y - altura, pos_.x + anchura / 2,pos_.y };
}
