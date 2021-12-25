#include "Parser.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include "World.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Object.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

Parser::Parser(std::string filename, bool VERBOSE): VERBOSE(VERBOSE) {
    std::ifstream inputFile;
    inputFile.open(filename);

    if (inputFile) {

        if (VERBOSE) std::cout << "Loading World..." << std::endl << std::endl;

        world = new World();

        std::string line;
        while (getline(inputFile, line)) {
            parseLine(line);
        }
        
        parseFileData();

        if (VERBOSE) std::cout << std::endl << "Parsing done" << std::endl;

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
                    if (VERBOSE) std::cout << "Camera:" << std::endl;
                    lastObject = CAMERA;
                }
                else if (identifier == "sphere") {
                    if (VERBOSE) std::cout << "Sphere:" << std::endl;
                    lastObject = SPHERE;
                }
                else if (identifier == "plane") {
                    if (VERBOSE) std::cout << "Plane:" << std::endl;
                    lastObject = PLANE;
                }
                else if (identifier == "point_light") {
                    if (VERBOSE) std::cout << "Point Light:" << std::endl;
                    lastObject = POINTLIGHT;
                }
                else if (identifier == "directional_light") {
                    if (VERBOSE) std::cout << "Directional Light:" << std::endl;
                    lastObject = DIRECTIONALLIGHT;
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
                        world->addObject((Object*)parseSphere(data));
                        break;
                    case PLANE:
                        world->addObject((Object*)parsePlane(data));
                        break;
                    case POINTLIGHT:
                        world->addLight((Light*)parsePointLight(data));
                        break;
                    case DIRECTIONALLIGHT:
                        world->addLight((Light*)parseDirectionalLight(data));
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
                    if (VERBOSE) std::cout << "\tposition -> " << std::endl;
                    lastProperty = Camera::POSITION;
                }
                else if (identifier == "up") {
                    if (VERBOSE) std::cout << "\tup -> " << std::endl;
                    lastProperty = Camera::UP;
                }
                else if (identifier == "forward") {
                    if (VERBOSE) std::cout << "\tforward -> " << std::endl;
                    lastProperty = Camera::FORWARD;
                }
                else if (identifier == "fov") {
                    if (VERBOSE) std::cout << "\tfov # " << std::endl;
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
                if (VERBOSE) std::cout << "\t\t" << propertyData << std::endl;
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
                    if (VERBOSE) std::cout << "\tcenter -> " << std::endl;
                    lastProperty = Sphere::CENTER;
                }
                else if (identifier == "radius") {
                    if (VERBOSE) std::cout << "\tradius # " << std::endl;
                    lastProperty = Sphere::RADIUS;
                }
                else if (identifier == "material") {
                    if (VERBOSE) std::cout << "\tmaterial * " << std::endl;
                    lastProperty = Sphere::MATERIAL;
                }
                else {
                    lastProperty = Sphere::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                if (VERBOSE) std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    case Sphere::CENTER:
                        outSphere->setCenter(parseVector(propertyData));
                        break;
                    case Sphere::RADIUS:
                        outSphere->setRadius(parseDouble(propertyData));
                        break;
                    case Sphere::MATERIAL:
                        outSphere->setMaterial(parseMaterial(propertyData));
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

Plane* Parser::parsePlane(std::string data) {
    Plane* outPlane = new Plane();
    int segmentCount = 0;
    Plane::PLANE_PROPERTIES lastProperty = Plane::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "q") {
                    if (VERBOSE) std::cout << "\tq -> " << std::endl;
                    lastProperty = Plane::Q;
                }
                else if (identifier == "n") {
                    if (VERBOSE) std::cout << "\tn -> " << std::endl;
                    lastProperty = Plane::N;
                }
                else if (identifier == "material") {
                    if (VERBOSE) std::cout << "\tmaterial * " << std::endl;
                    lastProperty = Plane::MATERIAL;
                }
                else {
                    lastProperty = Plane::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                if (VERBOSE) std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    case Plane::Q:
                        outPlane->setQ(parseVector(propertyData));
                        break;
                    case Plane::N:
                        outPlane->setN(parseVector(propertyData));
                        break;
                    case Plane::MATERIAL:
                        outPlane->setMaterial(parseMaterial(propertyData));
                        break;
                }
                lastProperty = Plane::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outPlane;
}

PointLight* Parser::parsePointLight(std::string data) {
    PointLight* outPointLight = new PointLight();
    int segmentCount = 0;
    PointLight::POINTLIGHT_PROPERTIES lastProperty = PointLight::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "position") {
                    if (VERBOSE) std::cout << "\tposition -> " << std::endl;
                    lastProperty = PointLight::POSITION;
                }
                else if (identifier == "intensity") {
                    if (VERBOSE) std::cout << "\tintensity -> " << std::endl;
                    lastProperty = PointLight::INTENSITY;
                }
                else {
                    lastProperty = PointLight::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                if (VERBOSE) std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    case PointLight::POSITION:
                        outPointLight->setPosition(parseVector(propertyData));
                        break;
                    case PointLight::INTENSITY:
                        outPointLight->setIntensity(parseVector(propertyData));
                        break;
                }
                lastProperty = PointLight::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outPointLight;
}

DirectionalLight* Parser::parseDirectionalLight(std::string data) {
    DirectionalLight* outDirectionalLight = new DirectionalLight();
    int segmentCount = 0;
    DirectionalLight::DIRECTIONALLIGHT_PROPERTIES lastProperty = DirectionalLight::NONE;
    for (int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case ':': {
                std::string identifier = data.substr(i-segmentCount, segmentCount);
                if (identifier == "direction") {
                    if (VERBOSE) std::cout << "\tdirection -> " << std::endl;
                    lastProperty = DirectionalLight::DIRECTION;
                }
                else if (identifier == "intensity") {
                    if (VERBOSE) std::cout << "\tintensity -> " << std::endl;
                    lastProperty = DirectionalLight::INTENSITY;
                }
                else {
                    lastProperty = DirectionalLight::NONE;
                }
                segmentCount = 0;
                break;
            }
            case ';': {
                std::string propertyData = data.substr(i-segmentCount, segmentCount);
                if (VERBOSE) std::cout << "\t\t" << propertyData << std::endl;
                switch (lastProperty) {
                    case DirectionalLight::DIRECTION:
                        outDirectionalLight->setDirection(parseVector(propertyData));
                        break;
                    case DirectionalLight::INTENSITY:
                        outDirectionalLight->setIntensity(parseVector(propertyData));
                        break;
                }
                lastProperty = DirectionalLight::NONE;
                segmentCount = 0;
                break;
            }
            default: {
                segmentCount++;
            }
        }
    }
    return outDirectionalLight;
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

Material Parser::parseMaterial(std::string data) {
    Material newMaterial {glm::dvec3(0, 0, 0), glm::dvec3(0, 0, 0), glm::dvec3(0, 0, 0), 0};
    int counter = 0;
    int dataCount = 0;
    if (data[0] == '[') {
        for (int i = 1; i < data.size(); i++) {
            if (data[i] == '>'|| data[i] == ']') {
                dataCount++;
                i++;
                if (counter == 0 ){
                    newMaterial.ambient = parseVector(data.substr(i-dataCount, dataCount));
                }
                else if (counter == 1) {
                    newMaterial.diffuse = parseVector(data.substr(i-dataCount, dataCount));
                }
                else if (counter == 2) {
                    newMaterial.specular = parseVector(data.substr(i-dataCount, dataCount));
                }
                else if (counter == 3) {
                    newMaterial.shinyness = parseDouble(data.substr(i-dataCount, dataCount-1));
                }
                counter++;
                dataCount = 0;
            }
            else {
                dataCount++;
            }
        }
    }
    return newMaterial;
}