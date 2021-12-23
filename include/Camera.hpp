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
    ):position(position),up(up),forward(forward),fov(fov){
        right = glm::normalize(glm::cross(up, forward));
    };

    Camera(){
        position = glm::dvec3(0, 0, 0);
        up = glm::dvec3(0, 0, 1);
        forward = glm::dvec3(0, 1, 0);
        right = glm::normalize(glm::cross(up, forward));
        fov = 90;
    };

    void setPosition(glm::dvec3 newPosition) {
        position = newPosition;
    }

    void setUp(glm::dvec3 newUp) {
        up = newUp;
        right = glm::normalize(glm::cross(up, forward));
    }

    void setForward(glm::dvec3 newForward) {
        forward = newForward;
        right = glm::normalize(glm::cross(up, forward));
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