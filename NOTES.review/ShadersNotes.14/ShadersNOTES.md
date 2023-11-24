### Going over Shaders and how they work with Vertex Buffers

## Vertex Buffer
- Essentially vertex buffer, and vertex data are information used to tell renderers where they want to draw things on the screen

### Shaders
Vertex Shaders
- Essentially render shaders per vertex data
Fragment Shaders
- Essentially render shaders per pixel.


### Errors That causes segfault!!!
- Meaning that these are what can be causing errors or things causing segfaults!!!!

- When using glad make sure to have
gladLoadGL() just after 
int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
And make these two lines after we call glfwMakeContextCurrent(GLFWwindow* window) function call!

-  And call these 
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

just after we create GLFWwindow.

NOTE: Rule of thumb if the shaders or opengl segfaults, even though everythings supposed to work, check to see if everything is initialized before being used!!!