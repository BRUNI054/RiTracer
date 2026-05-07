#define TINYOBJLOADER_IMPLEMENTATION
#include "../src/tiny_obj_loader/tiny_obj_loader.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class objLoader {
    private:
    std::string filename;
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;
    std::vector<float> VBO_data;

    public:
    objLoader(std::string _filename, bool textured) {
        filename = _filename;
        if (!reader.ParseFromFile(filename, reader_config)) {
            if(!reader.Error().empty()) {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if(!reader.Warning().empty()) {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                std::vector<float> vertices;
                glm::vec3 normal = glm::vec3(0, 0, 0);
                glm::vec3 normalCheck = normal;
                std::vector<float> normals;
                std::vector<float> texCoords;
                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                    tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                    tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

                    tinyobj::real_t red   = 1.0f;
                    tinyobj::real_t green = 1.0f;
                    tinyobj::real_t blue  = 1.0f;

                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                        tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                        tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                        normals.push_back(nx);
                        normals.push_back(ny);
                        normals.push_back(nz);
                    }

                    if (idx.texcoord_index >= 0 && textured) {
                        tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                        tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                        texCoords.push_back(tx);
                        texCoords.push_back(ty);
                    }

                    // Optional: vertex colors
                    red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                    green = attrib.colors[3*size_t(idx.vertex_index)+1];
                    blue  = attrib.colors[3*size_t(idx.vertex_index)+2];

                    std::vector<float> temp = {vx, vy, vz, red, green, blue};
                    vertices.insert(vertices.end(), temp.begin(), temp.end());
                }
                if (normals.empty()) {
                    glm::vec3 edge1 = glm::vec3(vertices[6], vertices[7], vertices[8]) - glm::vec3(vertices[0], vertices[1], vertices[2]);
                    glm::vec3 edge2 = glm::vec3(vertices[12], vertices[13], vertices[14]) - glm::vec3(vertices[0], vertices[1], vertices[2]);
                    normal = glm::normalize(glm::cross(edge2, edge1));
                    for (size_t v = 0; v < fv; v++) {
                        normals.push_back(normal.x);
                        normals.push_back(normal.y);
                        normals.push_back(normal.z);
                    }
                }
                for (size_t v = 0; v < fv; v++) {
                    std::vector<float> withNormals = {vertices[v*6], vertices[(v*6) + 1], vertices[(v*6) + 2], -1*normals[v*3], -1*normals[(v*3) + 1], -1*normals[(v*3) + 2], vertices[(v*6) + 3], vertices[(v*6) + 4], vertices[(v*6) + 5]};
                    if(textured && !texCoords.empty()) withNormals.insert(withNormals.end(), texCoords.begin(), texCoords.end());
                    VBO_data.insert(VBO_data.end(), withNormals.begin(), withNormals.end());
                    
                }


                index_offset += fv;

                // per-face material
                shapes[s].mesh.material_ids[f];
            }
        }
    }

    std::vector<float> get_VBO_data() {return VBO_data;}
    

    
};