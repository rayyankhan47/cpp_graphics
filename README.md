# Ray Tracer

A CPU-based ray tracer implemented in C++ that generates realistic images by simulating light transport through a 3D scene.

## Features

- **Ray-Sphere Intersection**: Efficient sphere intersection calculations
- **Material System**: 
  - Lambertian (diffuse) materials
  - Metal materials with configurable fuzziness
  - Material-based light scattering
- **Camera System**: 
  - Configurable field of view
  - Depth of field (defocus blur)
  - Adjustable focus distance
- **Lighting & Shading**:
  - Soft shadows
  - Reflections (metal materials)
  - Multiple light bounces (recursive ray tracing)
- **Scene Management**: Support for multiple objects in a scene
- **Anti-aliasing**: Multi-sample per pixel for smooth rendering
- **Image Output**: PPM format output

## Building

### Requirements
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.15 or higher

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

For optimized release build:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Usage

Run the ray tracer:
```bash
./raytracer > image.ppm
```

View the generated PPM image using any image viewer that supports PPM format, or convert it:
```bash
# Using ImageMagick
convert image.ppm image.png

# Or using ffmpeg
ffmpeg -i image.ppm image.png
```

## Rendering Parameters

You can modify rendering parameters in `src/main.cpp`:

- `image_width`: Output image width (default: 400)
- `image_height`: Output image height (auto-calculated based on aspect ratio)
- `samples_per_pixel`: Number of samples per pixel for anti-aliasing (default: 50)
- `max_depth`: Maximum ray bounce depth (default: 50)

The scene includes:
- A large ground sphere
- Multiple randomly placed small spheres with various materials
- Three large spheres with different material properties

## Project Structure

```
.
├── include/          # Header files
│   ├── Vec3.h       # 3D vector mathematics
│   ├── Ray.h        # Ray representation
│   ├── Sphere.h     # Sphere geometry and hit detection
│   ├── Material.h   # Material system (Lambertian, Metal)
│   ├── Camera.h     # Camera and ray generation
│   ├── Scene.h      # Scene management
│   ├── RayTracer.h  # Core ray tracing algorithm
│   └── Utils.h      # Utility functions (random number generation)
├── src/             # Source files
│   └── main.cpp     # Main rendering loop and scene setup
├── CMakeLists.txt   # CMake build configuration
└── README.md        # This file
```

## Algorithm Overview

The ray tracer uses a recursive algorithm:

1. For each pixel, cast multiple rays (anti-aliasing)
2. For each ray, check intersection with scene objects
3. If an intersection is found:
   - Calculate material properties
   - Generate scattered ray based on material
   - Recursively trace scattered ray
   - Combine colors with material attenuation
4. If no intersection, return background color
5. Average all samples and apply gamma correction
6. Output color values to PPM format

## Future Enhancements

Potential additions for future development:
- Dielectric (glass) materials with refraction
- More geometric primitives (planes, boxes, triangles)
- Texture mapping
- Area lights
- BVH (Bounding Volume Hierarchy) acceleration structure
- Multi-threading for faster rendering


