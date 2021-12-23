#include <iostream>
#include "Parser.hpp"
#include "World.hpp"
#include "Ray.hpp"

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
    for (int xPixel = 0; xPixel < 1920; xPixel++) {
        for (int yPixel = 0; yPixel < 1080; yPixel++) {
            double u = xPixel/1920.;
            double v = yPixel/1080.;

            Ray ray = world->getCamera()->getRayForUV(u, v);
            world->castRay(ray);
            if (ray.time != 0)
                std::cout << ray.time << std::endl;

            //use this ray to find light and shadows
            //then calculate a color
            //then assign it to an image
        }
    }

    return 0;
}