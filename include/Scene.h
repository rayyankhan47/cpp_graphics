#ifndef SCENE_H
#define SCENE_H

#include "Sphere.h"
#include "Ray.h"
#include <vector>
#include <memory>

class Scene {
public:
    std::vector<std::shared_ptr<Sphere>> objects;

    Scene() {}

    void add(std::shared_ptr<Sphere> object) {
        objects.push_back(object);
    }

    void clear() {
        objects.clear();
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif
