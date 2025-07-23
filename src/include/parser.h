//
// Created by edoardo on 7/22/25.
//

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "linear.h"

using Triangle = std::vector<int>;

class Mesh {
public:
    std::vector< Vector3> vertices;
    std::vector< Triangle> triangles;

    explicit Mesh(const std::string& filename);
};


#endif //PARSER_H
