#pragma once

#include "ray.hpp"
#include "shader.hpp"
#include "hitStruct.hpp"
#include <memory>


class shape : std::enable_shared_from_this<shape>{
public:
    virtual bool intersect(const ray& r, const float tmin, float& tmax, hitStruct& h) = 0;

    std::shared_ptr<shape> getSelf() {
        return shared_from_this();
    }
};