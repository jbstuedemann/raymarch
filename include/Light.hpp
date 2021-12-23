#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class Light {

public:
    Light(glm::dvec3 intensity):intensity(intensity){}

    virtual glm::dvec3 getDirectionTo(glm::dvec3 point) = 0;
    glm::dvec3 getIntensity() { return intensity; }

private:
    glm::dvec3 intensity;

};

#endif