#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
#include "Object.hpp"

struct Ray {

    glm::dvec3 position;
    glm::dvec3 direction;
    double time = 0;

    Object* objectHit;

    glm::dvec3 intersectPos() {
        return position + time*direction;
    }

};

#endif