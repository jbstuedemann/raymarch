#include "World.hpp"
#include "Sphere.hpp"

World::World() {
    objects = std::vector<Object*>();
}

void World::addObject(Object* object) {
    objects.push_back(object);
}

void World::addLight(Light* light) {
    lights.push_back(light);
}

// double World::getShortestDistance(glm::dvec3 position) {
//     double smallestDistance = DBL_MAX;
//     for (auto object : objects) {
//         double thisDistance = object->distanceTo(position);
//         if (thisDistance < smallestDistance) {
//             smallestDistance = thisDistance;
//         }
//     }
//     return smallestDistance;
// }

void World::castRay(Ray &ray) {
    glm::dvec3 currentLocation = ray.position;
    while (true) {
        // double smallestDistance = getShortestDistance(currentLocation);
        double smallestDistance = DBL_MAX;
        Object* closestObject = nullptr;
        for (auto object : objects) {
            double thisDistance = object->distanceTo(currentLocation);
            if (thisDistance < smallestDistance) {
                smallestDistance = thisDistance;
                closestObject = object;
            }
        }

        if (smallestDistance < 0.001) {
            ray.objectHit = closestObject;
            break;
        }
        else if (smallestDistance > 1000000) {
            ray.objectHit = nullptr;
            ray.time = 0;
            break;
        }
        else {
            currentLocation += smallestDistance * ray.direction;
            ray.time += smallestDistance;
        }
    }
}

glm::dvec3 World::getShading(Object* object, glm::dvec3 position) {
    glm::dvec3 surfaceNorm = object->getSurfaceNormal(position);
    glm::dvec3 totalShading = glm::dvec3(0, 0, 0);
    for (Light* light : lights) {
        glm::dvec3 lightDirection = light->getDirectionTo(position);
        totalShading = 
            totalShading*(1./2) + 
            ((glm::dot(surfaceNorm, -lightDirection))*(light->getIntensity() * object->getMaterial().diffuse))*(1./2);
    }
    return glm::clamp(totalShading, glm::dvec3(0, 0, 0), glm::dvec3(1, 1, 1));
}