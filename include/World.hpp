#ifndef WORLD_HPP
#define WORLD_HPP

#include "Sphere.hpp"
#include <vector>

class World {
public:
    World();

private:
    std::vector<Sphere*> Objects;
    Camera* camera;
};

#endif