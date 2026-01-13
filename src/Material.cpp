#include "../include/Material.h"
#include "../include/Sphere.h"
#include <cmath>
#include <cstdlib>

// Forward declaration helper for random
Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p = Vec3(
            (double)rand() / RAND_MAX * 2.0 - 1.0,
            (double)rand() / RAND_MAX * 2.0 - 1.0,
            (double)rand() / RAND_MAX * 2.0 - 1.0
        );
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

Vec3 random_unit_vector() {
    return random_in_unit_sphere().normalized();
}

bool Lambertian::scatter(const Ray& ray_in, const HitRecord& rec, 
                         Color& attenuation, Ray& scattered) const {
    Vec3 scatter_direction = rec.normal + random_unit_vector();
    
    // Catch degenerate scatter direction
    if (scatter_direction.length_squared() < 1e-8) {
        scatter_direction = rec.normal;
    }
    
    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const Ray& ray_in, const HitRecord& rec, 
                    Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(ray_in.dir.normalized(), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.dir, rec.normal) > 0);
}
