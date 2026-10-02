#ifndef ENEMY_HH
#define ENEMY_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Enemy {
private:
    pro2::Pt pos_, last_pos_, initial_pos_;
    pro2::Pt speed_;
    pro2::Pt accel_ = { 0, 0 };
    bool grounded_ = false;
    bool looking_left_ = false;
    int max_y_; // valor maximo hasta el que el enemigo puede caer
    void apply_physics_();

public:

    Enemy() :pos_({ 0,0 }), last_pos_({ 0,0 }), speed_({ 0,0 }), initial_pos_({ 0,0 }), max_y_(0) {}

    Enemy(pro2::Pt pos, pro2::Pt speed = { -1,0 }, int max_y = 251)
        : pos_(pos), speed_(speed), initial_pos_(pos), max_y_(max_y) {
    }

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }


    /**
     * @brief Calcula el rectangle de hitbox del enemy
     *
     */
    pro2::Rect get_rect()const;

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    /**
     * @brief Calcula l'altura del enemy
     *
     */
    int height()const;

    /**
     * @brief retorna la velocitat del enemy
     *
     */
    pro2::Pt speed() const;


private:
    static const std::vector<std::vector<int>> enemy_sprite_;
    static const std::vector<std::vector<int>> goku_sprite_normal_;
};

#endif