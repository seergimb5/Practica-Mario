#include "goku.hh"
#include "utils.hh"
#include "kamehameha.hh"
#include "goku_sprite_transformed_red_final.hh"
using namespace std;
using namespace pro2;

//clang format off
vector<vector<int>> Goku::goku_sprite_ = gokuSpriteNormal;
// clang-format on

void Goku::paint(pro2::Window& window) const {
    int anchura = goku_sprite_[0].size();
    int altura = goku_sprite_.size();
    const Pt top_left = { pos_.x - anchura / 2, pos_.y - altura + 1 };
    paint_sprite(window, top_left, goku_sprite_, looking_left_);
}

void Goku::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Goku::jump() {
    if (grounded_) {
        accel_.y = -8;
        grounded_ = false;
        accel_time_ = 2;
    }
}

void Goku::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0;
    if (window.is_key_down(left_key_)) {
        speed_.x = -4;
    }
    else if (window.is_key_down(right_key_)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    for (const Platform& platform : platforms) {
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
            return;
        }
    }

}


pro2::Rect Goku::get_rect() {
    int altura = goku_sprite_.size();
    int anchura = goku_sprite_[0].size();
    return { pos_.x - anchura / 2,pos_.y - altura, pos_.x + anchura / 2,pos_.y };
}

bool Goku::kill_enemy(const Enemy& enemy) {
    if (interseccionan(get_rect(), enemy.get_rect()) && get_rect().bottom <= enemy.get_rect().top + (3 * enemy.height() / 4)) {
        return true;
    }
    else {
        return false;
    }
}

bool Goku::is_transformed() const {
    return is_transformed_;
}

void Goku::set_transformed(bool transformed) {
    is_transformed_ = transformed;
    if (is_transformed_) {
        goku_sprite_ = gokuSpriteTransformed;
    }
    else {
        goku_sprite_ = gokuSpriteNormal;
    }
}

void Goku::nueva_bola() {
    if (!is_transformed_) {
        num_boles_drac_++;
        if (num_boles_drac_ == 7) {
            set_transformed(true);
            num_boles_drac_ = 0;
        }
    }
}

Kamehameha Goku::createkamehameha() {
    if (is_transformed_) {
        pro2::Pt poskame;
        int anchura = goku_sprite_[0].size();
        int altura = goku_sprite_.size();
        int direction;
        if (looking_left_) {
            poskame.x = pos_.x - anchura / 2;
            direction = -1;
        }
        else {
            poskame.x = pos_.x + anchura / 2;
            direction = 1;
        }
        poskame.y = pos_.y - altura / 3;
        Kamehameha atac(poskame, { 6,0 }, direction);
        return atac;
    }
    else {
        Kamehameha atac;
        return atac;
    }
}