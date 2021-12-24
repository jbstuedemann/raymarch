#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include "Object.hpp"

class Sphere : public Object {
public:
    enum SPHERE_PROPERTIES {
        NONE,
        CENTER,
        RADIUS,
        MATERIAL
    };

    Sphere(glm::dvec3 center, double radius):
        Object(),
        center(center),
        radius(radius)
    {};

    Sphere():Object(){
        center = glm::dvec3(0, 0, 0);
        radius = 1;
    };

    void setCenter(glm::dvec3 newCenter) {
        center = newCenter;
    }

    void setRadius(double newRadius) {
        radius = newRadius;
    }

    double distanceTo(glm::dvec3 position) {
        return glm::distance(position, center) - radius;
    }

    glm::dvec3 getSurfaceNormal(glm::dvec3 intersection) {
        return glm::normalize(intersection - center);
    }

private:
    glm::dvec3 center;
    double radius;
};

#endif