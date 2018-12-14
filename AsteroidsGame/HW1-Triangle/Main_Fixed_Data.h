#pragma once
#include "Standard_Includes.h"
#include <glm/gtc/random.hpp>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "GameObject.h"
#include "Ship.h"
#include "Asteroid.h"

#pragma region Global Variables
//Window Settings
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //GLFW will automatically call this when window is resized and paramaters will be filled
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window, Ship *ship);
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
typedef Shader::LightSettings lightsettings;

//Camera 
Camera camera(vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

//Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Lighting
vec3 lightPos(1.2f, 1.0f, 2.0f);

//Predifine Methods
void SetLighting(Shader shader, GameObject objectList[]);
unsigned int LoadTexture(string path);
#pragma endregion