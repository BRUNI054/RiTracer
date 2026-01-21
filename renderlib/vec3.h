#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
  public:
    float var[3];

    vec3() : var{0,0,0} {}
    vec3(float var0, float var1, float var2) : var{var0, var1, var2} {}

    float x() const { return var[0]; }
    float y() const { return var[1]; }
    float z() const { return var[2]; }

    vec3 operator-() const { return vec3(-var[0], -var[1], -var[2]); }
    float operator[](int i) const { return var[i]; }
    float& operator[](int i) { return var[i]; }

    vec3& operator+=(const vec3& v) {
        var[0] += v.var[0];
        var[1] += v.var[1];
        var[2] += v.var[2];
        return *this;
    }

    vec3& operator*=(float t) {
        var[0] *= t;
        var[1] *= t;
        var[2] *= t;
        return *this;
    }

    vec3& operator/=(float t) {
        return *this *= 1/t;
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return var[0]*var[0] + var[1]*var[1] + var[2]*var[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.var[0] << ' ' << v.var[1] << ' ' << v.var[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.var[0] + v.var[0], u.var[1] + v.var[1], u.var[2] + v.var[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.var[0] - v.var[0], u.var[1] - v.var[1], u.var[2] - v.var[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.var[0] * v.var[0], u.var[1] * v.var[1], u.var[2] * v.var[2]);
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t*v.var[0], t*v.var[1], t*v.var[2]);
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
    return u.var[0] * v.var[0]
         + u.var[1] * v.var[1]
         + u.var[2] * v.var[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.var[1] * v.var[2] - u.var[2] * v.var[1],
                u.var[2] * v.var[0] - u.var[0] * v.var[2],
                u.var[0] * v.var[1] - u.var[1] * v.var[0]);
}

inline vec3 get_unit_vector(const vec3& v) {
    return v / v.length();
}

#endif