#include "shader.hpp"
#include "ray.hpp"
#include "hitStruct.hpp"
#include "scene.hpp"

class mirror : public shader {
private:
    std::shared_ptr<scene> s_;
public:
    mirror(std::shared_ptr<scene> Scene) : s_(Scene) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 d = h.viewDir.get_unit_vector();
        vec3 mirrorDirection = d - 2.0f*(d.dot(h.normal))*h.normal;
        ray r(h.intersectPoint, mirrorDirection);
        return s_->computeRayColor(r, 0, std::numeric_limits<float>::infinity(), h.depth-1);
    }
};