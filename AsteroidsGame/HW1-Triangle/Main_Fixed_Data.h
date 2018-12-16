/*
 Authors: Barrington Campbell & Kaloyana Mihova
 Class: IGME.309.03
 Proffesor: David Schwartz

 File Name: Main_Fixed_Data.h
 Description: Stores data neceassry to run the main program. Another level of abstraction to
			  clean up main.cpp.
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
//void mouse_callback(GLFWwindow* window, double xpos, double ypos); //Call back method for mouse movement
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); //Call back method for mouse scrolling
void processInput(GLFWwindow *window, Ship *ship, Menu *menu, float time, vector<Bullet> *bulletList); //Input processing for the Keyboard
const int WINDOW_WIDTH = 1920;			//Predifined screen width
const int WINDOW_HEIGHT = 1080;			//Predifined screen height
typedef Shader::LightSettings lightsettings;

//Camera 
Camera camera(vec3(0.0f, 0.0f, 3.0f));	//Game camera class
float lastX = WINDOW_WIDTH / 2.0f;		//Mouse location in X
float lastY = WINDOW_HEIGHT / 2.0f;		//Mouse location in Y
bool firstMouse = true;					//Mouse click check

//Collision
//Octree octree = Octree(vec3(0, 0, 0), 100.0f, 2);

//Timing
float deltaTime = 0.0f; //Change in time between frames for consistent calculations
float lastFrame = 0.0f; //Last frame used to calculate DeltaTime

//Lighting
vec3 lightPos(1.2f, 1.0f, 2.0f);

//Predifine Methods
void SetLighting(Shader shader, GameObject objectList[]); //Set the lighting params of multiple objects at once
unsigned int LoadTexture(string path); //Load in a new texture to be used in the shader
#pragma endregion