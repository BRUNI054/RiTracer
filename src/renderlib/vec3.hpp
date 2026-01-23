#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
  private:
    
    //members
    float var[3];

  public:

    //constructors
    vec3() : var{0,0,0} {}
    vec3(float var0, float var1, float var2) : var{var0, var1, var2} {}
  
    //methods
    float x() const {return var[0];}
    float y() const {return var[1];}
    float z() const {return var[2];}

    float r() const {return var[0];}
    float g() const {return var[1];}
    float b() const {return var[2];}

    float length() const {
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return var[0]*var[0] + var[1]*var[1] + var[2]*var[2];
    }

    float dot(const vec3& v) {
        return var[0] * v.var[0]
            + var[1] * v.var[1]
            + var[2] * v.var[2];
    }

    vec3 cross(const vec3& v) {
        return vec3(var[1] * v.var[2] - var[2] * v.var[1],
                    var[2] * v.var[0] - var[0] * v.var[2],
                    var[0] * v.var[1] - var[1] * v.var[0]);
    }

    vec3 get_unit_vector() {
        return *this / length();
    }

    //operator overloads
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

    std::ostream& operator<<(std::ostream& out) {
        return out << var[0] << ' ' << var[1] << ' ' << var[2];
    }

    vec3 operator+( const vec3& v) {
        return vec3(var[0] + v.var[0], var[1] + v.var[1], var[2] + v.var[2]);
    }

    vec3 operator-(const vec3& v) {
        return vec3(var[0] - v.var[0], var[1] - v.var[1], var[2] - v.var[2]);
    }

    vec3 operator*(const vec3& v) {
        return vec3(var[0] * v.var[0], var[1] * v.var[1], var[2] * v.var[2]);
    }

    friend vec3 operator*(float t, const vec3& v) {
        return vec3(t*v.var[0], t*v.var[1], t*v.var[2]);
    }

    vec3 operator*(float t) {
        return t * *this;
    }

    vec3 operator/(float t) {
        return (1/t) * *this;
    }

};

using dmag = vec3;
using color = vec3;


#endif