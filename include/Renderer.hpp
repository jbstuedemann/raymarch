#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <vector>
#include "World.hpp"

class Renderer {
public:
    Renderer(int width, int height):
        width(width),
        height(height)
    {
        packed_pixels = std::vector<uint8_t>(width * height * 3);
    };

    void setWorld(World* worldPtr) {
        world = worldPtr;
    }

    std::vector<uint8_t> getRender() {
        return packed_pixels;
    }

    void renderScene();

private:
    int width;
    int height;
    std::vector<uint8_t> packed_pixels;

    World* world;

};

#endif