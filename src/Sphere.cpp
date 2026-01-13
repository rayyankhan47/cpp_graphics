#include "../include/Sphere.h"
#include <cmath>

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.orig - center;
    double a = r.dir.length_squared();
    double half_b = dot(oc, r.dir);
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return false;
    
    double sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}
