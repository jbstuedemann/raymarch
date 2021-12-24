#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

struct Material {

    glm::dvec3 ambient;
    glm::dvec3 diffuse;
    glm::dvec3 specular;
    double shinyness;

};

#endif