#include "vec3.hpp"

class ray {
    public:
        ray() : orig(point(0.0f,0.0f,0.0f)), dir(vec3(1.0f,1.0f,1.0f)) {}

        ray(const point& origin, const vec3 direction) : orig(origin), dir(direction) {}

        const point& origin() const {return orig;}
        const vec3& direction() const {return dir;}

        point at(float t) const {
            return (t*dir) + orig;
        }
    private:
        point orig;
        vec3 dir;
};