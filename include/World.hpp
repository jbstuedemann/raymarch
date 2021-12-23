#ifndef WORLD_HPP
#define WORLD_HPP

#include "Object.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <vector>

class World {
public:
    World();

    void addObject(Object* object);
    void addLight(Light* light);
    void setCamera(Camera* cameraPtr) { camera = cameraPtr; }
    Camera* getCamera() { return camera; }

    void castRay(Ray &ray);
    glm::dvec3 getShading(Object* object, glm::dvec3 position);

private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    // double getShortestDistance(glm::dvec3 position);
    Camera* camera;
};

#endif