#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "platform.hh"
#include "window.hh"
#include "utils.hh"
#include "goku.hh"
#include "boladedrac.hh"
#include "finder.hh"
#include "enemy.hh"
#include "kamehameha.hh"

class Game {
    Goku                 goku_; // goku2_;
    std::vector<Enemy> enemys_;
    Finder<Enemy> finder_enemy_;
    std::vector<Platform> platforms_;
    Finder<Platform> finder_platforms_;
    std::vector <BolaDeDrac> bolesdedrac_;
    Finder<BolaDeDrac> finder_bolesdedrac_;
    std::vector <Kamehameha> kamehamehas_;
    Finder<Kamehameha> finder_kamehameha_;
    bool finished_;
    bool paused_;
    int frecuenciapaint_;
    const static int frecuencia_ = 20;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

    bool is_paused() const {
        return paused_;
    }

private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif