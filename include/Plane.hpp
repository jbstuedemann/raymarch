#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

class Plane : public Object {
public:
    enum PLANE_PROPERTIES {
        NONE,
        Q,
        N,
        MATERIAL
    };

    Plane(glm::dvec3 q, glm::dvec3 n):
        Object(),
        q(q),
        n(glm::normalize(n))
    {};

    Plane():Object(){
        q = glm::dvec3(0, 0, 0);
        n = glm::dvec3(0, 0, 1);
    }

    void setQ(glm::dvec3 newQ) {
        q = newQ;
    }

    void setN(glm::dvec3 newN) {
        n = glm::normalize(newN);
    }

    double distanceTo(glm::dvec3 position) {
        return glm::abs(glm::dot(n, q-position));
    }

    glm::dvec3 getSurfaceNormal(glm::dvec3 intersection) {
        return n;
    }

private:
    glm::dvec3 q;
    glm::dvec3 n;
};

#endif