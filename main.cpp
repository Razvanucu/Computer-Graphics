#if defined (__APPLE__)
    #define GLFW_INCLUDE_GLCOREARB
    #define GL_SILENCE_DEPRECATION
#else
    #define GLEW_STATIC
    #include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp> //core glm functionality
#include <glm/gtc/matrix_transform.hpp> //glm extension for generating common transformation matrices
#include <glm/gtc/matrix_inverse.hpp> //glm extension for computing inverse matrices
#include <glm/gtc/type_ptr.hpp> //glm extension for accessing the internal data structure of glm types

#include "Window.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"

#include <iostream>

// window
gps::Window myWindow;

// matrices
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat3 normalMatrix;

// light parameters
glm::vec3 lightDir;
glm::vec3 lightColor;

// shader uniform locations
GLint modelLoc;
GLint viewLoc;
GLint projectionLoc;
GLint normalMatrixLoc;
GLint lightDirLoc;
GLint lightColorLoc;

// camera
gps::Camera myCamera(
    glm::vec3(0.0f, 1.2f, 12.0f),
    glm::vec3(0.0f, 1.2f, -10.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));

GLfloat cameraSpeed = 0.1f;

GLboolean pressedKeys[1024];

// models
gps::Model3D ground;

gps::Model3D bench1;
gps::Model3D bench2;
gps::Model3D bench3;

gps::Model3D trash;

gps::Model3D lamppost1;
gps::Model3D lamppost2;
gps::Model3D lamppost3;
gps::Model3D lamppost4;

gps::Model3D treeLeaves1;
gps::Model3D treeLeaves2;
gps::Model3D treeLeaves3;
gps::Model3D treeLeaves4;
gps::Model3D treeLeaves5;
gps::Model3D treeLeaves6;
gps::Model3D treeLeaves7;
gps::Model3D treeLeaves8;
gps::Model3D treeLeaves9;
gps::Model3D treeLeaves10;
gps::Model3D treeLeaves11;
gps::Model3D treeLeaves12;
gps::Model3D treeLeaves13;
gps::Model3D treeLeaves14;
gps::Model3D treeLeaves15;
gps::Model3D treeLeaves16;
gps::Model3D treeLeaves17;
gps::Model3D treeLeaves18;
gps::Model3D treeLeaves19;
gps::Model3D treeLeaves20;
gps::Model3D treeLeaves21;
gps::Model3D treeLeaves22;
gps::Model3D treeLeaves23;
gps::Model3D treeLeaves24;
gps::Model3D treeLeaves25;
gps::Model3D treeLeaves26;
gps::Model3D treeLeaves27;

gps::Model3D treeTrunk1;
gps::Model3D treeTrunk2;
gps::Model3D treeTrunk3;
gps::Model3D treeTrunk4;
gps::Model3D treeTrunk5;
gps::Model3D treeTrunk6;
gps::Model3D treeTrunk7;
gps::Model3D treeTrunk8;
gps::Model3D treeTrunk9;
gps::Model3D treeTrunk10;
gps::Model3D treeTrunk11;
gps::Model3D treeTrunk12;
gps::Model3D treeTrunk13;
gps::Model3D treeTrunk14;
gps::Model3D treeTrunk15;
gps::Model3D treeTrunk16;
gps::Model3D treeTrunk17;
gps::Model3D treeTrunk18;
gps::Model3D treeTrunk19;
gps::Model3D treeTrunk20;
gps::Model3D treeTrunk21;
gps::Model3D treeTrunk22;
gps::Model3D treeTrunk23;
gps::Model3D treeTrunk24;
gps::Model3D treeTrunk25;
gps::Model3D treeTrunk26;

gps::Model3D stonesAndLeaves;


GLfloat angle;

//depth
GLuint shadowMapFBO;
GLuint depthMapTexture;
gps::Shader depthMapShader;
const unsigned int SHADOW_WIDTH = 2048;
const unsigned int SHADOW_HEIGHT = 2048;

// shaders
gps::Shader myBasicShader;
gps::Shader screenQuadShader;
gps::Model3D screenQuad;

//pointLight
glm::vec3 lightPos = glm::vec3(0.30915f, 1.8472f, 1.9974f);
glm::vec3 lightAttenuation = glm::vec3(1.0f, 1.2, 2.8);

//spotLight
float innerCutOff = 0.966;
float outerCutOff = 0.953;
int ifSpotLight = 1;

//solid mode shader
bool showSolid = false;

GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) {
		std::string error;
		switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	fprintf(stdout, "Window resized! New width: %d , and height: %d\n", width, height);
	
}
bool start_animation1 = false;
bool start_animation2 = false;
bool start_animation3 = false;
bool start_animation4 = false;
int wireframeView = 0;
bool showSceneFromLight = false;
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

	if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            pressedKeys[key] = true;
        } else if (action == GLFW_RELEASE) {
            pressedKeys[key] = false;
        }
    }

    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        start_animation1 = true;
    }

    if (key == GLFW_KEY_T && action == GLFW_PRESS) {

        

        switch (wireframeView)
        {
        case 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframeView = -1;
            break;
        default:
            break;
        }
        wireframeView += 1;
    }

    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        showSceneFromLight = !showSceneFromLight;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        ifSpotLight ^= 1;
        myBasicShader.useShaderProgram();
        glUniform1i(glGetUniformLocation(myBasicShader.shaderProgram, "ifSpotLight"), ifSpotLight);
    }
}
float yaw = 0;
float pitch = 0;
double x_pos_cursor = 0;
double y_pos_cursor = 0;
const float sensitivity = 0.024f;
bool first_mouse = false;
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!first_mouse) {
        x_pos_cursor = xpos;
        y_pos_cursor = ypos;
        first_mouse = true;
    }

    yaw = (-xpos + x_pos_cursor) * sensitivity;
    pitch = (-ypos + y_pos_cursor) * sensitivity;

    myCamera.rotate(pitch, yaw);

    myBasicShader.useShaderProgram();
    glUniformMatrix4fv(glGetUniformLocation(myBasicShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(myCamera.getViewMatrix()));
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

    x_pos_cursor = xpos;
    y_pos_cursor = ypos;
}

float anim_cnt = 0.0f;
float anim_angle = 0.0f;
void rotateLight() {
    glm::mat4 mat(1.0f);
    mat = glm::rotate(mat, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
    lightDir = glm::vec3(mat * glm::vec4(lightDir,1.0f));
    myBasicShader.useShaderProgram();
    lightDirLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightDir");
    // send light dir to shader
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));
    glCheckError();
}
void processMovement() {
	if (pressedKeys[GLFW_KEY_W]) {
         start_animation1 = false;
       start_animation2 = false;
       start_animation3 = false;
         start_animation4 = false;
         anim_cnt = 0.0f;
		myCamera.move(gps::MOVE_FORWARD, cameraSpeed);

        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));
        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	}

	if (pressedKeys[GLFW_KEY_S]) {
        start_animation1 = false;
        start_animation2 = false;
        start_animation3 = false;
        start_animation4 = false;
        anim_cnt = 0.0f;
		myCamera.move(gps::MOVE_BACKWARD, cameraSpeed);

        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	}

	if (pressedKeys[GLFW_KEY_A]) {
        start_animation1 = false;
        start_animation2 = false;
        start_animation3 = false;
        start_animation4 = false;
        anim_cnt = 0.0f;
        myCamera.move(gps::MOVE_LEFT, cameraSpeed);

        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));
        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	}

	if (pressedKeys[GLFW_KEY_D]) {
        start_animation1 = false;
        start_animation2 = false;
        start_animation3 = false;
        start_animation4 = false;
        anim_cnt = 0.0f;
		myCamera.move(gps::MOVE_RIGHT, cameraSpeed);
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));
        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	}

    if (pressedKeys[GLFW_KEY_Q]) {
        start_animation1 = false;
        start_animation2 = false;
        start_animation3 = false;
        start_animation4 = false;
        anim_cnt = 0.0f;
        angle -= 1.0f;
        model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));

        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
    }

    if (pressedKeys[GLFW_KEY_E]) {
        start_animation1 = false;
        start_animation2 = false;
        start_animation3 = false;
        start_animation4 = false;
        anim_cnt = 0.0f;
        angle += 1.0f;
        model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));

        normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
    }

    if (start_animation1) {
        myCamera.move(gps::MOVE_FORWARD, cameraSpeed/2);
        
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        anim_cnt += 0.01f;
        if (anim_cnt > 2.4f) {
            anim_cnt = 0.0f;
            start_animation1 = false;
            start_animation2 = true;
        }
    }

    if (start_animation2) {
        anim_angle = 0.3f;
        myCamera.rotate(0.0f , anim_angle);
        
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        anim_cnt += 0.01f;
        if (anim_cnt > 7.4f) {
            anim_cnt = 0.0f;
            start_animation2 = false;
            start_animation3 = true;
        }
    }

    if (start_animation3) {
        anim_angle = 0.3f;
        if (anim_cnt < 2.5f) {
            myCamera.rotate(-anim_angle, 0.0f);
        }
        myCamera.move(gps::MOVE_BACKWARD, cameraSpeed / 9);
        
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));


        anim_cnt += 0.01f;
        if (anim_cnt > 14.4f) {
            anim_cnt = 0.0f;
            start_animation3 = false;
            start_animation4 = true;
        }
    }

    if (start_animation4) {
        anim_angle = 0.3f;
        if (anim_cnt > 12.0f) {
            myCamera.rotate(anim_angle, 0.0f);
        }
        myCamera.move(gps::MOVE_FORWARD, cameraSpeed / 9);
        
        view = myCamera.getViewMatrix();
        myBasicShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
        glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));

        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));


        anim_cnt += 0.01f;
        if (anim_cnt > 14.4f) {
            anim_cnt = 0.0f;
            start_animation4 = false;
        }
    }

    glCheckError();
    if (pressedKeys[GLFW_KEY_B]) {
        rotateLight();
    }
    glCheckError();
}

void initOpenGLWindow() {
    myWindow.Create(1920, 1080, "OpenGL Project Core");
    glfwSetInputMode(myWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void setWindowCallbacks() {
	glfwSetWindowSizeCallback(myWindow.getWindow(), windowResizeCallback);
    glfwSetKeyCallback(myWindow.getWindow(), keyboardCallback);
    glfwSetCursorPosCallback(myWindow.getWindow(), mouseCallback);
}

void initOpenGLState() {
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glViewport(0, 0, myWindow.getWindowDimensions().width, myWindow.getWindowDimensions().height);
    glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
}

void initModels() {
    ground.LoadModel("models/ground/ground.obj");
    
    bench1.LoadModel("models/benchobj/bench1.obj");
    bench2.LoadModel("models/benchobj/bench2.obj");
    bench3.LoadModel("models/benchobj/bench3.obj");
    trash.LoadModel("models/benchobj/trash.obj");

    lamppost1.LoadModel("models/lampposts/lamppost1.obj");
    lamppost2.LoadModel("models/lampposts/lamppost2.obj");
    lamppost3.LoadModel("models/lampposts/lamppost3.obj");
    lamppost4.LoadModel("models/lampposts/lamppost4.obj");

    treeLeaves1.LoadModel("models/treeLeaves/treeLeaves1.obj");
    treeLeaves2.LoadModel("models/treeLeaves/treeLeaves2.obj");
    treeLeaves3.LoadModel("models/treeLeaves/treeLeaves3.obj");
    treeLeaves4.LoadModel("models/treeLeaves/treeLeaves4.obj");
    treeLeaves5.LoadModel("models/treeLeaves/treeLeaves5.obj");
    treeLeaves6.LoadModel("models/treeLeaves/treeLeaves6.obj");
    treeLeaves7.LoadModel("models/treeLeaves/treeLeaves7.obj");
    treeLeaves8.LoadModel("models/treeLeaves/treeLeaves8.obj");
    treeLeaves9.LoadModel("models/treeLeaves/treeLeaves9.obj");
    treeLeaves10.LoadModel("models/treeLeaves/treeLeaves10.obj");
    treeLeaves11.LoadModel("models/treeLeaves/treeLeaves11.obj");
    treeLeaves12.LoadModel("models/treeLeaves/treeLeaves12.obj");
    treeLeaves13.LoadModel("models/treeLeaves/treeLeaves13.obj");
    treeLeaves14.LoadModel("models/treeLeaves/treeLeaves14.obj");
    treeLeaves15.LoadModel("models/treeLeaves/treeLeaves15.obj");
    treeLeaves16.LoadModel("models/treeLeaves/treeLeaves16.obj");
    treeLeaves17.LoadModel("models/treeLeaves/treeLeaves17.obj");
    treeLeaves18.LoadModel("models/treeLeaves/treeLeaves18.obj");
    treeLeaves19.LoadModel("models/treeLeaves/treeLeaves19.obj");
    treeLeaves20.LoadModel("models/treeLeaves/treeLeaves20.obj");
    treeLeaves21.LoadModel("models/treeLeaves/treeLeaves21.obj");
    treeLeaves22.LoadModel("models/treeLeaves/treeLeaves22.obj");
    treeLeaves23.LoadModel("models/treeLeaves/treeLeaves23.obj");
    treeLeaves24.LoadModel("models/treeLeaves/treeLeaves24.obj");
    treeLeaves25.LoadModel("models/treeLeaves/treeLeaves25.obj");
    treeLeaves26.LoadModel("models/treeLeaves/treeLeaves26.obj");
    treeLeaves27.LoadModel("models/treeLeaves/treeLeaves27.obj");

    treeTrunk1.LoadModel("models/treeTrunks/treeTrunk1.obj");
    treeTrunk2.LoadModel("models/treeTrunks/treeTrunk2.obj");
    treeTrunk3.LoadModel("models/treeTrunks/treeTrunk3.obj");
    treeTrunk4.LoadModel("models/treeTrunks/treeTrunk4.obj");
    treeTrunk5.LoadModel("models/treeTrunks/treeTrunk5.obj");
    treeTrunk6.LoadModel("models/treeTrunks/treeTrunk6.obj");
    treeTrunk7.LoadModel("models/treeTrunks/treeTrunk7.obj");
    treeTrunk8.LoadModel("models/treeTrunks/treeTrunk8.obj");
    treeTrunk9.LoadModel("models/treeTrunks/treeTrunk9obj.obj");
    treeTrunk10.LoadModel("models/treeTrunks/treeTrunk10.obj");
    treeTrunk11.LoadModel("models/treeTrunks/treeTrunk11.obj");
    treeTrunk12.LoadModel("models/treeTrunks/treeTrunk12.obj");
    treeTrunk13.LoadModel("models/treeTrunks/treeTrunk13.obj");
    treeTrunk14.LoadModel("models/treeTrunks/treeTrunk14.obj");
    treeTrunk15.LoadModel("models/treeTrunks/treeTrunk15.obj");
    treeTrunk16.LoadModel("models/treeTrunks/treeTrunk16.obj");
    treeTrunk17.LoadModel("models/treeTrunks/treeTrunk17.obj");
    treeTrunk18.LoadModel("models/treeTrunks/treeTrunk18.obj");
    treeTrunk19.LoadModel("models/treeTrunks/treeTrunk19.obj");
    treeTrunk20.LoadModel("models/treeTrunks/treeTrunk20.obj");
    treeTrunk21.LoadModel("models/treeTrunks/treeTrunk21.obj");
    treeTrunk22.LoadModel("models/treeTrunks/treeTrunk22.obj");
    treeTrunk23.LoadModel("models/treeTrunks/treeTrunk23.obj");
    treeTrunk24.LoadModel("models/treeTrunks/treeTrunk24.obj");
    treeTrunk25.LoadModel("models/treeTrunks/treeTrunk25.obj");
    treeTrunk26.LoadModel("models/treeTrunks/treeTrunk26.obj");

    stonesAndLeaves.LoadModel("models/stonesAndLeaves/stonesAndLeaves.obj");
    screenQuad.LoadModel("models/quad/quad.obj");
}

void initShaders() {
	myBasicShader.loadShader(
        "shaders/basic.vert",
        "shaders/basic.frag");
    depthMapShader.loadShader("shaders/depthMap.vert", "shaders/depthMap.frag");
    screenQuadShader.loadShader("shaders/screenQuad.vert", "shaders/screenQuad.frag");
}
void initShadowFBO() {
    
    glGenFramebuffers(1, &shadowMapFBO); //generate shadow map buffer
    glGenTextures(1, &depthMapTexture); //generate texture for the shadow map
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    float borderColor[4] = { 1.0f,1.0f,1.0f,1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);


    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void initUniforms() {
	myBasicShader.useShaderProgram();

    
    model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	modelLoc = glGetUniformLocation(myBasicShader.shaderProgram, "model");

	
	view = myCamera.getViewMatrix();
	viewLoc = glGetUniformLocation(myBasicShader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    
    normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	normalMatrixLoc = glGetUniformLocation(myBasicShader.shaderProgram, "normalMatrix");

	
	projection = glm::perspective(glm::radians(45.0f),
                               (float)myWindow.getWindowDimensions().width / (float)myWindow.getWindowDimensions().height,
                               0.1f, 30.0f);
	projectionLoc = glGetUniformLocation(myBasicShader.shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));	

	
	lightDir = glm::vec3(0.0f, 10.0f, 10.0f);
	lightDirLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightDir");
	glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));

	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColorLoc = glGetUniformLocation(myBasicShader.shaderProgram, "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

}
glm::mat4 computeLightSpaceTrMatrix() {
    glm::mat4 lightView = glm::lookAt(lightDir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const GLfloat near_plane = 0.1f, far_plane = 33.0f;
    glm::mat4 lightProjection = glm::ortho(-7.0f, 7.0f, -7.0f, 7.0f, near_plane, far_plane);
    glm::mat4 lightSpaceTrMatrix = lightProjection * lightView;

    return lightSpaceTrMatrix;
}
void initUniformsPointLight() {

    myBasicShader.useShaderProgram();
    
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "cameraPositon"), 1, glm::value_ptr(myCamera.getPosition()));
    glUniform1f(glGetUniformLocation(myBasicShader.shaderProgram, "constantAttenuation"),lightAttenuation.x);
    glUniform1f(glGetUniformLocation(myBasicShader.shaderProgram, "linearAttenuation"),lightAttenuation.y);
    glUniform1f(glGetUniformLocation(myBasicShader.shaderProgram, "quadraticAttenuation"),lightAttenuation.z);
}
void initUniformSpotLight() {
    myBasicShader.useShaderProgram();

    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightPos"), 1, glm::value_ptr(myCamera.getPosition()));
    glUniform3fv(glGetUniformLocation(myBasicShader.shaderProgram, "spotLightDir"), 1, glm::value_ptr(myCamera.getDirection()));
    glUniform1f(glGetUniformLocation(myBasicShader.shaderProgram, "innerCutOff"), innerCutOff);
    glUniform1f(glGetUniformLocation(myBasicShader.shaderProgram, "outerCutOff"), outerCutOff);
    glUniform1i(glGetUniformLocation(myBasicShader.shaderProgram, "ifSpotLight"), ifSpotLight);
}
void renderGround(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    ground.Draw(shader);
}
void renderBenchTrash(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    bench1.Draw(shader);
    bench2.Draw(shader);
    bench3.Draw(shader);
    trash.Draw(shader);
}
void renderTreeLeaves(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    treeLeaves1.Draw(shader);
    treeLeaves2.Draw(shader);
    treeLeaves3.Draw(shader);
    treeLeaves4.Draw(shader);
    treeLeaves5.Draw(shader);
    treeLeaves6.Draw(shader);
    treeLeaves7.Draw(shader);
    treeLeaves8.Draw(shader);
    treeLeaves9.Draw(shader);
    treeLeaves10.Draw(shader);
    treeLeaves11.Draw(shader);
    treeLeaves12.Draw(shader);
    treeLeaves13.Draw(shader);
    treeLeaves14.Draw(shader);
    treeLeaves15.Draw(shader);
    treeLeaves16.Draw(shader);
    treeLeaves17.Draw(shader);
    treeLeaves18.Draw(shader);
    treeLeaves19.Draw(shader);
    treeLeaves20.Draw(shader);
    treeLeaves21.Draw(shader);
    treeLeaves22.Draw(shader);
    treeLeaves23.Draw(shader);
    treeLeaves24.Draw(shader);
    treeLeaves25.Draw(shader);
    treeLeaves26.Draw(shader);
    treeLeaves27.Draw(shader);
}
void renderTreeTrunks(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    treeTrunk1.Draw(shader);
    treeTrunk2.Draw(shader);
    treeTrunk3.Draw(shader);
    treeTrunk4.Draw(shader);
    treeTrunk5.Draw(shader);
    treeTrunk6.Draw(shader);
    treeTrunk7.Draw(shader);
    treeTrunk8.Draw(shader);
    treeTrunk9.Draw(shader);
    treeTrunk10.Draw(shader);
    treeTrunk11.Draw(shader);
    treeTrunk12.Draw(shader);
    treeTrunk13.Draw(shader);
    treeTrunk14.Draw(shader);
    treeTrunk15.Draw(shader);
    treeTrunk16.Draw(shader);
    treeTrunk17.Draw(shader);
    treeTrunk18.Draw(shader);
    treeTrunk19.Draw(shader);
    treeTrunk20.Draw(shader);
    treeTrunk21.Draw(shader);
    treeTrunk22.Draw(shader);
    treeTrunk23.Draw(shader);
    treeTrunk24.Draw(shader);
    treeTrunk25.Draw(shader);
    treeTrunk26.Draw(shader);

}
void renderLampPosts(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    lamppost1.Draw(shader);
    lamppost2.Draw(shader);
    lamppost3.Draw(shader);
    lamppost4.Draw(shader);
}
void renderStonesLeaves(gps::Shader shader, bool depthPass) {
    shader.useShaderProgram();

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glCheckError();
    if (!depthPass) {
        glUniformMatrix3fv(glGetUniformLocation(shader.shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    stonesAndLeaves.Draw(shader);
   
}
void drawObjects(gps::Shader shader,bool depthPass) {

    renderBenchTrash(shader, depthPass);
    renderLampPosts(shader, depthPass);
    renderTreeLeaves(shader, depthPass);
    renderTreeTrunks(shader, depthPass);
    renderStonesLeaves(shader, depthPass);
    renderGround(shader, depthPass);
}
void shadowPass() {

    depthMapShader.useShaderProgram();  
    glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "lightSpaceTrMatrix"),1,GL_FALSE,glm::value_ptr(computeLightSpaceTrMatrix()));
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER , shadowMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);
    drawObjects(depthMapShader, true);
    glCullFace(GL_FRONT);
    drawObjects(depthMapShader, true);
    //render back and front for solving Peter Panning
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCullFace(GL_BACK);// set back to culling the backface
    
 
}
void lightPass() {
   
    glViewport(0, 0, myWindow.getWindowDimensions().width, myWindow.getWindowDimensions().height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myBasicShader.useShaderProgram();

    view = myCamera.getViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    glUniform1i(glGetUniformLocation(myBasicShader.shaderProgram, "shadowMap"), 3);

    glUniformMatrix4fv(glGetUniformLocation(myBasicShader.shaderProgram, "lightSpaceTrMatrix"),
        1,
        GL_FALSE,
        glm::value_ptr(computeLightSpaceTrMatrix()));

    drawObjects(myBasicShader, false);


}
void showDepthMap() {
    glViewport(0, 0, myWindow.getWindowDimensions().width, myWindow.getWindowDimensions().height);

    glClear(GL_COLOR_BUFFER_BIT);

    screenQuadShader.useShaderProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    glUniform1i(glGetUniformLocation(screenQuadShader.shaderProgram, "depthMap"), 0);

    glDisable(GL_DEPTH_TEST);
    screenQuad.Draw(screenQuadShader);
    glEnable(GL_DEPTH_TEST);
}
void renderScene() {
    glCheckError();
    shadowPass();
    if (showSceneFromLight) {
        showDepthMap();
    }
    else {
           lightPass();
     }
}

void cleanup() {
    myWindow.Delete();
    //cleanup code for your own data
}

int main(int argc, const char * argv[]) {

    try {
        initOpenGLWindow();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    initOpenGLState();
	initModels();
	initShaders();
    initShadowFBO();
	initUniforms();
    initUniformsPointLight();
    initUniformSpotLight();
    setWindowCallbacks();

	glCheckError();
	// application loop
	while (!glfwWindowShouldClose(myWindow.getWindow())) {
        
        processMovement();
        
        renderScene();
		glfwPollEvents();
       
		glfwSwapBuffers(myWindow.getWindow());

		glCheckError();
	}

	cleanup();

    return EXIT_SUCCESS;
}
