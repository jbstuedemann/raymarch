#include "Parser.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include "Camera.hpp"
#include "Box.hpp"

Parser::Parser(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);

    if (inputFile) {
        std::string line;
        while (getline(inputFile, line)) {
            parseLine(line);
        }
        
        parseFileData();

        inputFile.close();
    }
    else {
        throw FileNotFoundException();
    }
}

void Parser::parseLine(std::string line) {
    std::string line_nowspace;
    for (int i = 0; i < line.size(); i++) {
        if (!std::iswspace(line[i])) {
            line_nowspace.append(1u, line[i]);
        }
    }
    filedata.append(line_nowspace);
}

void Parser::parseFileData() {
    int segmentCount = 0;
    OBJECT lastObject = NONE;
    for (int i = 0; i < filedata.size(); i++) {
        switch (filedata[i]) {
            case '{': {
                std::string identifier = filedata.substr(i-segmentCount, segmentCount);
                if (identifier == "camera") {
                    std::cout << "Found a Camera -> Exctracting data:" << std::endl;
                    lastObject = CAMERA;
                }
                else if (identifier == "box") {
                    std::cout << "Found a Box -> Exctracting data:" << std::endl;
                    lastObject = BOX;
                }
                else {
                    lastObject = NONE;
                }
                segmentCount = 0;
                break;
            }
            case '}': {
                std::string data = filedata.substr(i-segmentCount, segmentCount);
                switch (lastObject) {
                    case CAMERA:
                        //TODO: add to world
                        parseCamera(data);
                        break;
                    case BOX:
                        //TODO: add to world
                        parseBox(data);
                        break;
                }
                lastObject = NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
}

Camera* Parser::parseCamera(std::string data) {
    Camera* outCamera = new Camera();
    int segmentCount = 0;
    Camera::CAMERA_PROPERTIES lastProperty = Camera::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "position") {
                    std::cout << "\tfound position:" << std::endl;
                    lastProperty = Camera::POSITION;
                }
                else if (identifier == "up") {
                    std::cout << "\tfound up:" << std::endl;
                    lastProperty = Camera::UP;
                }
                else if (identifier == "forward") {
                    std::cout << "\tfound forward:" << std::endl;
                    lastProperty = Camera::FORWARD;
                }
                else if (identifier == "fov") {
                    std::cout << "\tfound fov:" << std::endl;
                    lastProperty = Camera::FOV;
                }
                else {
                    lastProperty = Camera::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    //Parse Properties
                    case Camera::POSITION:
                        outCamera->setPosition(parseVector(propertyData));
                        break;
                    case Camera::UP:
                        outCamera->setUp(parseVector(propertyData));
                        break;
                    case Camera::FORWARD:
                        outCamera->setForward(parseVector(propertyData));
                        break;
                    case Camera::FOV:
                        outCamera->setFov(parseDouble(propertyData));
                        break;
                }
                lastProperty = Camera::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outCamera;
}

Box* Parser::parseBox(std::string data) {
    Box* outBox = new Box();
    int segmentCount = 0;
    Box::BOX_PROPERTIES lastProperty = Box::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "bottom_left") {
                    std::cout << "\tfound bottom_left:" << std::endl;
                    lastProperty = Box::BOTTOM_LEFT;
                }
                else if (identifier == "top_right") {
                    std::cout << "\tfound top_right:" << std::endl;
                    lastProperty = Box::TOP_RIGHT;
                }
                else {
                    lastProperty = Box::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    //Parse Properties
                    case Box::BOTTOM_LEFT:
                        outBox->setBottomLeft(parseVector(propertyData));
                        break;
                    case Box::TOP_RIGHT:
                        outBox->setTopRight(parseVector(propertyData));
                        break;
                }
                lastProperty = Box::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outBox;
}

glm::dvec3 Parser::parseVector(std::string data) {
    double vector [3] = {0, 0, 0};
    int vectorIndex = 0;
    int dataCount = 0;
    if (data[0] == '<') {
        for (int i = 1; i < data.size(); i++) {
            if (data[i] == ','|| data[i] == '>') {
                vector[vectorIndex] = parseDouble(data.substr(i-dataCount, dataCount));
                vectorIndex++;
                dataCount = 0;
            }
            else {
                dataCount++;
            }
        }
    }
    return glm::dvec3(vector[0], vector[1], vector[2]);
}