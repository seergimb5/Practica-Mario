#ifndef KAMEHAMEHA_HH
#define KAMEHAMEHA_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Kamehameha {
private:
    pro2::Pt pos_, pos_ini_;
    pro2::Pt speed_;
    bool looking_left_;
    const static int longitud_ = 150;
    int direction_;

public:
    Kamehameha()
        : pos_({ 0,0 }), speed_({ 0,0 }) {
    }
    Kamehameha(pro2::Pt pos, pro2::Pt speed, int direction)
        : pos_(pos), speed_(speed), pos_ini_(pos), direction_(direction) {
        if (direction_ < 0) {
            looking_left_ = true;
        }
        else {
            looking_left_ = false;
        }
    }

    void paint(pro2::Window& window) const;

    /**
     * @brief Mira si l'atac encara esta actiu
     *
     */
    bool is_active() const;

    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Calcula el rectangle de hitbox del kamehameha
     *
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Si l'atac esta actiu actualitza la seva posició
     *
     */
    void update(pro2::Window& window);


private:
    static const std::vector<std::vector<int>> kamehameha_sprite_;
};

#endif