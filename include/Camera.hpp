#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

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
    ):position(position),up(up),forward(forward),fov(fov){};

    Camera(){
        position = glm::dvec3(0, 0, 0);
        up = glm::dvec3(0, 0, 1);
        forward = glm::dvec3(0, 1, 0);
        fov = 90;
    };

    void setPosition(glm::dvec3 newPosition) {
        position = newPosition;
    }

    void setUp(glm::dvec3 newUp) {
        up = newUp;
    }

    void setForward(glm::dvec3 newForward) {
        forward = newForward;
    }

    void setFov(double newFov) {
        fov = newFov;
    }

private:
    glm::dvec3 position;
    glm::dvec3 up;
    glm::dvec3 forward;
    double fov;
};

#endif