//
// Created by edoardo on 7/22/25.
//

#ifndef BUFFERS_H
#define BUFFERS_H

#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
#include <sys/types.h>

#include "linear.h"
#include "parser.h"

// List of chars to simulate light
constexpr char ASCII_SHADES[] = ".:-=+*#%@";

struct ASCIIRenderer {
    Reference ref;
    ASCIIRenderer(const int width_, const int height_, Mesh&& mesh);

    void clearBuffers();
    void renderFrame();

    void projectVectorOnFrame(const Vector3 & vec, const char symbol);

    void drawLine(const Vector3 from, const Vector3 to,  const char shade);
    void drawFace(const Triangle& tr);
    void drawMesh();


private:
    int width, height; // default 800, 400
    uint frameSize;

    std::vector<char> frameBuffer;
    std::vector<char> previousFrame;
    std::vector<float> depthBuffer;
    std::vector<float> cleanDepth;

    Mesh mesh;

    void drawSymbol(const uint frameIndex, const char symbol, const float depth);
    char static shadeFromNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
};


#endif //BUFFERS_H
