#include "game.hh"
#include "utils.hh"
using namespace pro2;

Game::Game(int width, int height)
    : goku_({ width / 2, 150 }, Keys::Space, Keys::Left, Keys::Right),
    platforms_{
        Platform(100, 300, 200, 211),
        Platform(0, 200, 250, 261),
        Platform(250, 400, 150, 161),
    },
    // goku2_({ width / 2 - 30, 150 }, 'W', 'A', 'D'),
    finished_(false),
    paused_(false),
    bolesdedrac_(),
    enemys_(),
    kamehamehas_(),
    frecuenciapaint_(frecuencia_) {
    for (int i = 0; i < 100; i++) {
        const int stride = i * 200;
        Platform* p;
        BolaDeDrac* bdd;
        Enemy* enm;
        if (i % 4 == 0) {
            platforms_.push_back(Platform(stride, 200 + stride, 150, 161));
            bolesdedrac_.push_back(BolaDeDrac({ 180 + stride,140 }, 30));
            enemys_.push_back(Enemy({ 100 + stride,150 }));
        }
        else if (i % 4 == 1) {
            platforms_.push_back(Platform(90 + stride, 300 + stride, 200, 211));
            bolesdedrac_.push_back(BolaDeDrac({ 200 + stride,190 }, 50, false));
            enemys_.push_back(Enemy({ 280 + stride,200 }));
        }
        else if (i % 4 == 2) {
            platforms_.push_back(Platform(150 + stride, 400 + stride, 150, 161));
            bolesdedrac_.push_back(BolaDeDrac({ 300 + stride,140 }, 30));
            enemys_.push_back(Enemy({ 380 + stride,150 }));
        }
        else if (i % 4 == 3) {
            platforms_.push_back(Platform(200 + stride, 500 + stride, 100, 111));
            bolesdedrac_.push_back(BolaDeDrac({ 400 + stride,100 }, 50, false));
            enemys_.push_back(Enemy({ 480 + stride,100 }));
        }

    }

    for (int i = 0; i < platforms_.size(); i++) {
        Platform* p = &platforms_[i];
        finder_platforms_.add(p);
    }
    for (int i = 0; i < bolesdedrac_.size(); i++) {
        BolaDeDrac* bdd = &bolesdedrac_[i];
        finder_bolesdedrac_.add(bdd);
    }
    for (int i = 0; i < enemys_.size(); i++) {
        Enemy* enm = &enemys_[i];
        finder_enemy_.add(enm);
    }
}

void Game::process_keys(pro2::Window& window) {
    // The game finish if we press esc or if goku is under all the platforms
    if (window.is_key_down(Keys::Escape) || goku_.pos().y >= 400) {
        finished_ = true;
        return;
    }
    else if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        return;
    }
    if (window.was_key_pressed('X') && goku_.is_transformed() && kamehamehas_.size() <= 0) {
        Kamehameha atac = goku_.createkamehameha();
        kamehamehas_.push_back(atac);
        Kamehameha* pkame = &(kamehamehas_[kamehamehas_.size() - 1]);
        finder_kamehameha_.add(pkame);
    }
}

void Game::update_objects(pro2::Window& window) {
    goku_.update(window, platforms_);
    // goku2_.update(window, platforms_);
    auto itbdd = bolesdedrac_.begin();
    while (itbdd != bolesdedrac_.end()) {
        itbdd->update();
        // si interseccionen el goku i la bola de drac elimina la bola de drac del vector i suma la puntuacio al goku i la mostra pel terminal
        if (interseccionan(goku_.get_rect(), itbdd->get_rect())) {
            goku_.increment_puntuacion(BolaDeDrac::get_puntuacion());
            goku_.nueva_bola();
            std::cout << goku_.get_puntuacion() << std::endl;
            finder_bolesdedrac_.remove(&(*itbdd));
            itbdd = bolesdedrac_.erase(itbdd);
        }
        else {
            finder_bolesdedrac_.update(&(*itbdd));
            itbdd++;
        }
    }
    auto itkamehameha = kamehamehas_.begin();
    while (itkamehameha != kamehamehas_.end()) {
        itkamehameha->update(window);
        if (!itkamehameha->is_active()) {
            finder_kamehameha_.remove(&(*itkamehameha));
            itkamehameha = kamehamehas_.erase(itkamehameha);
        }
        else {
            finder_kamehameha_.update(&(*itkamehameha));
            itkamehameha++;
        }
    }

    auto itenemy = enemys_.begin();
    while (itenemy != enemys_.end()) {
        itenemy->update(window, platforms_);
        // si interseccionen el goku i el enemy elimina el enemy del vector
        if (goku_.kill_enemy(*itenemy)) {
            finder_enemy_.remove(&(*itenemy));
            itenemy = enemys_.erase(itenemy);
        }
        auto itkame = kamehamehas_.begin();
        bool kamekill = false;
        while (itkame != kamehamehas_.end() && !kamekill) {
            // si interseccionen el kamehameha y el enemy elimina el enemy y el de sus respectivos vectores y finders
            if (interseccionan(itkame->get_rect(), itenemy->get_rect())) {
                kamekill = true;
            }
            else {
                itkame++;
            }
        }
        if (kamekill) {
            finder_enemy_.remove(&(*itenemy));
            itenemy = enemys_.erase(itenemy);
            finder_kamehameha_.remove(&(*itkame));
            itkame = kamehamehas_.erase(itkame);
        }
        else {
            if (interseccionan(goku_.get_rect(), itenemy->get_rect())) {
                if (!goku_.is_transformed()) {
                    goku_.desplazar_x(100 * itenemy->speed().x);
                }
                else {
                    goku_.set_transformed(false);
                }
            }
            finder_enemy_.update(&(*itenemy));
            itenemy++;
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const pro2::Pt pos = goku_.pos();
    const pro2::Pt cam = window.camera_center();

    const int left = cam.x; //- window.width() / 4;
    const int right = cam.x; //+ window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;


    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    }
    else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    }
    else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }
    window.move_camera({ dx, dy });
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!paused_) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    pro2::Rect cam = window.camera_rect();
    const set<const Platform*>& platforms_in_camera = finder_platforms_.query(cam);
    const set<const BolaDeDrac*>& boles_in_camera = finder_bolesdedrac_.query(cam);
    const set<const Enemy*>& enemys_in_camera = finder_enemy_.query(cam);
    const set<const Kamehameha*>& kamehamehas_in_camera = finder_kamehameha_.query(cam);
    for (const Platform* p : platforms_in_camera) {
        p->paint(window);
    }
    for (const BolaDeDrac* bdd : boles_in_camera) {
        bdd->paint(window);
    }
    for (const Enemy* enm : enemys_in_camera) {
        enm->paint(window);
    }
    for (const Kamehameha* kame : kamehamehas_in_camera) {
        kame->paint(window);
    }
    goku_.paint(window);
    //goku2_.paint(window);
    paint_hline(window, cam.left, cam.right, cam.top);
    paint_hline(window, cam.left, cam.right, cam.bottom - 1);
    paint_vline(window, cam.left, cam.top, cam.bottom - 1);
    paint_vline(window, cam.right - 1, cam.top, cam.bottom - 1);

}