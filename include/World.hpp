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
    void castRay(Ray &ray, Object* ignoreObject);
    glm::dvec3 getShading(Ray ray);

private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Camera* camera;
};

#endif