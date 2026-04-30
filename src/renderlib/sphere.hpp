#pragma once

#include "shape.hpp"
#include "vec3.hpp"
#include <memory>
#include <iostream>
#include <array>


class sphere : public shape {
private:
    float radius;
    std::shared_ptr<shader> shade;
    point center;
public:
    sphere(point center_, float radius_, std::shared_ptr<shader> shade_) : center(center_), radius(radius_), shade(shade_) {}
    
    bool intersect(const ray& r, const float tmin, float& tmax, hitStruct& h) override {
        vec3 dist = r.origin() - center;
        float A, B, C, dis, t, t1, t2;
        A = r.direction().dot(r.direction());
        B = (r.direction()*2).dot(dist);
        C = (dist.dot(dist)) - (radius*radius);
        dis = (B*B) - (4*A*C);
        t1 = (-B + std::sqrt(dis))/(2*A);
        t2 = (-B - std::sqrt(dis))/(2*A);
        
        if (t1 <= t2) {
            t = t1;
        } else {
            t = t2;
        }
        if (tmax < t || tmin > t) {
            return false;
        }
        if (dis >= 0){
            tmax = t;
            h.t = t;
            h.normal = (r.at(t) - center)/radius;
            h.intersectPoint = r.at(t);
            h.viewDir = r.direction();
            h.shade = shade;

            return true;
        }
        return false;
    }
};