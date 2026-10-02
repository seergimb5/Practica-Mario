#include "enemy.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;

const vector<vector<int>> enemy_sprite_normal_ = {
    {-1, -1, -1, -1, -1, -1, r, r, r, r, r, r, r, r, r, r, -1, -1, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, -1, -1, r, r, r, r, r, r, r, r, r, r, -1, -1, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, h, h, h, h, h, h, s, s, s, s, h, h, s, s, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, h, h, h, h, h, h, s, s, s, s, h, h, s, s, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, s, s, h, h, s, s, s, s, s, s, h, h, s, s, s, s, s, s, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, s, s, h, h, s, s, s, s, s, s, h, h, s, s, s, s, s, s, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, s, s, h, h, h, h, s, s, s, s, s, s, h, h, s, s, s, s, s, s, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, s, s, h, h, h, h, s, s, s, s, s, s, h, h, s, s, s, s, s, s, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, h, h, s, s, s, s, s, s, s, s, h, h, h, h, h, h, h, h, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, h, h, h, h, s, s, s, s, s, s, s, s, h, h, h, h, h, h, h, h, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, -1, -1, s, s, s, s, s, s, s, s, s, s, s, s, s, s, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, -1, -1, s, s, s, s, s, s, s, s, s, s, s, s, s, s, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, r, r, r, r, b, b, r, r, r, r, r, r, -1, -1, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, r, r, r, r, b, b, r, r, r, r, r, r, -1, -1, -1, -1, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, r, r, r, r, r, r, b, b, r, r, r, r, b, b, r, r, r, r, r, r, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, r, r, r, r, r, r, b, b, r, r, r, r, b, b, r, r, r, r, r, r, -1, -1, _, _, _, _, _, _, _, _},
    {r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, r, r, r, r, r, r, r, r, _, _, _, _, _, _, _, _},
    {r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, r, r, r, r, r, r, r, r, _, _, _, _, _, _, _, _},
    {g, g, g, g, r, r, b, b, y, y, b, b, b, b, y, y, b, b, r, r, g, g, g, g, _, _, _, _, _, _, _, _},
    {g, g, g, g, r, r, b, b, y, y, b, b, b, b, y, y, b, b, r, r, g, g, g, g, _, _, _, _, _, _, _, _},
    {g, g, g, g, g, g, b, b, b, b, b, b, b, b, b, b, b, b, g, g, g, g, g, g, _, _, _, _, _, _, _, _},
    {g, g, g, g, g, g, b, b, b, b, b, b, b, b, b, b, b, b, g, g, g, g, g, g, _, _, _, _, _, _, _, _},
    {g, g, g, g, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, g, g, g, g, _, _, _, _, _, _, _, _},
    {g, g, g, g, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, g, g, g, g, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, b, b, b, b, b, b, -1, -1, -1, -1, b, b, b, b, b, b, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, -1, -1, b, b, b, b, b, b, -1, -1, -1, -1, b, b, b, b, b, b, -1, -1, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, w, w, w, w, w, w, -1, -1, -1, -1, -1, -1, -1, -1, w, w, w, w, w, w, -1, -1, _, _, _, _, _, _, _, _},
    {-1, -1, w, w, w, w, w, w, -1, -1, -1, -1, -1, -1, -1, -1, w, w, w, w, w, w, -1, -1, _, _, _, _, _, _, _, _},
    {w, w, w, w, w, w, w, w, -1, -1, -1, -1, -1, -1, -1, -1, w, w, w, w, w, w, w, w, _, _, _, _, _, _, _, _},
    {w, w, w, w, w, w, w, w, -1, -1, -1, -1, -1, -1, -1, -1, w, w, w, w, w, w, w, w, _, _, _, _, _, _, _, _}
};
const vector<vector<int>> Enemy::enemy_sprite_ = enemy_sprite_normal_;

// clang-format on

void Enemy::paint(pro2::Window& window) const {
    int anchura = enemy_sprite_[0].size();
    int altura = enemy_sprite_.size();
    const pro2::Pt top_left = { pos_.x - anchura / 2, pos_.y - altura + 1 };
    paint_sprite(window, top_left, enemy_sprite_, looking_left_);
}

/**
 * @brief If the enemy is going to fall of the platform, change the direction of the speed to be always grounded
 *
*/
void Enemy::apply_physics_() {
    if (!grounded_ && pos_.x != initial_pos_.x) {
        speed_.x = -speed_.x;
        pos_.x += enemy_sprite_[0].size() * speed_.x;
        last_pos_ = pos_;
    }
    pos_.x += speed_.x;
}


void Enemy::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply speed
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


pro2::Rect Enemy::get_rect() const {
    int altura = enemy_sprite_.size();
    int anchura = enemy_sprite_[0].size();
    return { pos_.x - anchura / 2,pos_.y - altura, pos_.x + anchura / 2,pos_.y };
}

int Enemy::height() const {
    return get_rect().bottom - get_rect().top;
}

pro2::Pt Enemy::speed() const {
    return speed_;
}