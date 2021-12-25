#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"

class PointLight : public Light {
public:
    enum POINTLIGHT_PROPERTIES {
        NONE,
        POSITION,
        INTENSITY
    };

    PointLight(): Light(glm::dvec3(0, 0, 0)) {
        position = glm::dvec3(0, 0, 0);
    }

    PointLight(glm::dvec3 position, glm::dvec3 intensity):
        position(position),
        Light(intensity)
    {}

    glm::dvec3 getDirectionTo(glm::dvec3 point) {
        return glm::normalize(point - position);
    }

    double getDistanceTo(glm::dvec3 point) {
        return glm::distance(point, position);
    }

    void setPosition(glm::dvec3 newPosition) {
        position = newPosition;
    }

private:
    glm::dvec3 position;

};

#endif