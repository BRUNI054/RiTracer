#include "shape.hpp"
#include "vec3.hpp"

class sphere : public shape {
private:
    float radius;
    color c;
    point center;
public:
    sphere(point center, float radius, color c) : center(center), radius(radius), c(c) {}
    bool intersect(const ray& r) override {
        ray tmp = ray(r.origin(), r.direction());
        vec3 dist = tmp.origin() - center;
        float A = tmp.direction().dot(tmp.direction());
        float B = (tmp.direction()*2).dot(dist);
        float C = (dist.dot(dist)) - (radius*radius);
        float dis = (B*B) - (4*A*C);
        if (dis >= 0){
            return true;
        }
        return false;
    }
};