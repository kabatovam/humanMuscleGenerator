#include "ShaderManipulator.h"
#include "GLManipulator.h"

bool keyW, keyS, keyA, keyD;
double lastX, lastY;
GLfloat lastXoffset, lastYoffset;
GLfloat lastZoom;
bool mousePressed;
GLManipulator gm;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_movement_callback(GLFWwindow *window, double x, double y);
void scroll_callback(GLFWwindow *window, double x, double y);

int main()
{
	std::cout << "Starting GLFW context, OpenGL 4.0" << std::endl;
	// Init GLFW
	glfwInit();

	//attribute setup
	mousePressed = false;
	lastX = 0.0;
	lastY = 0.0;
	lastXoffset = 0;
	lastYoffset = 0;

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Muscle modeller", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	int version[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &version[0]); // Get back the OpenGL MAJOR version we are using  
	glGetIntegerv(GL_MINOR_VERSION, &version[1]);
	std::cout << "Using version OpenGL " << version[0] << "." << version[1] << std::endl;
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_movement_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	
	gm.initialize();

	

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//GLManipulator::paint() --recreates the paintGL function
		gm.paint();
		glfwSwapBuffers(window);
	}

	gm.~GLManipulator();
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		gm.stopAnimation();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		mousePressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		mousePressed = false;
	}
}

void mouse_movement_callback(GLFWwindow *window, double x, double y){
	if (mousePressed){
		GLfloat xoffset = x - lastX;
		GLfloat yoffset = y - lastY;
		gm.rotateCamera(xoffset, true, false);
		gm.rotateCamera(yoffset, false, true);
	}

	lastX = x;
	lastY = y;
}

void scroll_callback(GLFWwindow *window, double x, double y){
	if (y > lastZoom){
		gm.moveCamera("ZOOM_IN");
	}
	else if (y < lastZoom){
		gm.moveCamera("ZOOM_OUT");
	}
	
}