#include "World.hpp"

World::World() {
    objects = std::vector<Sphere*>();
}

void World::addObject(Sphere* object) {
    objects.push_back(object);
}

double World::getShortestDistance(glm::dvec3 position) {
    double smallestDistance = DBL_MAX;
    for (auto object : objects) {
        double thisDistance = object->distanceTo(position);
        if (thisDistance < smallestDistance) {
            smallestDistance = thisDistance;
        }
    }
    return smallestDistance;
}

void World::castRay(Ray &ray) {
    glm::dvec3 currentLocation = ray.position;
    while (true) {
        double stepSize = getShortestDistance(currentLocation);
        if (stepSize < 0.001 || stepSize > 1000000) {
            break;
        }
        else {
            currentLocation += stepSize * ray.direction;
            ray.time += stepSize;
        }
    }
}