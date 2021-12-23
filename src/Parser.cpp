#include "Parser.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include "Camera.hpp"
#include "Sphere.hpp"

Parser::Parser(std::string filename) {
    std::ifstream inputFile;
    inputFile.open(filename);

    if (inputFile) {

        std::cout << "Loading World..." << std::endl << std::endl;
        world = new World();

        std::string line;
        while (getline(inputFile, line)) {
            parseLine(line);
        }
        
        parseFileData();

        std::cout << std::endl << "Parsing done" << std::endl;

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
                    std::cout << "Camera:" << std::endl;
                    lastObject = CAMERA;
                }
                else if (identifier == "sphere") {
                    std::cout << "Sphere:" << std::endl;
                    lastObject = SPHERE;
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
                        world->setCamera(parseCamera(data));
                        break;
                    case SPHERE:
                        world->addObject(parseSphere(data));
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
                    std::cout << "\tposition -> " << std::endl;
                    lastProperty = Camera::POSITION;
                }
                else if (identifier == "up") {
                    std::cout << "\tup -> " << std::endl;
                    lastProperty = Camera::UP;
                }
                else if (identifier == "forward") {
                    std::cout << "\tforward -> " << std::endl;
                    lastProperty = Camera::FORWARD;
                }
                else if (identifier == "fov") {
                    std::cout << "\tfov # " << std::endl;
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

Sphere* Parser::parseSphere(std::string data) {
    Sphere* outSphere = new Sphere();
    int segmentCount = 0;
    Sphere::SPHERE_PROPERTIES lastProperty = Sphere::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "center") {
                    std::cout << "\tcenter -> " << std::endl;
                    lastProperty = Sphere::CENTER;
                }
                else if (identifier == "radius") {
                    std::cout << "\tradius # " << std::endl;
                    lastProperty = Sphere::RADIUS;
                }
                else {
                    lastProperty = Sphere::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    case Sphere::CENTER:
                        outSphere->setCenter(parseVector(propertyData));
                        break;
                    case Sphere::RADIUS:
                        outSphere->setRadius(parseDouble(propertyData));
                        break;
                }
                lastProperty = Sphere::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outSphere;
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