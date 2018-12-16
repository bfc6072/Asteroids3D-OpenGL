#include "Main_Fixed_Data.h"

int main()
{
#pragma region Window and GLAD initialization
	//====Initialize glfw====
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Setting the GLFW version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Telling glfw to use core which alots a smaller subset of OpenGL features

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Barry's Engine", NULL, NULL); //Window object creation
	if (window == NULL) //Check if the window was created correctly
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	//====Create Viewport====
	//Call back if window is resized
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Tells GLFW we want to call this function on every window resize
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//====Initialize glad====
	//important because glad is used to manage function pointers for opengl
	//it needs to be initialized before using any of the opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Loading the correct OpenGL function pointer location to GLAD (specific to os)
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	srand(time(NULL));

#pragma endregion


#pragma region Render Setup
	//====Setting up rendering stuff====
	//Configure global opengl states
	glEnable(GL_DEPTH_TEST);

	//Build and compile shader
	Shader shader("VertexShader.vert", "FragmentShader.frag");
	int asteroidCount = 300;
	vector<Asteroid> asteroidList;
	vector<Bullet> bulletList;
	for (int i = 0; i < asteroidCount; i++)
	{
		asteroidList.push_back(Asteroid("resources/Ball.obj"));
	}
	
	Ship ship("resources/ship.obj");



	unsigned int crate_diffuse = LoadTexture("container.png");
	unsigned int crate_specular = LoadTexture("container_specular.png");
	unsigned int pinball_diffuse = LoadTexture("resources/Pinball.jpg");
	shader.StartPipelineProgram();
	shader.setInt("material.diffuse", 2); // or with shader class
	shader.setInt("material.specular", 1);
	SetLighting(shader, &asteroidList[0]);

	//Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crate_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, crate_specular);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, pinball_diffuse);
#pragma endregion

#pragma region Game Loop
	//====Game loop====
	while (!glfwWindowShouldClose(window)) //Check if the window is supposed to close
	{
		//per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input commands
		processInput(window, &ship, currentFrame, &bulletList);
		ship.fly();
		
		//Rendering commands
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//View/Projection/world transform
		mat4 projection = perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		vec3 eye = ship.getPosition();
		vec3 at = eye + ship.getDirection();
		vec3 up = ship.getVertical();
		mat4 view = glm::lookAt(eye, at, up);
		mat4 model = mat4(1.0f);
		shader.StartPipelineProgram(projection, view, model);
		shader.setVec3("viewPos", ship.getPosition());
		shader.setFloat("material.shininess", 32.0f);
		shader.setMat4("model", model);

		//Draw our Objects
		for (int i = 0; i < asteroidCount; i++)
		{
			Asteroid* obj = &asteroidList[i];
			obj->Move(deltaTime);
			obj->Rotate(deltaTime);
			model = mat4(1.0f);
			model = translate(model, obj->position);
			model[1][0] = ship.getSpeed() * 10.0f;// ship.getSpeed();
			shader.setMat4("model", model);
			obj->Draw(shader);

			/*if (length(obj->position - (ship.getPosition() + (ship.getDirection() * 4.8f))) < 3)
			{
				cout << "Should hit";
			}*/
			if ((int)currentFrame % 2 == 0)
			{
				if (obj->CheckCollision(ship))
				{
					asteroidList.erase(asteroidList.begin() + i);
					asteroidCount--;
				}

			}

			for (int k = 0; k < bulletList.size(); k++)
			{
				Bullet bullet = bulletList[k];
				if (obj->CheckBulletCollision(bulletList[k]))
				{
					asteroidList.erase(asteroidList.begin() + i);
					asteroidCount--;
					bulletList.erase(bulletList.begin() + k);
					ship.shooting = false;
				}
			}
		}

		for (int i = 0; i < bulletList.size(); i++)
		{
			Bullet* bullet = &bulletList[i];
			if (bullet->Fly(currentFrame))
			{
				bulletList.erase(bulletList.begin() + i);
				ship.shooting = false;
			}

			model = mat4(1.0f);
			model = translate(model, bullet->getPosition());
			shader.setMat4("model", model);
			bullet->Draw(shader);
		}
		model = mat4(1.0f);
		model = inverse(glm::lookAt(eye, at, up));
		
		shader.setMat4("model", model);
		ship.Draw(shader);
		
		//Check and call events | Buffer swapping
		glfwSwapBuffers(window);
		glfwPollEvents(); //Checks for events triggerd (Ex: keyboard or mouse input)
	}
	//After exiting the main loop we need to clean/delet all resources
	glfwTerminate();
#pragma endregion
	return 0;
}

#pragma region Helper/Utility Functions


/*
* Input method
*/
void processInput(GLFWwindow *window, Ship *ship, float time, vector<Bullet> *bulletList)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ship->setSpeed(deltaTime / 100); //camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ship->setSpeed(-deltaTime / 100); //camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ship->yaw(0.002f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ship->yaw(-0.002f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ship->pitch(0.01f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ship->pitch(-0.01f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ship->roll(-0.02f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ship->roll(0.02f);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !ship->shooting)
	{
		bulletList->push_back(Bullet("resources/Ball.obj", ship->getPosition(), ship->getDirection(), time));
		ship->Shoot();
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ship->teleport(vec3(0,0,0));
}

unsigned int LoadTexture(string path)
{
	//Loading in Texture
	unsigned int textureID;
	// texture 1
	// ---------
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// load image, create texture and generate mipmaps
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters & filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	return textureID;
}

void SetLighting(Shader shader, GameObject objectList[])
{
	lightsettings settings;

	// directional light
	shader.setVec3("dirLight.direction", vec3(-0.2f, -1.0f, -0.3f));
	shader.setVec3("dirLight.ambient", vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("dirLight.diffuse", vec3(0.4f, 0.4f, 0.4f));
	shader.setVec3("dirLight.specular", vec3(0.5f, 0.5f, 0.5f));
	// point light 1
	settings = { "pointLights[0]", objectList[3].position, vec3(0.5f, 0.5f, 0.5f),
				vec3(.2f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f };
	shader.setPointLight(settings);

	// point light 2
	settings.name = "pointLights[1]";
	settings.ambient = vec3(0.0f, 0.0f, .2f);
	settings.specular = vec3(1.0f, 1.0f, 1.f);

	settings.position = objectList[4].position;
	shader.setPointLight(settings);

	// point light 3
	settings.name = "pointLights[2]";
	settings.ambient = vec3(0.0f, .2f, 0.0f);
	settings.position = objectList[5].position;
	shader.setPointLight(settings);

	// point light 4
	settings.name = "pointLights[3]";
	settings.ambient = vec3(0.0f, 0.0f, 0.0f);
	settings.position = objectList[5].position;
	shader.setPointLight(settings);
	//spotLight
	shader.setPointLight(settings);
	shader.setVec3("spotLight.position", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setVec3("spotLight.ambient", vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("spotLight.diffuse", vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("spotLight.specular", vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09);
	shader.setFloat("spotLight.quadratic", 0.032);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}
#pragma endregion

#pragma region Callback Functions
/*
* Frame Call back method
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) //GLFW will automatically call this when window is resized and paramaters will be filled
{
	glViewport(0, 0, width, height);
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//	ship.yaw(xoffset);
//		//camera.ProcessMouseMovement(xoffset, yoffset);
//}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

//struct LightSettings
//{
//	vec3 position;
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//	float constant;
//	float linear;
//	float quadratic;
//};


#pragma endregion
