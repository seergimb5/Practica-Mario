#ifndef GEOMETRY_HH
#define GEOMETRY_HH

namespace pro2 {

    struct Pt {
        int x = 0, y = 0;
    };

    /**
     * @brief Compara dos punts del pla
     *
     * La comparació és necessària per poder fer servir `Pt` com la clau d'un `map`.
     * La comparació utilitza primer la coordenada `x` (com si fos més "important"),
     * i, quan les `x`s són iguals, la coordenada `y`.
     */
    inline bool operator<(const Pt& a, const Pt& b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }

    struct Rect {
        int left, top, right, bottom;
    };

    /**
     * @brief Comprueva si dos rectangulos interseccionan
     *
     * @param r1 rectangulo por referencia
     * @param r2 rectangulo por referencia
     * @return Retorna un bool que indica si hay intersección entre r1 y r2
     */
    inline bool interseccionan(const Rect& r1, const Rect& r2) {
        // miro si está a la izquierda, a la derecha, abajo o arriba, si no está en esos casos hay intersección
        return !(r1.left >= r2.right || r1.right <= r2.left || r1.bottom <= r2.top || r1.top >= r2.bottom);
    }
}

#endif