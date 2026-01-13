#include "../include/RayTracer.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"
#include "../include/Material.h"
#include "../include/Camera.h"
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

Scene random_scene() {
    Scene world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = (double)rand() / RAND_MAX;
            Point3 center(a + 0.9 * ((double)rand() / RAND_MAX), 0.2, b + 0.9 * ((double)rand() / RAND_MAX));

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color(
                        (double)rand() / RAND_MAX * (double)rand() / RAND_MAX,
                        (double)rand() / RAND_MAX * (double)rand() / RAND_MAX,
                        (double)rand() / RAND_MAX * (double)rand() / RAND_MAX
                    );
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color(
                        0.5 * (1 + (double)rand() / RAND_MAX),
                        0.5 * (1 + (double)rand() / RAND_MAX),
                        0.5 * (1 + (double)rand() / RAND_MAX)
                    );
                    auto fuzz = 0.5 * (double)rand() / RAND_MAX;
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass (for now, just use metal - can add later)
                    auto albedo = Color(0.9, 0.9, 0.9);
                    sphere_material = std::make_shared<Metal>(albedo, 0.1);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 0.1);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    // Seed random number generator
    srand(time(nullptr));

    // World
    Scene world = random_scene();

    // Camera
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + ((double)rand() / RAND_MAX)) / (image_width - 1);
                double v = (j + ((double)rand() / RAND_MAX)) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixel_color += RayTracer::ray_color(r, world, max_depth);
            }
            RayTracer::write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cerr << "\nDone! Rendering took " << duration.count() << " seconds.\n";
}
