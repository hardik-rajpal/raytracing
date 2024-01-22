#pragma once
#include "hittable.h"
class sphere: public hittable{
public:
    sphere(point3 _center, double _radius):center(_center),radius(_radius){}
    bool isHit(const ray&r, interval rayT, hitRecord& rec)const{
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0){return false;};
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (! rayT.contains(root)) {
            root = (-half_b + sqrtd) / a;
            if (!rayT.contains(root)){
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center)/radius;
        rec.setFaceNormal(r,rec.normal);
        return true;
    }
private:
    point3 center;
    double radius;
};