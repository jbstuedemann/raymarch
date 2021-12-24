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
    for (int n = 0; n < 1024; n++) {
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

glm::dvec3 World::getShading(Ray ray) {
    Object* object = ray.objectHit;
    glm::dvec3 position = ray.intersectPos();
    glm::dvec3 surfaceNorm = object->getSurfaceNormal(position);

    //Ambient Shading
    glm::dvec3 ambientShading = glm::dvec3(0, 0, 0);
    for (Light* light : lights) {
        ambientShading += object->getMaterial().ambient*light->getIntensity();
    }
    ambientShading *= (1./lights.size());

    //Diffuse Shading
    glm::dvec3 diffuseShading = glm::dvec3(0, 0, 0);
    for (Light* light : lights) {
        glm::dvec3 lightDirection = light->getDirectionTo(position);
        diffuseShading += glm::max(glm::dot(surfaceNorm, -lightDirection),0.)*(object->getMaterial().diffuse)*light->getIntensity();
    }
    diffuseShading *= (1./lights.size());

    //Specular Shading
    glm::dvec3 specularShading = glm::dvec3(0, 0, 0);
    for (Light* light : lights) {
        glm::dvec3 lightDirection = light->getDirectionTo(position);
        glm::dvec3 lightReflect = glm::reflect(lightDirection, surfaceNorm);
        double specularScalar = glm::pow(glm::max(glm::dot(-ray.direction, lightReflect), 0.), object->getMaterial().shinyness);
        specularShading += specularScalar*(object->getMaterial().specular)*light->getIntensity();
    }
    specularShading *= (1./lights.size());

    return glm::clamp((ambientShading+diffuseShading+specularShading)*(1./3.), glm::dvec3(0, 0, 0), glm::dvec3(1, 1, 1));
    // return glm::clamp((specularShading), glm::dvec3(0, 0, 0), glm::dvec3(1, 1, 1));
}