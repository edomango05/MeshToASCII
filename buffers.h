//
// Created by edoardo on 7/22/25.
//

#ifndef BUFFERS_H
#define BUFFERS_H

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
    ASCIIRenderer(const int width_, const int height_, Mesh&& mesh): frameSize((width_ + 1) * height_), mesh(std::move(mesh)) {
        width = width_;
        height = height_;
        frameBuffer = std::vector<char>((width + 1) * height, ' ');
        depthBuffer = std::vector<float>((width + 1) * height, 0.0f);
        std::cout << "\x1b[2J"; // clean terminal

    }

    void clearBuffers()
    {
        // Escaping each line and setting the grid
        std::fill(frameBuffer.begin(), frameBuffer.end(), ' ');
        std::fill(depthBuffer.begin(), depthBuffer.end(), 0.f);

        for (uint row = 1; row <= height; row ++) {
            frameBuffer[row * (width + 1) - 1] = '\n';
        }
    }

     void renderFrame() const {
        std::cout << "\x1b[H"; // transfer cursor
        std::cout << std::string(frameBuffer.begin(), frameBuffer.end());
        std::cout.flush();
    }

    void projectVectorOnFrame(const Vector3 & vec, const char symbol) {
        // Projection to the plane z = k
        const int xFrame = static_cast<int>(vec.x * 2 + static_cast<float>(width) / 2);
        const int yFrame = static_cast<int>(vec.y + static_cast<float>(height) / 2);

        if (xFrame >=  width || yFrame >= height) return;

        const int frameIndex = yFrame * (width + 1) - 1 + xFrame;
        if (frameIndex > frameSize) return;
        if (const float depth = 1 / (vec.z +  110.f); depthBuffer[frameIndex] < depth) {
            drawSymbol(frameIndex, symbol, depth);
        }
    }

    void drawLine(const Vector3 from, const Vector3 to,  const char shade) {
        for (float lambda = 0.f; lambda <= 1.f; lambda += 0.01f) {
            projectVectorOnFrame(ref.rotatePoint({
                lambda*(to.x - from.x) + from.x,
                lambda*(to.y - from.y) + from.y,
                lambda*(to.z - from.z) + from.z}),
                shade);
        }
    }

    void drawFace(const Triangle& tr) {
        const char shade = shadeFromNormal(
                 ref.rotatePoint(mesh.vertices[tr[0]]),
                 ref.rotatePoint(mesh.vertices[tr[1]]),
                 ref.rotatePoint(mesh.vertices[tr[2]]));

        for (uint i = 0; i < 2; i ++) {
            // Drawing lines
            const Vector3 from = mesh.vertices[tr[i]];
            const Vector3 to = mesh.vertices[tr[i+ 1]];

            drawLine(from, to , shade);
        }
    }

    void drawMesh() {
        for (const auto & triangle : mesh.triangles) {
            drawFace(triangle);
        }
    }

private:
    int width, height; // default 800, 400
    uint frameSize;
    std::vector<char> frameBuffer;
    std::vector<float> depthBuffer;
    Mesh mesh;
    void drawSymbol(const uint frameIndex, const char symbol, const float depth) {
         frameBuffer[frameIndex] = symbol;
         depthBuffer[frameIndex] = depth;
    }

    char static shadeFromNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
         const Vector3 edge1 = v2 - v1;
         const Vector3 edge2 = v3 - v1;
         if ((edge2 - edge1).module() == 0) return ' ';
         const Vector3 normal = edge1.cross(edge2).normalize();

         float intensity = normal.dot(lightDir);
         intensity = std::clamp(intensity, 0.0f, 1.0f);

         const int index = static_cast<int>(intensity * (sizeof(ASCII_SHADES) - 2));
         return ASCII_SHADES[index];
     }
};


#endif //BUFFERS_H
