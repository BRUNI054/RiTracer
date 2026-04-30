#include "scene.hpp"
#include <vector>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class sceneLoader {
private:
    scene s;
    std::vector<float> vertexList;
    glm::vec3 light;
    int vertexCount;

public:
    sceneLoader(scene _s) {
        s = _s;
        vertexCount = 0;
    }

    void populateVertexList(int sphereDepth) {
        for (auto shape : s.getObjects()) {
            std::vector<float> temp = shape->returnVertices(sphereDepth);
            vertexCount += temp.size()/4;
            vertexList.insert(vertexList.end(), temp.begin(), temp.end());
        }
    }

    std::vector<float> getVertexList() {return vertexList;}
    glm::vec3 getLights() {return light;}

};