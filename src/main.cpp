#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"

int PIXEL_WIDTH = 1920;
int PIXEL_HEIGHT = 1080;

using namespace std;

int runTestCase(std::string testCase) {
    Parser* parser;
    try { 
        parser = new Parser((testCase+".scene"), false);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    Renderer* renderer = new Renderer(PIXEL_WIDTH, PIXEL_HEIGHT);
    renderer->setWorld(parser->getWorld());
    renderer->renderScene();

    std::ofstream imageFile;
    imageFile.open(testCase+".ppm");
    imageFile << "P3\n" << PIXEL_WIDTH << '\t' << PIXEL_HEIGHT << '\t' << 255 << '\n';
    for (uint8_t pixel : renderer->getRender()) {
        imageFile << (int)pixel << '\t';
    }
    imageFile.close();

    system(("pnmtopng "+testCase+".ppm > "+testCase+".png && rm "+testCase+".ppm").data());

    return 0;
}

int main(int argc, char* argv[]) {
    vector<std::string> testCases {"../tests/Test1", "../tests/Test2", "../tests/Test3"};

    for (std::string test : testCases) {
        std::cout << "Running case: " << test << std::endl;
        if (runTestCase(test) != 0) return -1;
    }

    return 0;
}