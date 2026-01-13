#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"
#include <algorithm>

class RayTracer {
public:
    static Color ray_color(const Ray& r, const Scene& world, int depth) {
        if (depth <= 0) {
            return Color(0, 0, 0);
        }

        HitRecord rec;
        if (world.hit(r, 0.001, INFINITY, rec)) {
            Ray scattered;
            Color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, world, depth-1);
            }
            return Color(0, 0, 0);
        }

        // Background gradient
        Vec3 unit_direction = r.dir.normalized();
        double t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    static void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel) {
        double r = pixel_color.x;
        double g = pixel_color.y;
        double b = pixel_color.z;

        // Divide the color by the number of samples and gamma-correct
        double scale = 1.0 / samples_per_pixel;
        r = std::sqrt(scale * r);
        g = std::sqrt(scale * g);
        b = std::sqrt(scale * b);

        // Write the translated [0,255] value of each color component
        out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
    }
};

#endif
