#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Material.hpp"

class Object {

public:
    Object() {
        material = Material{
            glm::dvec3(0, 0, 0),
            glm::dvec3(0, 0, 0),
            glm::dvec3(0, 0, 0),
            0
        };
    }

    Material getMaterial() { return material; }
    void setMaterial(Material newMaterial) { material = newMaterial; }

    virtual double distanceTo(glm::dvec3 position) = 0;
    virtual glm::dvec3 getSurfaceNormal(glm::dvec3 intersection) = 0;

private:
    Material material;

};

#endif