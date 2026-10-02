#ifndef FINDER_HH
#define FINDER_HH

#include <vector>
#include <map>
#include <set>
#include <stack>
#include "geometry.hh"
using namespace std;

/**
         * @brief Comprueva si dos rectangulos intersecciona
         *
         * @param r1 rectangulo por referencia
         * @param r2 rectangulo por referencia
         * @return Retorna un bool que indica si hay intersección entre r1 y r2
         */
inline bool intersecciona(const pro2::Rect& r1, const pro2::Rect& r) {
    // miro si está a la izquierda, a la derecha, abajo o arriba, si no está en esos casos hay intersección
    return !(r1.left > r.right || r1.right < r.left || r1.bottom < r.top || r1.top > r.bottom);
}

/**
         * @brief Comprueva si dos rectangulos son iguales
         *
         * @param r1 rectangulo por referencia
         * @param r2 rectangulo por referencia
         * @return Retorna un bool que indica si r1 es igual a r2 o no
         */
inline bool rect_iguals(const pro2::Rect& r1, const pro2::Rect& r2) {
    return r1.left == r2.left && r1.right == r2.right && r1.top == r2.top && r1.bottom == r2.bottom;
}

template <class T>
class FinderTree {
private:
    set <const T* > objects_;
    int level_, child_;
    vector < FinderTree* > children = vector<FinderTree*>(4, nullptr);
    pro2::Rect bounding_box_;

    const static int N_CHILDREN = 4;
    const static int LEFT_ = 0, TOP_ = 0, RIGHT_ = 20000, BOTTOM_ = 20000;
    const static int MAX_LEVELS = 9;

    FinderTree(const pro2::Rect& bounding_box, int level) :
        level_(level),
        bounding_box_(bounding_box) {
    }

    /**
         * @brief Crea los hijos del arbol
         *
         */
    inline void create_children() {
        int xmin = bounding_box_.left;
        int ymin = bounding_box_.top;
        int xmax = bounding_box_.right;
        int ymax = bounding_box_.bottom;
        int xmed = (xmax - xmin) / 2;
        int ymed = (ymax - ymin) / 2;
        children[0] = new FinderTree({ xmin,ymin,xmed,ymed }, level_ + 1);
        children[1] = new FinderTree({ xmed,ymin,xmax,ymed }, level_ + 1);
        children[2] = new FinderTree({ xmin,ymed,xmed,ymax }, level_ + 1);
        children[3] = new FinderTree({ xmed,ymed,xmax,ymax }, level_ + 1);
    }

    /**
         * @brief Calcula el índice del hijo
         *
         * @param r rectangulo constante
         *
         * @return retorna un vector con los indices donde se encuentran los hijos
    */
    inline vector <int> children_index(const pro2::Rect r) const {
        vector<int> v;
        for (int i = 0; i < N_CHILDREN; i++) {
            if (intersecciona(r, children[i]->bounding_box_)) {
                v.push_back(i);
            }
        }
        return v;
    }

    /**
         * @brief Crea una query de forma recursiva
         *
         * @param qrect rectangulo por referencia
         * @param s set por referencia de punteros constantes a tipos T
         */
    void query_rec(const pro2::Rect& qrect, set<const T*>& s) const {
        pro2::Rect r = bounding_box_;
        if (intersecciona(qrect, r)) {
            if (children[0] == nullptr) {
                for (auto it = objects_.begin(); it != objects_.end(); it++) {
                    if (intersecciona((*it)->get_rect(), qrect)) {
                        s.insert(*it);
                    }
                }
            }
            else {
                for (int i = 0; i < N_CHILDREN; i++) {
                    children[i]->query_rec(qrect, s);
                }
            }
        }
    }

    inline void query_iter(const pro2::Rect& qrect, set<const T*>& s) const {
        std::stack<const FinderTree*> stack;
        stack.push(this);

        while (!stack.empty()) {
            const FinderTree* current = stack.top();
            stack.pop();
            pro2::Rect r = current->bounding_box_;
            if (intersecciona(qrect, r)) {
                if (current->children[0] == nullptr) {
                    for (auto it = current->objects_.begin(); it != current->objects_.end(); ++it) {
                        if (intersecciona((*it)->get_rect(), qrect)) {
                            s.insert(*it);
                        }
                    }
                }
                else {
                    for (int i = 0; i < N_CHILDREN; ++i) {
                        if (current->children[i] != nullptr) {
                            stack.push(current->children[i]);
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief elimina los hijos
     *
     */
    void remove_children() {
        while (children[0] != nullptr) {
            for (int i = 0; i < N_CHILDREN; i++) {
                children[i]->remove_children();
                delete children[i];
                children[i] = nullptr;
            }
        }
    }

    inline void add_iter(const T* t1) {
        std::stack < pair< FinderTree*, const T*> > stack;
        stack.push({ this,t1 });

        while (!stack.empty()) {
            const pair< FinderTree*, const T*> p = stack.top();
            FinderTree* current = p.first;
            const T* t = p.second;
            stack.pop();
            if (current->children[0] == nullptr) {
                current->objects_.insert(t);
                if (current->objects_.size() > N_CHILDREN && current->level_ < MAX_LEVELS) {
                    current->create_children();
                    for (auto it = current->objects_.begin(); it != current->objects_.end();) {
                        vector <int> child = current->children_index((*it)->get_rect());
                        if (child.size() != 0) {
                            for (int i = 0; i < child.size(); i++) {
                                stack.push({ current->children[child[i]], *it });
                            }
                            it = current->objects_.erase(it);
                        }
                        else {
                            it++;
                        }
                    }
                }
            }
            else {
                vector<int> indexs = current->children_index(t->get_rect());
                if (indexs.size() != 0) {
                    for (int i = 0; i < indexs.size(); i++) {
                        stack.push({ current->children[indexs[i]],t });
                    }
                }
            }
        }
    }

    /**
         * @brief Añade los objetos al finder
         *
         * @param t puntero constante a un objeto de tipo T
         */
    void add_rec(const T* t) {
        if (children[0] == nullptr) {
            objects_.insert(t);
            if (objects_.size() > N_CHILDREN && level_ < MAX_LEVELS) {
                create_children();
                for (auto it = objects_.begin(); it != objects_.end();) {
                    vector <int> child = children_index((*it)->get_rect());
                    if (child.size() != 0) {
                        for (int i = 0; i < child.size(); i++) {
                            children[child[i]]->add_rec(*it);
                        }
                        it = objects_.erase(it);
                    }
                    else {
                        it++;
                    }
                }
            }
        }
        else {
            vector<int> indexs = children_index(t->get_rect());
            if (indexs.size() != 0) {
                for (int i = 0; i < indexs.size(); i++) {
                    children[indexs[i]]->add_rec(t);
                }
            }
        }

    }

    /**
         * @brief Elimina los objetos
         *
         * @param t puntero constante a un objeto de tipo T
         * @param rect rectangulo por referencia
         */
    void remove_rec(const T* t, const pro2::Rect& rect) {
        pro2::Rect r = bounding_box_;
        if (intersecciona(rect, r)) {
            if (children[0] == nullptr) {
                for (auto it = objects_.begin(); it != objects_.end();it++) {
                    if (*it == t) {
                        objects_.erase(it);
                        return;
                    }
                }
            }
            else {
                vector<int> index = children_index(rect);
                for (int i = 0; i < index.size(); i++) {
                    children[index[i]]->remove_rec(t, rect);
                }
            }
        }
    }

public:
    FinderTree() {
        bounding_box_ = { LEFT_,TOP_,RIGHT_,BOTTOM_ };
        level_ = 0;
    }

    ~FinderTree() {
        remove_children();
    }

    void add(const T* t) {
        add_iter(t);
    }

    void remove(const T* t, const pro2::Rect& rect) {
        remove_rec(t, rect);
    }

    void update(const T* t) {
        remove(t);
        add(t);
    }

    std::set<const T*> query(pro2::Rect qrect) const {
        set<const T*> s;
        query_iter(qrect, s);
        return s;
    }

};

template <class T>
class Finder {
private:
    FinderTree<T> tree_;
    map <const T*, pro2::Rect > m_;
public:
    Finder() {}

    int size() {
        return m_.size();
    }

    void add(const T* t) {
        auto it = m_.find(t);
        if (it == m_.end()) {
            tree_.add(t);
            m_[t] = t->get_rect();
        }
        else {
            if (!rect_iguals(t->get_rect(), it->second)) {
                update(t);
            }
        }
    }

    void remove(const T* t) {
        auto it = m_.find(t);
        if (it != m_.end()) {
            tree_.remove(t, it->second);
            m_.erase(it);
        }
    }

    void update(const T* t) {
        remove(t);
        add(t);
    }

    std::set<const T*> query(pro2::Rect qrect) {
        return tree_.query(qrect);
    }
};

#endif