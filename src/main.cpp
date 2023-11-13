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
int windowWidth = 1500;
double xpos;
double ypos;
double prevx = 0;
double prevy = 0;
double dx = 0;
double dy = 0;

int res = 80;
int updateCount = 30;
int windowResized = 0;
int isMouseOnScreen = 0;
int isMouseLeftPressed = 0;
int isMouseRightPressed = 0;
int isMouseMiddlePressed = 0;
int isControlPressed = 1;
int brushPositionsX[] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
int brushPositionsY[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void cursor_enter_callback(GLFWwindow* wind, int entered);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void brush(Sim *sim);
void velocityBrush(Sim *sim);
void smokeBrush(Sim *sim);
void barrierBrush(Sim *sim);
void emptyBrush(Sim *sim);
int init();
Sim initSim(int res);
void resizeSim(int res, Sim *sim);
int main()
{
    if (init()){
        return -1;
    }
    Sim sim = initSim(res);

    double oldTimeSinceStart = 0;
    int iii = 0;
    while (!glfwWindowShouldClose(window))
    {
        double timeSinceStart = glfwGetTime();
        double deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (windowResized){
            resizeSim(res, &sim);
            windowResized = 0;
        }


//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        brush(&sim);

        sim.update(updateCount, deltaTime);

        sim.show();
//        std::cout << 1/deltaTime <<"\n";
//        std::cout<<sim.sampleField(windowHeight - ypos, xpos, 1)<<"\n";


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void resizeSim(int res, Sim *sim){
    float realH;
    float realW;
    realH = windowHeight/res;
    realH = windowHeight/realH;
    realW = windowWidth/(windowHeight/res);
    sim->resize(realH, realW);
}
Sim initSim(int res){
    float realH;
    float realW;
    realH = windowHeight/res;
    realH = windowHeight/realH;
    realW = windowWidth/(windowHeight/res);
    Sim sim = Sim(realH, realW);
    sim.o = 1.5;
    return sim;
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
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        isMouseMiddlePressed = 1;
    }else{
        isMouseMiddlePressed = 0;
    }

}
void brush(Sim *sim){
    if ( isMouseLeftPressed){
        velocityBrush(sim);
    }else if (isMouseRightPressed){
        smokeBrush(sim);
    }else if (isMouseMiddlePressed){
        if (isControlPressed){
            emptyBrush(sim);
        }else{
            barrierBrush(sim);
        }
    }
}
void velocityBrush(Sim *sim){
    for (int i = 0; i < 9; ++i) {
        sim->grid.getCell(bound(0, sim->grid.rows - 1,

                                sim->grid.rows -  ypos/sim->h - 1 + brushPositionsY[i]),

                          bound(0, sim->grid.cols - 1,

                                xpos/sim->h + brushPositionsX[i])).u = -1000 * dy;
        sim->grid.getCell(bound(0, sim->grid.rows - 1,
                                sim->grid.rows -  ypos/sim->h - 1 + brushPositionsY[i] ),
                          bound(0, sim->grid.cols - 1,
                                xpos/sim->h + brushPositionsX[i])).v = 1000 * dx;
    }
}

void smokeBrush(Sim *sim){
    for (int i = 0; i < 9; ++i) {
        sim->grid.getCell(bound(0, sim->grid.rows - 1,
                                sim->grid.rows - ypos / sim->h - 1 + brushPositionsY[i] ),
                          bound(0, sim->grid.cols - 1,
                                xpos / sim->h + brushPositionsX[i])).d = 2000;
    }
}
void barrierBrush(Sim *sim){
    for (int i = 0; i < 9; ++i) {
        sim->grid.getCell(bound(0, sim->grid.rows - 1,
                                sim->grid.rows - ypos / sim->h - 1 + brushPositionsY[i]),
                          bound(0, sim->grid.cols - 1,
                                xpos / sim->h + brushPositionsX[i] )).isSim = 0;
    }
}
void emptyBrush(Sim *sim){
    for (int i = 0; i < 9; ++i) {
        sim->grid.getCell(bound(1, sim->grid.rows - 2,
                                sim->grid.rows - ypos / sim->h - 1 + brushPositionsY[i]),
                          bound(1, sim->grid.cols - 2,
                                xpos / sim->h + brushPositionsX[i] )).isSim = 1;
    }
}

void framebuffer_size_callback(GLFWwindow* wind, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    windowResized = 1;
}
void processInput(GLFWwindow *wind)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(wind, true);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        isControlPressed = 1;
    }else{
        isControlPressed = 0;
    }

    if (isMouseOnScreen){

        glfwGetCursorPos(window, &xpos, &ypos);
        dx = xpos - prevx;
        dy = ypos - prevy;
        prevx = xpos;
        prevy = ypos;

    }

}