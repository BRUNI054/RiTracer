#pragma once

#include "shape.hpp"



class triangle : public shape {
private:
    point a, b, c;
    std::shared_ptr<shader> shade;

public:
    triangle() : a(point(1.0f,0.0f,0.0f)), b(point(0.0f, 1.0f, 0.0f)), c(point(0.0f, 0.0f, 1.0f)) {}
    triangle(point a, point b, point c, std::shared_ptr<shader> shade) : a(a), b(b), c(c), shade(shade) {}

    bool intersect(const ray& r, const float tmin, float& tmax, hitStruct& h) override {
        float ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml, beta, gamma, t, M;
        ma = a.x() - b.x(); md = a.x() - c.x(); mg = r.direction().x();
        mb = a.y() - b.y(); me = a.y() - c.y(); mh = r.direction().y();
        mc = a.z() - b.z(); mf = a.z() - c.z(); mi = r.direction().z();
        mj = a.x() - r.origin().x(); 
        mk = a.y() - r.origin().y();
        ml = a.z() - r.origin().z();
        
        M = (ma*((me*mi)-(mh*mf))) + (mb*((mg*mf)-(md*mi))) + (mc*((md*mh)-(me*mg)));
        
        t = ((mf*((ma*mk)-(mj*mb))) + (me*((mj*mc)-(ma*ml))) + (md*((mb*ml)-(mk*mc))))/M;
        if (tmax < t || tmin > t){return false;}
        
        gamma = ((mi*((ma*mk)-(mj*mb))) + (mh*((mj*mc)-(ma*ml))) + (mg*((mb*ml)-(mk*mc))))/M;
        if (gamma < 0 || gamma > 1) {return false;}
        
        beta = ((mj*((me*mi)-(mh*mf))) + (mk*((mg*mf)-(md*mi))) + (ml*((md*mh)-(me*mg))))/M;
        if (beta < 0 || beta > (1-gamma)) {return false;}
        
        tmax = t;
        h.t = t;
        vec3 u = b-a;
        vec3 v = c-a;
        h.normal = -(u.cross(v).get_unit_vector());
        h.intersectPoint = r.at(t);
        h.viewDir = r.direction();
        h.shade = shade;
        return true;
    }
};