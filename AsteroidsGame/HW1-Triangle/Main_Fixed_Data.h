#pragma once
#include "Standard_Includes.h"
#include <glm/gtc/random.hpp>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "GameObject.h"


#pragma region Global Variables
//Window Settings
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //GLFW will automatically call this when window is resized and paramaters will be filled
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
const int WINDOW_WIDTH = 800;
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

#pragma region Physics
#define number_of_objects 6 // Dont have this number be greater than 1000
#define EPSILON 0.00001
typedef struct Tree_Point
{
	float xpos, ypos;

}Tree_Point;

#pragma region program specific Data members

float timestep = 0.016f;
bool collision = false;
const int k = 2;
float min_x = -1.0f;
float min_y = -1.0f;
float max_x = 1.0f;
float max_y = 1.0f;

float min_x_2 = -1.0f;
float min_y_2 = -1.0f;

glm::vec3 tempVelocity;
glm::vec3 tempPosition;

float point_body_x[number_of_objects];
float point_body_y[number_of_objects];

float point_tree_x[number_of_objects];
float point_tree_y[number_of_objects];

struct VertexFormat
{
	glm::vec4 color;	// A vector4 for color has 4 floats: red, green, blue, and alpha
	glm::vec3 position;	// A vector3 for position has 3 float: x, y, and z coordinates

	// Default constructor
	VertexFormat()
	{
		color = glm::vec4(0.0f);
		position = glm::vec3(0.0f);
	}

	// Constructor
	VertexFormat(const glm::vec3 &pos, const glm::vec4 &iColor)
	{
		position = pos;
		color = iColor;
	}
};

// vector of scene bodies
std::vector<VertexFormat> lines;
std::vector<GameObject*> bodies;

//vectors for data-trees
std::vector<float> domain;
std::vector<float> range;
std::vector<Tree_Point> Points_Tree;
//std::vector<_Point_xy> Point_Coord;

//objects for data-trees
//VertexBuffer lineBuffer;
//Model* mesh;
Tree_Point point_temp;


#pragma endregion
#pragma endregion