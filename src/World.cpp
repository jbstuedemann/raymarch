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

void World::castRay(Ray &ray) {
    return castRay(ray, nullptr);
}

void World::castRay(Ray &ray, Object* ignoreObject) {
    glm::dvec3 currentLocation = ray.position;
    for (int n = 0; n < 1024; n++) {
        double smallestDistance = DBL_MAX;
        Object* closestObject = nullptr;
        for (auto object : objects) {
            if (object == ignoreObject) continue;

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
    glm::dvec3 shading = glm::dvec3(0, 0, 0);
    
    for (Light* light : lights) {
        //Ambient Shading
        glm::dvec3 ambientShading = object->getMaterial().ambient*light->getIntensity();

        //Diffuse Shading
        glm::dvec3 lightDirection = light->getDirectionTo(position);
        glm::dvec3 diffuseShading = glm::max(glm::dot(surfaceNorm, -lightDirection),0.)*(object->getMaterial().diffuse)*light->getIntensity();
        
        //Specular Shading
        glm::dvec3 lightReflect = glm::reflect(lightDirection, surfaceNorm);
        double specularScalar = glm::pow(glm::max(glm::dot(-ray.direction, lightReflect), 0.), object->getMaterial().shinyness);
        glm::dvec3 specularShading = specularScalar*(object->getMaterial().specular)*light->getIntensity();

        //Phong Shading
        glm::dvec3 phongShading = (ambientShading+diffuseShading+specularShading) * (1./lights.size());

        //Shadow Ray
        Ray shadowRay = Ray{position, glm::normalize(-lightDirection)};
        castRay(shadowRay, object);

        //Calculate Shading
        if (!shadowRay.objectHit || shadowRay.time > light->getDistanceTo(position)) {
            shading += phongShading;
        }
    }

    return glm::clamp(shading, glm::dvec3(0, 0, 0), glm::dvec3(1, 1, 1));
}