//
// Created by edoardo on 7/23/25.
//
#include "parser.h"

Mesh::Mesh(const std::string& filename)  {
    std::ifstream file(filename);
    std::string line;


    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vector3 v{};
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (prefix == "f") {
            int i0, i1, i2;
            std::string a, b, c;
            iss >> a >> b >> c;

            auto parseIndex = [](const std::string& token) {
                std::istringstream ss(token);
                std::string vi_str;
                std::getline(ss, vi_str, '/');
                return std::stoi(vi_str) - 1;
            };

            i0 = parseIndex(a);
            i1 = parseIndex(b);
            i2 = parseIndex(c);

            triangles.push_back({i0, i1, i2});
        }
    }
}