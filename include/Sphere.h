#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include <memory>

struct HitRecord {
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Sphere {
public:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;

    Sphere() {}
    Sphere(Point3 cen, double r, std::shared_ptr<Material> m)
        : center(cen), radius(r), mat(m) {}

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

#endif
