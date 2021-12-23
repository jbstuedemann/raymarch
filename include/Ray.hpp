#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray {

    glm::dvec3 position;
    glm::dvec3 direction;
    double time = 0;

};

#endif