#include <iostream>
#include "Parser.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    try {
        auto parser = new Parser("../tests/Test1.scene");
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}