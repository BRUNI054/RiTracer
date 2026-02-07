#include "ray.hpp"

class shape {
public:
    virtual bool intersect(const ray& r) = 0;
};