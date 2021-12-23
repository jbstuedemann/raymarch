#include "Camera.hpp"

Ray Camera::getRayForUV(double u, double v) {
    double xFactor = ((u*2)-1);
    double xMax = glm::tan(glm::radians(fov) * 1./2.);
    double yFactor = ((v*2)-1);
    double yMax = glm::tan(glm::radians(fov) * 9./32.);

    glm::dvec3 direction = forward + (xFactor*xMax*right) + (yFactor*yMax*up);

    return Ray{position, direction, 0};
}