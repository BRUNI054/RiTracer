#pragma once

#include "shape.hpp"



class triangle : public shape {
private:
    point A, B, C;
    std::shared_ptr<shader> shade;

public:
    triangle() : A(point(1.0f,0.0f,0.0f)), B(point(0.0f, 1.0f, 0.0f)), C(point(0.0f, 0.0f, 1.0f)) {}
    triangle(point a, point b, point c, std::shared_ptr<shader> shade) : A(a), B(b), C(c), shade(shade) {}

    std::vector<float> returnVertices(int sphereDepth) override {
        vec3 N = (B-A).cross(C-A).get_unit_vector();
        return {A.x(), A.y(), A.z(), B.x(), B.y(), B.z(), C.x(), C.y(), C.z(), N.x(), N.y(), N.z()};
    }

    

    bool intersect(const ray& r, const float tmin, float& tmax, hitStruct& hit) override {
        vec3 edge2 = B - A;
        vec3 edge1 = C - A;
        vec3 P = r.direction().cross(edge2);
        float det = edge1.dot(P);

        constexpr float eps = 1e-8f;
        if (det > -eps && det < eps) {return false;}

        float inv_det = 1.0f / det;

        vec3 T = r.origin() - A;

        vec3 Q = T.cross(edge1);

        float t = edge2.dot(Q) * inv_det;
        if (t < tmin || t > tmax) {return false;}

        float u = T.dot(P) * inv_det;
        if (u < 0.0f || u > 1.0f) {return false;}

        float v = r.direction().dot(Q) * inv_det;
        if (v < 0.0f || u + v > 1.0f) {return false;}

        tmax = t;
        hit.t = t;
        hit.normal = edge1.cross(edge2).get_unit_vector();
        hit.intersectPoint = r.at(t);
        hit.viewDir = r.direction();
        hit.shade = shade;
        return true;

        // float a = A.x() - B.x();
        // float b = A.y() - B.y();
        // float c = A.z() - B.z();
        // float d = A.x() - C.x();
        // float e = A.y() - C.y();
        // float f = A.z() - C.z();
        // float g = r.direction().x();
        // float h = r.direction().y();
        // float i = r.direction().z();
        // float j = A.x() - r.origin().x();
        // float k = A.y() - r.origin().y();
        // float l = A.z() - r.origin().z();

        // float M = a * ((e* i) - (h * f)) + b * ((g * f) - (d * i)) + c * ((d * h) - (e * g));

        // float t = -(f * ((a * k) - (j * b)) + e * ((j * c) - (a * l)) + d * ((b * l) - (k * c))) / M;


        // if (t < tmin || t > tmax) {
        //     return false;
        // }

        // float gamma = (i * ((a * k) - (j * b)) + h * ((j * c) - (a * l)) + g * ((b * l) - (k * c))) / M;


        // if(gamma < 0 || gamma > 1) {
        //     return false;
        // }

        // float beta = (j * ((e * i) - (h * f)) + k * ((g * f) - (d * i)) + l * ((d * h) - (e * g))) / M;

        // if(beta < 0 || (beta > (1 - gamma))) {
        //     return false;
        // }
        
        // tmax = t;
        // hit.t = t;
        // vec3 u = B-A;
        // vec3 v = C-A;
        // hit.normal = -(u.cross(v).get_unit_vector());
        // hit.intersectPoint = r.at(t);
        // hit.viewDir = r.direction();
        // hit.shade = shade;
        // return true;
    }
};