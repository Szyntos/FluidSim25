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
double prevx = 0;
double prevy = 0;
double dx = 0;
double dy = 0;
int isMouseOnScreen = 0;
int isMouseLeftPressed = 0;
int isMouseRightPressed = 0;
//Sim sim;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void cursor_enter_callback(GLFWwindow* wind, int entered);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void brush(Sim sim);
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
    int iii = 0;
    while (!glfwWindowShouldClose(window))
    {
        double timeSinceStart = glfwGetTime();
        double deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;

        processInput(window);

        glClearColor(0.5f, 0.0f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if ( isMouseLeftPressed){
            sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                             bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).u = 2000 * dx;
            sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                             bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).v = -2000 * dy;
        }else if (isMouseRightPressed){
            sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                             bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).d = 5000;
        }


//        if (iii % 100 == 0||1){
//            std::cout<<"=======================================================\n";
//        }
        iii ++;
        sim.update(10, deltaTime);

        sim.show();
//        std::cout<<sim.sampleField(xpos, windowHeight - ypos, 1)<<"\n";


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
        isMouseLeftPressed = 1;
    }else{
        isMouseLeftPressed = 0;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        isMouseRightPressed = 1;
    }else{
        isMouseRightPressed = 0;
    }

}
void brush(Sim sim){
    if (isMouseLeftPressed){
        sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                         bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).v = 5000;
    }else if (isMouseRightPressed){
        sim.grid.getCell(bound(0, sim.grid.cols - 1, xpos/sim.h),
                         bound(0, sim.grid.cols - 1, sim.grid.rows -  ypos/sim.h - 1)).d = 5000;
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
        dx = xpos - prevx;
        dy = ypos - prevy;
        prevx = xpos;
        prevy = ypos;

    }

}