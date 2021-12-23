#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"

class PointLight : public Light {

public:
    PointLight(glm::dvec3 position, glm::dvec3 intensity):
        position(position),
        Light(intensity)
    {}

    glm::dvec3 getDirectionTo(glm::dvec3 point) {
        return glm::normalize(point - position);
    }

private:
    glm::dvec3 position;

};

#endif