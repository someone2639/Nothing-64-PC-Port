#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(){
    // Initialise GLFW
    glewExperimental = 1; // Needed for core profile
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    GLFWwindow* window;
    window = glfwCreateWindow( 640, 480, "", NULL, NULL);
    if(window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental=1;
    if (glewInit() != GLEW_OK) return -1;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        extern void nothing();
        glClear( GL_COLOR_BUFFER_BIT );

        #define MAX_THREAD_COUNT 128
        #pragma omp parallel for
        for (int i = 0; i < MAX_THREAD_COUNT; i++) nothing();

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
}