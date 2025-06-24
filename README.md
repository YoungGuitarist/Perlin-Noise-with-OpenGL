# Perlin Noise with OpenGL
![OpenGL](https://img.shields.io/badge/OpenGL-3.3%2B-brightgreen)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-blue)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey)

A cross-platform implementation of Perlin noise generation and visualization using modern OpenGL (Core Profile 3.3+).

## 📌 Key Features
- **Classic Perlin Noise Implementation**: Faithful recreation of Ken Perlin's original algorithm
- **Customizable Scaling**: Dynamically adjust noise granularity via `scale` parameter
- **Color Gradient Visualization**: Intuitive heatmap display (blue to red spectrum)
- **Cross-Platform Compatibility**:
    - ✔️ Linux (Arch/Ubuntu)
    - ✔️ Windows (MSVC/MinGW)
- **Modern OpenGL Pipeline**: Utilizes GLFW+GLAD for efficient rendering (OpenGL 3.3+ Core Profile)

## 📦 Setup files

### For Linux (Ubuntu/Arch)
```bash
#Ubuntu
sudo apt install -y \
    build-essential \
    cmake \
    libglfw3-dev \
    libgl1-mesa-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev
#Arch
sudo pacman -Syu --needed \
    base-devel \
    cmake \
    glfw-x11 \
    mesa \
    libxi \
    libxrandr \
    libxinerama \
    libxcursor
```
### For Windows
1. Install CMake
2. Install GLFW (download binary version)
3. Install GLAD:

    - Go to glad.dav1d.de
    
    - Setup:

          Language: C/C++

          Specification: OpenGL

          API: Version 3.3 ir higher

          Profile: Core

          Options: Generate a loader

          Download an archive and unpack it include/glad
## 🛠️ Project build
### Linux
```bash
git clone https://github.com/YoungGuitarist/Perlin-Noise-with-OpenGL
cd Perlin-Noise-with-OpenGL

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Windows (via CMake GUI)
- Open CMake GUI
- Specify the path to the source code and the build folder (e.g., `build`)
- Click "Configure" and select your compiler (Visual Studio or MinGW)
- Specify paths to dependencies (GLFW, GLAD)
- Click "Generate", then open the project in your IDE

### Windows (via command line)
```cmd
git clone https://github.com/YoungGuitarist/Perlin-Noise-with-OpenGL
cd Perlin-Noise-with-OpenGL

mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## 🚀 Launch programm
After build:
```
#Linux:    
./build/PerlinNoise
```

```
#Windows: 
build\Release\PerlinNoise.exe
```

## ⚙️ Setup params
You can change params in main.cpp:
```cpp
const float scale = 0.1f;  // Масштаб шума
const int width = 800;     // Ширина окна
const int height = 600;    // Высота окна
```