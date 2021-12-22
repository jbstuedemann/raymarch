#ifndef BOX_H
#define BOX_H

#include <glm/glm.hpp>

class Box {
public:
    enum BOX_PROPERTIES {
        NONE,
        BOTTOM_LEFT,
        TOP_RIGHT
    };

    Box(
        glm::dvec3 bottomLeft,
        glm::dvec3 topRight
    ):bottomLeft(bottomLeft),topRight(topRight){};

    Box(){
        bottomLeft = glm::dvec3(0, 0, 0);
        topRight = glm::dvec3(0, 0, 1);
    };

    void setBottomLeft(glm::dvec3 newBottomLeft) {
        bottomLeft = newBottomLeft;
    }

    void setTopRight(glm::dvec3 newTopRight) {
        topRight = newTopRight;
    }

private:
    glm::dvec3 bottomLeft;
    glm::dvec3 topRight;
};

#endif