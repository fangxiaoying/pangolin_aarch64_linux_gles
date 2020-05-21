#include <pangolin/platform.h>
#include <pangolin/display/display.h>
#include <pangolin/display/display_internal.h>
#include <pangolin/factory/factory_registry.h>

//#include <pangolin/gl/gldraw.h>



#ifdef HAVE_PYTHON
#include <pangolin/python/pyinterpreter.h>
#include <pangolin/console/ConsoleView.h>
#endif // HAVE_PYTHON

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <mutex>
#include <cstdlib>

#include <GLFW/glfw3.h>


//#include <pangolin/window_frameworks.h>
#define GLFW_VERSION_GE(MAJ, MIN) GLFW_VERSION_MAJOR >= MAJ && GLFW_VERSION_MINOR >= MIN

namespace pangolin {
    

extern __thread PangolinGl* context;

struct GLFWWaylandWindow : public PangolinGl {
    GLFWWaylandWindow(const std::string& title, const int width, const int height, const bool offscreen = false);
    ~GLFWWaylandWindow() override;
    void ToggleFullscreen() override;
    void Move(int x, int y) override;
    void Resize(unsigned int w, unsigned int h) override;
    void MakeCurrent() override;
    void RemoveCurrent() override;
    void SwapBuffers() override;
    void ProcessEvents() override;

    GLFWwindow* window;

};



static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


GLFWWaylandWindow::GLFWWaylandWindow(const std::string& title, const int width, const int height, const bool offscreen){
        //CreateGLFWWindow
    windowed_size[0] = width;
    windowed_size[1] = height;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

#ifndef HAVE_GLES_2
    printf("Error:   not found GLES v2    ! \n");
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    // default offscreen is false,  if not full screen, should not set GLFW_VISIBLE as GLFW_FALSE
    if(offscreen) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }
    //create glfw window
    window = glfwCreateWindow(width, height, "Pangolin GLFW", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
        printf("Error:   can not create glfw window    ! \n");
        return ;
    }
   

}


GLFWWaylandWindow::~GLFWWaylandWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}


void GLFWWaylandWindow::ToggleFullscreen(){
    std::cout << "GLFWWaylandWindow::ToggleFullscreen is not Implemented !" << std::endl;

}

void GLFWWaylandWindow::ProcessEvents(){
    glfwPollEvents();
}

void GLFWWaylandWindow::SwapBuffers(){
    glfwSwapBuffers(window);
}


void GLFWWaylandWindow::MakeCurrent() {
    glfwMakeContextCurrent(window);
    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
    context = this;
}

void GLFWWaylandWindow::RemoveCurrent() {
    glfwMakeContextCurrent(nullptr);
}

void GLFWWaylandWindow::Move(int x, int y) {
    glfwSetWindowPos(window, x, y);
}

void GLFWWaylandWindow::Resize(unsigned int w, unsigned int h) {
     glfwSetWindowSize(window, w, h);
}



std::unique_ptr<WindowInterface> CreateGLFWWindowAndBind(const std::string& window_title, const int w, const int h, const bool offscreen = false) {
    return std::unique_ptr<WindowInterface>(new GLFWWaylandWindow(window_title, w, h, offscreen));
}


PANGOLIN_REGISTER_FACTORY(GLFWWindow) {
    struct GLFWWindowFactory : public FactoryInterface<WindowInterface> {
        std::unique_ptr<WindowInterface> Open(const Uri& uri) override {

            const std::string window_title = uri.Get<std::string>("window_title", "window");
            const int w = uri.Get<int>("w", 640);
            const int h = uri.Get<int>("h", 480);
            const bool offscreen = uri.Get<int>("offscreen", false);
            return std::unique_ptr<WindowInterface>(CreateGLFWWindowAndBind(window_title, w, h, offscreen));
        }
    
};

    auto factory = std::make_shared<GLFWWindowFactory>();
    FactoryRegistry<WindowInterface>::I().RegisterFactory(factory, 10, "wayland");
    FactoryRegistry<WindowInterface>::I().RegisterFactory(factory, 9,  "linux");
    FactoryRegistry<WindowInterface>::I().RegisterFactory(factory, 20,  "default");
}

}


