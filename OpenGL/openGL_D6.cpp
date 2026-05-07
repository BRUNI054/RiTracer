#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../src/renderlib/sphere.hpp"
#include "../src/renderlib/vec3.hpp"

#include "GLSL.h"

#include <random>



int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

int main(void)
{
    
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 300;
    float aspectRatio = 1.0f; //16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;
    
    GLuint m_triangleVBO[1];
    
    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    std::vector<float> host_VertexBuffer {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 
        // 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        // 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 
        // 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        // -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        // -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        // 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
        // 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        // -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        // -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
        // -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        // 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
        // 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
        // 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        // -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        // 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        // -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f
    };
    int numBytes = host_VertexBuffer.size() * sizeof(float);

    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    host_VertexBuffer.clear();

    GLuint m_VAO;
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);

    // Create a shader using my GLSLObject class                                                                                                       
    sivelab::GLSLObject shader;
    shader.addShader( "vertexShader_prepFrag.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    shader.addShader( "fragmentShader_Lambertian.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.createProgram();

    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID, lightPosID, diffuseComponentID, camPosID;
    projMatrixID = shader.createUniform( "projMatrix" );
    viewMatrixID = shader.createUniform( "viewMatrix" );
    modelMatrixID = shader.createUniform( "modelMatrix" );
    normalMatrixID = shader.createUniform( "normalMatrix" );
    lightPosID = shader.createUniform( "lightPosWorld" );
    diffuseComponentID = shader.createUniform( "diffuseComponent" );
    camPosID = shader.createUniform( "cameraPosition" );

    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
    float halfWidth = 15.0 / 2.0;
    float halfHeight = halfWidth;

    float left = -halfWidth;
    float right = halfWidth;

    float bottom = -halfHeight;
    float top = halfHeight;

    float near = 0.1f;
    float far = 10000.0f;

    glm::mat4 M_ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);
    glm::mat4 M_persp = glm::perspective(glm::radians(60.0f), 1.0f, near, far);
    
    glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    glm::vec4 lightPos(1.0f, 1.0f, -5.0f, 0.0f);
    glm::vec3 diffuseComponent(0.0f, 1.0f, 0.0f);

    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis = std::uniform_real_distribution<float>(0.0001f, 0.25f * M_PI);


    float rotAngleX = 0;
    float rotAngleY = 0;

    float rotAngleDeceleration = M_PI/1000;
    float rotAngleXVelocity = dis(gen);
    float rotAngleYVelocity = dis(gen);
    float rotAngleYDeceleration;// = rotAngleDeceleration;
    float rotAngleXDeceleration;// = rotAngleDeceleration;

    float rotRatio = fmin((rotAngleYVelocity/rotAngleXVelocity), (rotAngleXVelocity/rotAngleYVelocity));

    if (rotAngleXVelocity - rotAngleYVelocity >= 0.0f) {
        std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
        rotAngleYDeceleration = rotRatio * rotAngleDeceleration;
        rotAngleXDeceleration = (1.0f-rotRatio) * rotAngleDeceleration;
        std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
    }
    else {
        std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
        rotAngleXDeceleration = rotRatio * rotAngleDeceleration;
        rotAngleYDeceleration = (1.0f-rotRatio) * rotAngleDeceleration;
        std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Poll for and process events */
        glfwPollEvents();

        float moveRatePerFrame = 0.25;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_pos = m_pos - m_W * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_pos = m_pos + m_W * moveRatePerFrame;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_pos = m_pos - m_U * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_pos = m_pos + m_U * moveRatePerFrame;
        }

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        std::cout << "fps: " << 1.0 / timeDiff << std::endl;
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            rotAngleXVelocity = dis(gen);
            rotAngleYVelocity = dis(gen);
            rotRatio = fmin((rotAngleYVelocity/rotAngleXVelocity), (rotAngleXVelocity/rotAngleYVelocity));

            if (rotAngleXVelocity - rotAngleYVelocity > 0.0f) {
                std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
                rotAngleYDeceleration = rotRatio * rotAngleDeceleration;
                rotAngleXDeceleration = (1.0f-rotRatio) * rotAngleDeceleration;
                std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;

            }
            else {
                std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
                rotAngleXDeceleration = rotRatio * rotAngleDeceleration;
                rotAngleYDeceleration = (1.0f-rotRatio) * rotAngleDeceleration;
                std::cout << rotAngleDeceleration << std::endl << rotAngleYDeceleration << std::endl << rotAngleXDeceleration << std::endl;
            }
        }

        // create the view matrix from our camera data                                                                                                   
        glm::mat4 M_view = glm::lookAt( m_pos, m_pos - m_W, m_V );

        // modify the model matrix for our triangle
        glm::mat4 modelRotateX = glm::rotate(glm::mat4(1.0), rotAngleX, glm::vec3(1, 0, 0));
        glm::mat4 modelRotateY = glm::rotate(glm::mat4(1.0), rotAngleY, glm::vec3(0, 1, 0));
        glm::mat4 modelRotate = modelRotateY * modelRotateX;
        glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -11));
        glm::mat4 modelScale = glm::scale(glm::mat4(1.0), {3.0f, 3.0f, 3.0f});
        glm::mat4 modelTransform = modelTranslate * modelRotate * modelScale;
        
        rotAngleXVelocity -= rotAngleDeceleration;
        rotAngleYVelocity -= rotAngleDeceleration;

        if (rotAngleXVelocity <= 0.0f) {
            rotAngleXVelocity = 0.0f;
        }
        if (rotAngleYVelocity <= 0.0f) {
            rotAngleYVelocity = 0.0f;
        }

        rotAngleX += rotAngleXVelocity;
        rotAngleY += rotAngleYVelocity;

        if (rotAngleXVelocity == 0.0f && rotAngleYVelocity == 0.0f) {
            float temp;
            temp = std::fmod(rotAngleX, M_PI/2);
            if (temp < M_PI/4) rotAngleX -= temp;
            else rotAngleX += ((M_PI/2)-temp);
            temp = std::fmod(rotAngleY, M_PI/2);
            if (temp < M_PI/4) rotAngleY -= temp;
            else rotAngleY += ((M_PI/2)-temp);
        }

        glm::mat4 normalTransform = glm::transpose(glm::inverse(modelTransform));

        /* Render your objects here */
        shader.activate();

        // copy from the host to the device the view matrix and the projection matrix                                                                                       
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( M_persp ));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr( M_view ));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr( modelTransform ));
        glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr( normalTransform ));

        glUniform4fv(lightPosID, 1, glm::value_ptr( lightPos ));
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr( diffuseComponent ));
        glUniform3fv(camPosID, 1, glm::value_ptr( m_pos ));

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        shader.deactivate();


        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
  
    glfwTerminate();
    return 0;
}
