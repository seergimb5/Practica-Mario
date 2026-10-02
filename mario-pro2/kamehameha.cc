#include <iostream>
#include <vector>
#include "utils.hh"
#include "kamehameha.hh"
using namespace pro2;
using namespace std;

const int _ = -1;
const int b = 0x00BFFFEE;

// clang-format off
const vector<vector<int>> Kamehameha::kamehameha_sprite_ = {
    {_, _, _, _, b, b, b, b, b, _, _, _},
    {_, _, _, b, b, b, b, b, b, b, _, _},
    {_, _, b, b, b, b, b, b, b, b, b, _},
    {_, _, b, b, b, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, b, b, b, b},
    {b, b, b, b, b, b, b, b, b, b, b, b},
    {b, b, b, b, b, b, b, b, b, b, b, b},
    {b, b, b, b, b, b, b, b, b, b, b, b},
    {b, b, b, b, b, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, b, b, b, b},
    {_, _, b, b, b, b, b, b, b, b, b, b},
    {_, _, b, b, b, b, b, b, b, b, b, _},
    {_, _, _, b, b, b, b, b, b, b, _, _},
    {_, _, _, _, b, b, b, b, b, _, _, _},

};

bool Kamehameha::is_active() const {
    return abs(pos_.x - pos_ini_.x) <= longitud_;
}

void Kamehameha::paint(pro2::Window& window) const {
    if (is_active()) {
        int anchura = kamehameha_sprite_[0].size();
        int altura = kamehameha_sprite_.size();
        const pro2::Pt top_left = { pos_.x - anchura / 2, pos_.y - altura + 1 };
        paint_sprite(window, top_left, kamehameha_sprite_, looking_left_);
    }
}

/**
 * @brief Calcula el rectangle de hitbox del kamehameha
 *
 */
pro2::Rect Kamehameha::get_rect() const {
    int altura = kamehameha_sprite_.size();
    int anchura = kamehameha_sprite_[0].size();
    return { pos_.x - anchura / 2,pos_.y - altura, pos_.x + anchura / 2,pos_.y };
}

void Kamehameha::update(pro2::Window& window) {
    if (is_active()) {
        pos_.x += direction_ * speed_.x;
    }
}


