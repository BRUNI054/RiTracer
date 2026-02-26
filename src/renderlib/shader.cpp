#include "shader.hpp"
#include "scene.hpp"
#include "hitStruct.hpp"
#include "vec3.hpp"
#include <memory>

bool shader::inShadow(hitStruct& h, vec3 lightDirection, std::shared_ptr<scene> s_) {
    hitStruct shadowStruct;
    ray shadowRay(h.intersectPoint, (lightDirection));
    float tmax = lightDirection.length();
    for (int idx=0; idx<s_->getObjects().size(); idx++) {
        if (s_->getObjects()[idx]->intersect(shadowRay, 0, tmax, shadowStruct)) {
            return true;
        }
    }
    return false;
}
