# MeshToASCII

**MeshToASCII** is a lightweight C++ application that renders 3D triangular meshes as ASCII art directly in the terminal. It reads standard `.obj` files and projects the 3D geometry into a 2D ASCII view, updating the terminal in real time with smooth rotation and lighting simulation.

The project is written entirely in C++17 and emphasizes performance, compactness, and minimal dependencies. It provides a visually engaging way to explore 3D shapes in environments without graphical output, making it ideal for experimentation, learning, or just entertainment in a terminal window.

## Building the Project

MeshToASCII uses CMake for its build system. To compile it, ensure that a C++17-compatible compiler is available on your system. Then follow these steps:

```bash
git clone https://github.com/edomango05/MeshToASCII.git
cd MeshToASCII
mkdir build && cd build
cmake ..
make
```

This will produce the executable `m2ascii` inside the `build` directory.

## Running the Application

To run the renderer, execute the binary with the path to a valid `.obj` file as an argument:

```bash
./m2ascii path/to/model.obj
```

The program expects the OBJ file to include vertex (`v`) and triangular face (`f`) data. Once loaded, the model will begin rotating automatically and render continuously in the terminal.

## Performance and Rendering Approach

The rendering system is optimized to work efficiently in terminal environments. It performs differential frame updates, meaning only the characters that have changed since the previous frame are redrawn. This significantly reduces the overhead of full-screen redraws.

To enhance realism, the renderer uses simple lighting techniques based on triangle normals and applies varying ASCII characters to simulate shading. Rotation is handled via transformation matrices, and a Z-buffer is used to manage depth and visibility.

Despite its minimal resource usage (approximately 3MB of RAM), the renderer can maintain interactive frame rates even on larger terminal windows.

## Compatibility

MeshToASCII is designed for UNIX-like systems and works best in ANSI-compatible terminals such as Gnome Terminal, iTerm2, Alacritty, or others supporting standard escape codes. On Windows, it is recommended to run it under WSL or through a terminal that supports ANSI escape sequences.

## License and Credits

The project is released under the MIT License. It was created and is maintained by [edomango05](https://github.com/edomango05).
