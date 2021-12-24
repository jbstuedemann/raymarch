#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "Ray.hpp"

class Camera {
public:
    enum CAMERA_PROPERTIES {
        NONE,
        POSITION,
        UP,
        FORWARD,
        FOV
    };

    Camera(
        glm::dvec3 position,
        glm::dvec3 up,
        glm::dvec3 forward,
        double fov
    ):
        position(position),
        up(glm::normalize(up)),
        forward(glm::normalize(forward)),
        fov(fov)
        {
        right = glm::normalize(glm::cross(forward, up));
        up = glm::normalize(glm::cross(right, forward));
    };

    Camera(){
        position = glm::dvec3(0, 0, 0);
        up = glm::dvec3(0, 0, 1);
        forward = glm::dvec3(0, 1, 0);
        right = glm::normalize(glm::cross(forward, up));
        fov = 90;
    };

    void setPosition(glm::dvec3 newPosition) {
        position = newPosition;
    }

    void setUp(glm::dvec3 newUp) {
        up = glm::normalize(newUp);
        right = glm::normalize(glm::cross(forward, up));
        forward = glm::normalize(glm::cross(up, right));
    }

    void setForward(glm::dvec3 newForward) {
        forward = glm::normalize(newForward);
        right = glm::normalize(glm::cross(forward, up));
        up = glm::normalize(glm::cross(right, forward));
    }

    void setFov(double newFov) {
        fov = newFov;
    }

    Ray getRayForUV(double u, double v);

private:
    glm::dvec3 position;
    glm::dvec3 up;
    glm::dvec3 forward;
    glm::dvec3 right;
    double fov;
};

#endif