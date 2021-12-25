#include "Renderer.hpp"

void Renderer::renderScene() {
    for (int xPixel = 0; xPixel < width; xPixel++) {
        for (int yPixel = 0; yPixel < height; yPixel++) {
            //Get U,V coords
            double u = xPixel/(float)width;
            double v = yPixel/(float)height;

            //Cast Ray, and get shading
            Ray ray = world->getCamera()->getRayForUV(u, v);
            world->castRay(ray);
            glm::dvec3 color = glm::dvec3(0, 0, 0);
            if (ray.objectHit) {
                color = world->getShading(ray);
            }

            //Add pixel to array
            int pixelIndex = ((yPixel)*width + xPixel)*3;
            packed_pixels[pixelIndex] = (uint8_t)(color.x * 255);
            packed_pixels[pixelIndex+1] = (uint8_t)(color.y * 255);
            packed_pixels[pixelIndex+2] = (uint8_t)(color.z * 255);
        }
    }
}