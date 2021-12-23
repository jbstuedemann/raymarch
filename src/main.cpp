#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "World.hpp"
#include "Ray.hpp"

#include "DirectionalLight.hpp"

const int PIXEL_WIDTH = 1920;
const int PIXEL_HEIGHT = 1080;

using namespace std;

int main(int argc, char* argv[]) {

    Parser* parser;

    try {
        parser = new Parser("../tests/Test1.scene");
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }


    World* world = parser->getWorld();
    world->addLight(new DirectionalLight(glm::dvec3(0, 1, -1), glm::dvec3(1, 0, 1)));
    uint8_t packed_pixels [PIXEL_WIDTH * PIXEL_HEIGHT * 3];

    for (int xPixel = 0; xPixel < PIXEL_WIDTH; xPixel++) {
        for (int yPixel = 0; yPixel < PIXEL_HEIGHT; yPixel++) {
            //Get U,V coords
            double u = xPixel/(float)PIXEL_WIDTH;
            double v = yPixel/(float)PIXEL_HEIGHT;

            //Cast Ray, and get shading
            Ray ray = world->getCamera()->getRayForUV(u, v);
            world->castRay(ray);
            glm::dvec3 color = glm::dvec3(0, 0, 0);
            if (ray.objectHit) {
                glm::dvec3 intersectPos = ray.intersectPos();
                color = world->getShading(ray.objectHit, intersectPos);
            }

            //int pixelIndex = xPixel*PIXEL_HEIGHT + yPixel;
            int pixelIndex = ((PIXEL_HEIGHT-yPixel-1)*PIXEL_WIDTH + xPixel)*3;
            packed_pixels[pixelIndex] = (uint8_t)(color.x * 255);
            packed_pixels[pixelIndex+1] = (uint8_t)(color.y * 255);
            packed_pixels[pixelIndex+2] = (uint8_t)(color.z * 255);

            //use this ray to find light and shadows
            //then calculate a color
            //then assign it to an image
        }
    }

    std::ofstream imageFile;
    imageFile.open("../Test1.ppm");
    imageFile << "P3\n" << PIXEL_WIDTH << '\t' << PIXEL_HEIGHT << '\t' << 255 << '\n';
    for (int i = 0; i < PIXEL_WIDTH * PIXEL_HEIGHT * 3; i++) {
        imageFile << (int)packed_pixels[i] << '\t';
    }
    imageFile.close();

    return 0;
}