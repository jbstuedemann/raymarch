#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"

int PIXEL_WIDTH = 1920;
int PIXEL_HEIGHT = 1080;

using namespace std;

int main(int argc, char* argv[]) {

    Parser* parser;
    try { 
        parser = new Parser("../tests/Test1.scene", false);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    Renderer* renderer = new Renderer(PIXEL_WIDTH, PIXEL_HEIGHT);
    renderer->setWorld(parser->getWorld());
    renderer->renderScene();

    std::ofstream imageFile;
    imageFile.open("../Test1.ppm");
    imageFile << "P3\n" << PIXEL_WIDTH << '\t' << PIXEL_HEIGHT << '\t' << 255 << '\n';
    for (uint8_t pixel : renderer->getRender()) {
        imageFile << (int)pixel << '\t';
    }
    imageFile.close();

    return 0;
}