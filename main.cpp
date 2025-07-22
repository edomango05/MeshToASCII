#include <chrono>
#include <thread>

#include "buffers.h"
#include "parser.h"

[[noreturn]] int main(const int argc, const char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_obj_file>\n";
        return 1;
    }

    const std::string filename = argv[1];
    ASCIIRenderer renderer(1600,300,Mesh(filename));

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