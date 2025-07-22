#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "buffers.h"
#include "parser.h"

[[noreturn]] int main() {
    ASCIIRenderer renderer(400,150,Mesh("test.obj"));
    // Loop frame rendering
    while (true) {
        std::chrono::time_point<std::chrono::steady_clock> next = std::chrono::steady_clock::now();

        renderer.clearBuffers();
        renderer.drawMesh();
        renderer.renderFrame();
        renderer.ref.rotateReference(.05,.01,.02);

        next += std::chrono::milliseconds(32);
        std::this_thread::sleep_until(next);
    }
}