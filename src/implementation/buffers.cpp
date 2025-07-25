//
// Created by edoardo on 7/23/25.
//

#include "buffers.h"

#include <cstring>
#include <iostream>

ASCIIRenderer::ASCIIRenderer(const int width_, const int height_, Mesh &&mesh): m_frameSize((width_ + 1) * height_),
    m_mesh(std::move(mesh)) {
    m_width = width_;
    m_height = height_;
    m_frameBuffer = std::vector(m_frameSize, ' ');
    m_depthBuffer = std::vector(m_frameSize, 0.0f);
    m_cleanDepth = std::vector(m_frameSize, 0.0f);
    m_previousFrame = m_frameBuffer;
    for (uint row = 1; row <= m_height; row++) {
        m_previousFrame[row * (m_width + 1) - 1] = '\n';
    }
    std::cout << "\x1b[2J"; // clean terminal
    std::cout << "\x1b[?25l"; // remove cursor
}

void ASCIIRenderer::clearBuffers() {
    // Escaping each line and setting the grid
    std::memset(m_frameBuffer.data(), ' ', m_frameBuffer.size());

    //copying optimization makes it a 30% faster
    std::ranges::copy(m_cleanDepth, m_depthBuffer.begin());

    for (uint row = 1; row <= m_height; row++) {
        m_frameBuffer[row * (m_width + 1) - 1] = '\n';
    }
}

void ASCIIRenderer::renderFrame() {
    std::cout << "\x1b[H"; // transfer cursor
    std::cout << std::flush;

    const int stride = m_width + 1;

    for (int i = 0; i < m_frameSize; ++i) {
        if (m_frameBuffer[i] != m_previousFrame[i]) {
            int x = i % stride;
            int y = i / stride;
            std::printf("\x1b[%d;%dH%c", y + 1, x + 1, m_frameBuffer[i]);
            m_previousFrame[i] = m_frameBuffer[i];
        }
    }

    std::fflush(stdout);
}

void ASCIIRenderer::projectVectorOnFrame(const Vector3 &vec, const char symbol) {
    // Projection to the plane z = k
    const int xFrame = static_cast<int>(vec.x * 2 + static_cast<float>(m_width) / 2);
    const int yFrame = static_cast<int>(vec.y + static_cast<float>(m_height) / 2);

    if (xFrame >= m_width || yFrame >= m_height) return;

    const int frameIndex = yFrame * (m_width + 1) - 1 + xFrame;
    if (frameIndex > m_frameSize) return;
    if (const float depth = 1 / (vec.z + 1100.f); m_depthBuffer[frameIndex] < depth) {
        drawSymbol(frameIndex, symbol, depth);
    }
}

void ASCIIRenderer::drawLine(const Vector3 from, const Vector3 to, const char shade) {
    for (float lambda = 0.f; lambda <= 1.f; lambda += 0.05f) {
        projectVectorOnFrame(ref.rotatePoint({
                                 lambda * (to.x - from.x) + from.x,
                                 lambda * (to.y - from.y) + from.y,
                                 lambda * (to.z - from.z) + from.z
                             }),
                             shade);
    }
}

void ASCIIRenderer::drawFace(const Triangle &tr) {
    const char shade = shadeFromNormal(
        ref.rotatePoint(m_mesh.vertices[tr.i1]),
        ref.rotatePoint(m_mesh.vertices[tr.i2]),
        ref.rotatePoint(m_mesh.vertices[tr.i3]));

    Vector3 from = m_mesh.vertices[tr.i1];
    Vector3 to = m_mesh.vertices[tr.i2];
    drawLine(from, to, shade);

    from = m_mesh.vertices[tr.i2];
    to = m_mesh.vertices[tr.i3];
    drawLine(from, to, shade);

    from = m_mesh.vertices[tr.i3];
    to = m_mesh.vertices[tr.i1];
    drawLine(from, to, shade);
}

void ASCIIRenderer::drawMesh() {
    for (const auto &triangle: m_mesh.triangles) {
        drawFace(triangle);
    }
}

void ASCIIRenderer::drawSymbol(const uint frameIndex, const char symbol, const float depth) {
    m_frameBuffer[frameIndex] = symbol;
    m_depthBuffer[frameIndex] = depth;
}


char ASCIIRenderer::shadeFromNormal(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) {
    const Vector3 edge1 = v2 - v1;
    const Vector3 edge2 = v3 - v1;
    if ((edge2 - edge1).module() == 0) return ' ';
    const Vector3 normal = edge1.cross(edge2).normalize();

    float intensity = normal.dot(g_lightDir);
    intensity = std::clamp(intensity, 0.0f, 1.0f);

    const int index = static_cast<int>(intensity * (sizeof(ASCII_SHADES) - 2));
    return ASCII_SHADES[index];
}
