#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"

class DirectionalLight : public Light {

public:
    DirectionalLight(glm::dvec3 direction, glm::dvec3 intensity):
        direction(glm::normalize(direction)),
        Light(intensity)
    {}

    glm::dvec3 getDirectionTo(glm::dvec3 point) {
        return direction;
    }

private:
    glm::dvec3 direction;

};

#endif