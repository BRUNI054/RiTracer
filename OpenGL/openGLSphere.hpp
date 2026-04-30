#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"
    
class openGLSphere {
private:  
    float radius;


    void splitTriangles(int depth, std::vector<glm::vec3> triangles) {
            if(depth > 0) {    
                std::vector<glm::vec3> tempTriangles;
                for (int i=0; i<triangles.size(); i++) {
                glm::vec3 M0 = (triangles[i+1] - triangles[i]) / 2.0f;
                M0 = glm::normalize(M0) * radius;
                glm::vec3 M1 = (triangles[i+2] - triangles[i+1]) / 2.0f;
                M1 = glm::normalize(M1) * radius;
                glm::vec3 M2 = (triangles[i+2] - triangles[i]) / 2.0f;
                M2 = glm::normalize(M2) * radius;
                // glm::vec3 N0 = glm::normalize(glm::cross(M2-triangles[i], M0-triangles[i]));
                // glm::vec3 N1 = glm::normalize(glm::cross(M1-M0, triangles[i-1]-M0));
                // glm::vec3 N2 = glm::normalize(glm::cross(triangles[i+2]-M2, M1-M2));
                tempTriangles.push_back(triangles[i]);
                tempTriangles.push_back(M2);
                tempTriangles.push_back(M0);
                // tempTriangles.push_back(N0);
                tempTriangles.push_back(M0);
                tempTriangles.push_back(M1);
                tempTriangles.push_back(triangles[i+1]);
                // tempTriangles.push_back(N1);
                tempTriangles.push_back(M2);
                tempTriangles.push_back(triangles[i+2]);
                tempTriangles.push_back(M1);
                // tempTriangles.push_back(N2);
            }
            triangles = tempTriangles;
            depth -= 1;
            splitTriangles(depth, triangles);
        }
        return;
    }

    std::vector<float> returnVertices(int sphereDepth) {
        float phi = (1.0f + sqrt(5.0f))/2.0f;
        float temp = radius/(sqrt(1+pow(phi, 2.0f)));
        std::vector<glm::vec3> v = {
                temp*glm::vec3(0, 1, phi), temp*glm::vec3(0, -1, phi), temp*glm::vec3(0, 1, -phi), temp*glm::vec3(0, -1, -phi), 
                temp*glm::vec3(1, phi, 0), temp*glm::vec3(-1, phi, 0), temp*glm::vec3(1, -phi, 0), temp*glm::vec3(-1, -phi, 0),
                temp*glm::vec3(phi, 0, 1), temp*glm::vec3(-phi, 0, 1), temp*glm::vec3(phi, 0, -1), temp*glm::vec3(-phi, 0, -1)
                };
        std::vector<glm::vec3> triangles = {
                                        v[0], v[1], v[8], v[0], v[1], v[9], v[0], v[4], v[5], v[0], v[4], v[8],
                                        v[0], v[5], v[9], v[1], v[6], v[7], v[1], v[6], v[8], v[1], v[7], v[9],
                                        v[2], v[3], v[10], v[2], v[3], v[11], v[2], v[4], v[5], v[2], v[4], v[10],
                                        v[2], v[5], v[11], v[3], v[6], v[7], v[3], v[6], v[10], v[3], v[7], v[11],
                                        v[4], v[8], v[10], v[5], v[9], v[11], v[6], v[8], v[10], v[7], v[9], v[11]
                                        };
        
        splitTriangles(sphereDepth, triangles);
        std::vector<float> temp2;
        for(glm::vec3 triangle : triangles) {
            temp2.push_back(triangle.x());
            temp2.push_back(triangle.y());
            temp2.push_back(triangle[0].z());
            temp2.push_back(triangle[1].x());
            temp2.push_back(triangle[1].y());
            temp2.push_back(triangle[1].z());
            temp2.push_back(triangle[2].x());
            temp2.push_back(triangle[2].y());
            temp2.push_back(triangle[2].z());
            temp2.push_back(triangle[3].x());
            temp2.push_back(triangle[3].y());
            temp2.push_back(triangle[3].z());
        }
        return temp2;
    }
}