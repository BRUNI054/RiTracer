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
    shader.addShader( "fragmentShader_BlinnPhong.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
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

    float near = 5.0f;
    float far = -5.0f;

    glm::mat4 M_ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);
    glm::mat4 M_persp = glm::perspective(glm::radians(60.0f), 1.0f, near, far);
    
    glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    glm::vec4 lightPos(0.0f, 0.0f, -12.0f, 0.0f);
    glm::vec3 diffuseComponent(0.0f, 1.0f, 0.0f);

    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis = std::uniform_real_distribution<float>(0.125f * M_PI, 0.25f * M_PI);


    float rotAngleX = 0;
    float rotAngleY = 0;
    // float rotAngleZ = 0;
    float rotAngleChangeChange = M_PI/1500;
    float rotAngleChangeX = dis(gen);
    float rotAngleChangeY = dis(gen);
    // float rotAngleChangeXChange;
    // float rotAngleChangeYChange;
    // if(rotAngleChangeX < rotAngleChangeY) {
    //     rotAngleChangeYChange = rotAngleChangeChange * (1-(rotAngleChangeX/rotAngleChangeY));
    //     rotAngleChangeXChange = rotAngleChangeChange * (rotAngleChangeX/rotAngleChangeY);
    // }
    // if(rotAngleChangeX > rotAngleChangeY) {
    //     rotAngleChangeXChange = rotAngleChangeChange * (1-(rotAngleChangeY/rotAngleChangeX));
    //     rotAngleChangeYChange = rotAngleChangeChange * (rotAngleChangeY/rotAngleChangeX);
    // }
    // else {
    //     rotAngleChangeXChange = rotAngleChangeChange * 0.5;
    //     rotAngleChangeYChange = rotAngleChangeChange * 0.5;
    // }
    // float rotAngleChangeZ = dis(gen);


    GLuint fboID, fboTextureID, fboRBOID;

    // Generate FBO
    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    // Create color texture attachment
    glGenTextures(1, &fboTextureID);
    glBindTexture(GL_TEXTURE_2D, fboTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb_width, fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTextureID, 0);

    // Create depth renderbuffer
    glGenRenderbuffers(1, &fboRBOID);
    glBindRenderbuffer(GL_RENDERBUFFER, fboRBOID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fb_width, fb_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fboRBOID);

    // Check FBO completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete!" << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);



    // You need a new piece of geometry for the screen filling quad
    // Note, it's only in 2D

    // =====================================================================
    // SCREEN-FILLING QUAD: For post-processing pass
    // =====================================================================
    GLuint screenQuadVBO, screenQuadVAO;
    
    // Screen quad vertices: (position xy, texcoord xy)
    std::vector<float> screenQuadVertices = {
        // positions        // texCoords
        -1.0f,  1.0f,        0.0f, 1.0f,  // Top Left (V0)
        -1.0f, -1.0f,        0.0f, 0.0f,  // Bottom Left (V1)
        1.0f,  1.0f,        1.0f, 1.0f,  // Top Right (V2)
        1.0f, -1.0f,        1.0f, 0.0f   // Bottom Right (V3)
    };

    glGenBuffers(1, &screenQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
    glBufferData(GL_ARRAY_BUFFER, screenQuadVertices.size() * sizeof(float), screenQuadVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &screenQuadVAO);
    glBindVertexArray(screenQuadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid *)(2 * sizeof(float)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Setup your post-processing filter shader here

    // =====================================================================
    // GAMMA CORRECTION POST-PROCESSING SHADER
    // =====================================================================
    sivelab::GLSLObject gammaShader;
    gammaShader.addShader("vertexShader_screenQuad.glsl", sivelab::GLSLObject::VERTEX_SHADER);
    gammaShader.addShader("fragmentShader_gammaCorrection.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
    gammaShader.createProgram();

    GLuint gammaTextureID = gammaShader.createUniform("fboTexture");
    GLuint gammaGammaID = gammaShader.createUniform("gamma");

    float gammaValue = 2.2f;  // Standard gamma value


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Get current framebuffer size for FBO viewport
        glfwGetFramebufferSize(window, &fb_width, &fb_height);

        // =====================================================================
        // PASS 1: Render scene to FBO
        // =====================================================================
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);  // <<<<<-----------
        glViewport(0, 0, fb_width, fb_height);
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
            rotAngleChangeX = dis(gen);
            rotAngleChangeY = dis(gen);
        }

        // create the view matrix from our camera data                                                                                                   
        glm::mat4 M_view = glm::lookAt( m_pos, m_pos - m_W, m_V );

        // modify the model matrix for our triangle
        glm::mat4 modelRotateX = glm::rotate(glm::mat4(1.0), rotAngleX, glm::vec3(1, 0, 0));
        glm::mat4 modelRotateY = glm::rotate(glm::mat4(1.0), rotAngleY, glm::vec3(0, 1, 0));
        // glm::mat4 modelRotateZ = glm::rotate(glm::mat4(1.0), rotAngleZ, glm::vec3(0, 0, 1));
        glm::mat4 modelRotate = 
        // modelRotateZ * 
        modelRotateY * modelRotateX;
        glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -15));
        glm::mat4 modelScale = glm::scale(glm::mat4(1.0), {3.0f, 3.0f, 3.0f});
        glm::mat4 modelTransform = modelTranslate * modelRotate * modelScale;
        
        rotAngleChangeX -= rotAngleChangeChange;
        rotAngleChangeY -= rotAngleChangeChange;
        // rotAngleChangeZ -= rotAngleChangeChange;

        if (rotAngleChangeX <= 0.0f) {
            rotAngleChangeX = 0.0f;
        }
        if (rotAngleChangeY <= 0.0f) {
            rotAngleChangeY = 0.0f;
        }
        // if (rotAngleChangeZ <= 0.0f) {
        //     rotAngleChangeZ = 0.0f;
        // }

        rotAngleX += rotAngleChangeX;
        rotAngleY += rotAngleChangeY;
        // rotAngleZ += rotAngleChangeZ;

        if (rotAngleChangeX == 0.0f && rotAngleChangeY == 0.0f 
            // && rotAngleChangeZ == 0.0f
        ) {
            float temp;
            temp = std::fmod(rotAngleX, M_PI/2);
            if (temp < M_PI/4) rotAngleX -= temp;
            else rotAngleX += ((M_PI/2)-temp);
            temp = std::fmod(rotAngleY, M_PI/2);
            if (temp < M_PI/4) rotAngleY -= temp;
            else rotAngleY += ((M_PI/2)-temp);
            // temp = std::fmod(rotAngleZ, M_PI/2);
            // if (temp < M_PI/4) rotAngleZ -= temp;
            // else rotAngleZ += ((M_PI/2)-temp);
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
        // glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }

        // =====================================================================
        // PASS 2: Render FBO texture to back buffer with gamma correction
        // =====================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Bind default framebuffer (back buffer)
        glViewport(0, 0, fb_width, fb_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Disable depth testing for the post-processing pass to ensure the
        // screen quad renders completely without depth conflicts with the
        // depth buffer from Pass 1 scene rendering
        glDisable(GL_DEPTH_TEST);
        
        gammaShader.activate();

        // Bind FBO color texture to texture unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fboTextureID);
        glUniform1i(gammaTextureID, 0);

        // Set gamma value
        glUniform1f(gammaGammaID, gammaValue);

        // Draw screen-filling quad
        glBindVertexArray(screenQuadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        gammaShader.deactivate();
        
        // Swap the front and back buffers
        glfwSwapBuffers(window);
    }
  
    glfwTerminate();
    return 0;
}
