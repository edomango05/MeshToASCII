//
// Created by edoardo on 7/22/25.
//



#ifndef BUFFERS_H
#define BUFFERS_H

#include <vector>
#include <sys/types.h>

#include "linear.h"
#include "parser.h"

// List of chars to simulate light
constexpr char ASCII_SHADES[] = ".:-=+*#%@";
// Light direction
const Vector3 g_lightDir = Vector3{0, 1, -1}.normalize();

struct ASCIIRenderer {
    Reference ref;

    ASCIIRenderer(const int width_, const int height_, Mesh &&mesh);

    void clearBuffers();

    void renderFrame();

    void projectVectorOnFrame(const Vector3 &vec, const char symbol);

    void drawLine(const Vector3 from, const Vector3 to, const char shade);

    void drawFace(const Triangle &tr);

    void drawMesh();

private:
    int m_width, m_height; // default 800, 400
    uint m_frameSize;

    std::vector<char> m_frameBuffer;
    std::vector<char> m_previousFrame;
    std::vector<float> m_depthBuffer;
    std::vector<float> m_cleanDepth;

    Mesh m_mesh;

    void drawSymbol(const uint frameIndex, const char symbol, const float depth);

    char static shadeFromNormal(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);
};


#endif //BUFFERS_H
