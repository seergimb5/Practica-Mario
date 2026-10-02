#ifndef GOKU_HH
#define GOKU_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"
#include "enemy.hh"
#include "kamehameha.hh"

class Goku {
private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = { 0, 0 };
    pro2::Pt accel_ = { 0, 0 };
    int      accel_time_ = 0;
    int puntuacion_ = 0;
    int num_boles_drac_ = 0;

    int jump_key_, left_key_, right_key_;

    bool grounded_ = false;
    bool looking_left_ = false;
    bool is_transformed_ = false;

    void apply_physics_();

public:
    Goku(pro2::Pt pos, int jump, int left, int right)
        : pos_(pos), last_pos_(pos), jump_key_(jump), left_key_(left), right_key_(right) {
    }

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    void desplazar_x(int desplazamiento) {
        pos_.x += desplazamiento;
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
     * @brief Incrementa la puntuació del goku amb el valor dels punts
     *
     * @param puntos Copiem els nous punts obtinguts pel goku
     *
     */
    void increment_puntuacion(int puntos) {
        puntuacion_ += puntos;
    }

    /**
     * @return Retorna la puntuació actual del goku
     *
     */
    int get_puntuacion() {
        return puntuacion_;
    }

    /**
     * @brief Calcula el rectangle de hitbox del goku
     *
     */
    pro2::Rect get_rect();

    /**
     * @brief Calcula si el goku mata al enemy
     *
     * Nomes el matara si intersecciona per la part superior
     *
     * @param enemy se li passa un enemy per referencia constant
     */
    bool kill_enemy(const Enemy& enemy);

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    /**
     * @brief Retorna si el goku esta transformat
     */
    bool is_transformed() const;

    /**
     * @brief modifica el atributo que indica si el goku esta transormado o no
     *
     * @param transformed estado al que queremos poner el atributo
     */
    void set_transformed(bool transformed);

    /**
     * @brief le indica al goku que ha capturado una nueva bola de drac
     */
    void nueva_bola();

    /**
     * @brief crea un kamehameha en la posicion del goku y la direccion en la que mira
     */
    Kamehameha createkamehameha();


private:
    static std::vector<std::vector<int>> goku_sprite_;
};

#endif