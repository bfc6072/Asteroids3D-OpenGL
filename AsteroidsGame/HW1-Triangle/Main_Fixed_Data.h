/*
 Authors: Barrington Campbell & Kaloyana Mihova
 Class: IGME.309.03
 Proffesor: David Schwartz

 File Name: Main_Fixed_Data.h
 Description: Stores data neceassry to run the main program. Another level of abstraction to
			  clean up  main.cpp.
*/


#pragma once
#include "Standard_Includes.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "GameObject.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Menu.h"
//#include "Octree.h"
#pragma region Global Variables
//Window Settings
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //GLFW will automatically call this when window is resized and paramaters will be filled
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window, Ship *ship, Menu *menu, float time, vector<Bullet> *bulletList);
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
typedef Shader::LightSettings lightsettings;

//Camera 
Camera camera(vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

//Collision
//Octree octree = Octree(vec3(0, 0, 0), 100.0f, 2);

//Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Lighting
vec3 lightPos(1.2f, 1.0f, 2.0f);

//Predifine Methods
void SetLighting(Shader shader, GameObject objectList[]);
unsigned int LoadTexture(string path);
#pragma endregion