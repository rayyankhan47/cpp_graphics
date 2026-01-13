#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Vec3.h"
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Camera {
public:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;

    Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, 
           double vfov, double aspect_ratio, 
           double aperture, double focus_dist) {
        double theta = vfov * M_PI / 180.0;
        double h = std::tan(theta/2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        w = (lookfrom - lookat).normalized();
        u = cross(vup, w).normalized();
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        lens_radius = aperture / 2;
    }

    Ray get_ray(double s, double t) const {
        Vec3 rd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rd.x + v * rd.y;

        return Ray(
            origin + offset,
            lower_left_corner + s*horizontal + t*vertical - origin - offset
        );
    }

private:
    Vec3 random_in_unit_disk() const {
        while (true) {
            Vec3 p = Vec3(
                (double)rand() / RAND_MAX * 2.0 - 1.0,
                (double)rand() / RAND_MAX * 2.0 - 1.0,
                0
            );
            if (p.length_squared() < 1.0) {
                return p;
            }
        }
    }
};

#endif
