#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"

class DirectionalLight : public Light {
public:
    enum DIRECTIONALLIGHT_PROPERTIES {
        NONE,
        DIRECTION,
        INTENSITY
    };

    DirectionalLight(): Light(glm::dvec3(0, 0, 0)) {
        direction = glm::dvec3(0, 0, 0);
    }

    DirectionalLight(glm::dvec3 direction, glm::dvec3 intensity):
        direction(glm::normalize(direction)),
        Light(intensity)
    {}

    glm::dvec3 getDirectionTo(glm::dvec3 point) {
        return direction;
    }

    double getDistanceTo(glm::dvec3 point) {
        return DBL_MAX;
    }

    void setDirection(glm::dvec3 newDirection) {
        direction = glm::normalize(newDirection);
    }

private:
    glm::dvec3 direction;

};

#endif