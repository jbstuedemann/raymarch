#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

class Sphere {
public:
    enum SPHERE_PROPERTIES {
        NONE,
        CENTER,
        RADIUS
    };

    Sphere(
        glm::dvec3 center,
        double radius
    ):center(center),radius(radius){};

    Sphere(){
        center = glm::dvec3(0, 0, 0);
        radius = 1;
    };

    void setCenter(glm::dvec3 newCenter) {
        center = newCenter;
    }

    void setRadius(double newRadius) {
        radius = newRadius;
    }

private:
    glm::dvec3 center;
    double radius;
};

#endif