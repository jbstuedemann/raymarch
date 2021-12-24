#ifndef PARSER_HPP
#define PARSER_HPP

#include "Camera.hpp"
#include "Sphere.hpp"
#include "World.hpp"
#include <string>
#include <glm/glm.hpp>

struct FileNotFoundException : public std::exception
{
	const char * what () const throw ()
    {
    	return "File Not Found";
    }
};

enum OBJECT {
    NONE,
    CAMERA,
    SPHERE
};

class Parser {
public:
    Parser(std::string filename, bool VERBOSE=false);

    World* getWorld() { return world; }

private:
    std::string filedata;
    World* world;

    const bool VERBOSE = false;

    //File Parsing
    void parseLine(std::string line);
    void parseFileData();

    //Object Parsing
    Camera* parseCamera(std::string data);
    Sphere* parseSphere(std::string data);

    //Property Parsing
    glm::dvec3 parseVector(std::string data);
    double parseDouble(std::string data) { return std::stod(data); }
    Material parseMaterial(std::string data);
};

#endif