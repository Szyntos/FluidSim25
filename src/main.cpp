#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Primitives/Triangle.h"
#include "Primitives/Quad.h"
#include "Simulation/Grid.h"
#include "Simulation/Sim.h"
#include "utils/utils.h"
GLFWwindow* window;
int windowHeight = 1000;
int windowWidth = 1000;
double xpos;
double ypos;
int isMouseOnScreen = 0;
int isMousePressed = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void cursor_enter_callback(GLFWwindow* wind, int entered);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
int init();
int main()
{
    if (init()){
        return -1;
    }

//    Grid grid = Grid(50, 50);
    int h = 100;
    Sim sim = Sim(h, h);
    sim.o = 1.9;


    double oldTimeSinceStart = 0;
    while (!glfwWindowShouldClose(window))
    {
        double timeSinceStart = glfwGetTime();
        double deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;

        processInput(window);

        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        q.show();

//        grid.show();
        if (isMousePressed){

        }else{
            sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                             bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).d = 500;
        }

//        sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
//                         bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).d = 500;
        sim.show();
        std::cout<<deltaTime<<"\n";
        sim.update(deltaTime);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


int init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight,
                                          "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    return 0;
}
void cursor_enter_callback(GLFWwindow* wind, int entered)
{
    if (entered)
    {
        isMouseOnScreen = 1;
    }
    else
    {
        isMouseOnScreen = 0;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        isMousePressed = 1;
    }else{
        isMousePressed = 0;
    }

}


void framebuffer_size_callback(GLFWwindow* wind, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *wind)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(wind, true);
    if (isMouseOnScreen){
        glfwGetCursorPos(window, &xpos, &ypos);
    }

}