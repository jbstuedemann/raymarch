#ifndef WORLD_HPP
#define WORLD_HPP

#include "Sphere.hpp"
#include "Camera.hpp"
#include <vector>

class World {
public:
    World();

    void addObject(Sphere* object);
    void setCamera(Camera* cameraPtr) { camera = cameraPtr; }
    Camera* getCamera() { return camera; }

    void castRay(Ray &ray);

private:
    std::vector<Sphere*> objects;
    double getShortestDistance(glm::dvec3 position);
    Camera* camera;
};

#endif