#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec3.h"
#include "Ray.h"

struct HitRecord;

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray& ray_in, const HitRecord& rec, 
                         Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Color albedo;

    Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray& ray_in, const HitRecord& rec, 
                 Color& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
public:
    Color albedo;
    double fuzz;

    Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const Ray& ray_in, const HitRecord& rec, 
                 Color& attenuation, Ray& scattered) const override;
};

#endif
