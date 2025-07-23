//
// Created by edoardo on 7/23/25.
//

#include "buffers.h"

ASCIIRenderer::ASCIIRenderer(const int width_, const int height_, Mesh&& mesh):
frameSize((width_ + 1) * height_),
mesh(std::move(mesh)) {
    width = width_;
    height = height_;
    frameBuffer = std::vector(frameSize, ' ');
    depthBuffer = std::vector(frameSize, 0.0f);
    cleanDepth = std::vector(frameSize, 0.0f);
    previousFrame = frameBuffer;
    for (uint row = 1; row <= height; row ++) {
        previousFrame[row * (width + 1) - 1] = '\n';
    }
    std::cout << "\x1b[2J"; // clean terminal
    std::cout << "\x1b[?25l"; // remove cursor
}

void ASCIIRenderer::clearBuffers() {
    // Escaping each line and setting the grid
    std::memset(frameBuffer.data(),' ', frameBuffer.size());

    //copying optimization makes it a 30% faster
    std::ranges::copy(cleanDepth, depthBuffer.begin());

    for (uint row = 1; row <= height; row ++) {
        frameBuffer[row * (width + 1) - 1] = '\n';
    }
}

void ASCIIRenderer::renderFrame()  {
    std::cout << "\x1b[H"; // transfer cursor
    std::cout << std::flush;

    const int stride = width + 1;

    for (int i = 0; i < frameSize; ++i) {
        if (frameBuffer[i] != previousFrame[i]) {
            int x = i % stride;
            int y = i / stride;
            std::printf("\x1b[%d;%dH%c", y + 1, x + 1, frameBuffer[i]);
            previousFrame[i] = frameBuffer[i];
        }
    }

    std::fflush(stdout);
}

void ASCIIRenderer::projectVectorOnFrame(const Vector3 & vec, const char symbol) {
    // Projection to the plane z = k
    const int xFrame = static_cast<int>(vec.x * 2 + static_cast<float>(width) / 2);
    const int yFrame = static_cast<int>(vec.y + static_cast<float>(height) / 2);

    if (xFrame >=  width || yFrame >= height) return;

    const int frameIndex = yFrame * (width + 1) - 1 + xFrame;
    if (frameIndex > frameSize) return;
    if (const float depth = 1 / (vec.z +  1100.f); depthBuffer[frameIndex] < depth) {
        drawSymbol(frameIndex, symbol, depth);
    }
}

void ASCIIRenderer::drawLine(const Vector3 from, const Vector3 to,  const char shade) {
    for (float lambda = 0.f; lambda <= 1.f; lambda += 0.05f) {
        projectVectorOnFrame(ref.rotatePoint({
            lambda*(to.x - from.x) + from.x,
            lambda*(to.y - from.y) + from.y,
            lambda*(to.z - from.z) + from.z}),
            shade);
    }
}

void ASCIIRenderer::drawFace(const Triangle& tr) {
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

void ASCIIRenderer::drawMesh() {
    for (const auto & triangle : mesh.triangles) {
        drawFace(triangle);
    }
}

void ASCIIRenderer::drawSymbol(const uint frameIndex, const char symbol, const float depth) {
    frameBuffer[frameIndex] = symbol;
    depthBuffer[frameIndex] = depth;
}


char ASCIIRenderer::shadeFromNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    const Vector3 edge1 = v2 - v1;
    const Vector3 edge2 = v3 - v1;
    if ((edge2 - edge1).module() == 0) return ' ';
    const Vector3 normal = edge1.cross(edge2).normalize();

    float intensity = normal.dot(lightDir);
    intensity = std::clamp(intensity, 0.0f, 1.0f);

    const int index = static_cast<int>(intensity * (sizeof(ASCII_SHADES) - 2));
    return ASCII_SHADES[index];
}