#ifndef PARSER_H
#define PARSER_H

#include "Camera.hpp"
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
    BOX
};

class Parser {
public:
    Parser(std::string filename);

private:
    std::string filedata;

    //File Parsing
    void parseLine(std::string line);
    void parseFileData();

    //Object Parsing
    Camera* parseCamera(std::string data);
    int parseBox(std::string data);

    //Property Parsing
    glm::dvec3 parseVector(std::string data);
    double parseDouble(std::string data) { return std::stod(data); }
};

#endif