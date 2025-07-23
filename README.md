# MeshToASCII

**MeshToASCII** is a 3D ASCII renderer written in C++ that projects mesh models (`.obj`) directly into your terminal. It features automatic scene rotation and smooth real-time rendering using terminal-optimized techniques.

---

## 🚀 Features

- Real-time visualization of 3D models in ASCII
- Supports `.obj` files with vertices and triangular faces
- 3D projection with depth buffering
- Simulated lighting using ASCII shading
- Automatic rotation for dynamic scene rendering
- Differential frame updates for high performance

---

## 🔧 Build Instructions

This project uses **CMake** and requires a compiler that supports C++17 or later.

```bash
git clone https://github.com/edomango05/MeshToASCII.git
cd MeshToASCII
mkdir build && cd build
cmake ..
make
```

The compiled binary will be `m2ascii`.

---

## ▶️ Usage

```bash
./m2ascii path/to/model.obj
```

The model will rotate continuously in the terminal.

---

## 📈 Performance

Rendering is optimized for speed and efficiency:

- Only changed characters between frames are redrawn
- Fast buffer operations using `std::memset`, `std::ranges::copy`
- Target frame rate of ~30 FPS, even on large terminal windows
- Very low memory footprint (~4 MB typical)

---

## 🧠 Techniques Used

- Orthographic projection with depth buffering (Z-buffer)
- Scene rotation using 3D transformation matrices
- Basic lighting model based on face normals
- ANSI escape sequences (`\x1b[y;xH`) for fast terminal drawing

---

## 🖥️ Requirements

- ANSI-compatible terminal (Gnome Terminal, Alacritty, iTerm2, etc.)
- Unix-like OS (Linux/macOS). On Windows, use WSL or a compatible terminal

---

## 📜 License

Distributed under the **MIT License**.

---

## 👤 Author

[edomango05](https://github.com/edomango05)
