#include "viewer_window.h"

ViewerWindow::ViewerWindow(Viewer& app, int width,int height):
    Window{
        app,
        width,
        height,
        "curveEdit",
        framebuffer_size_callback,
        cursor_position_callback,
        mouse_button_callback,
        key_callback,
        scroll_callback
    }
{

}


void ViewerWindow::update(core::App& app)
{
    Viewer& viewer = static_cast<Viewer&>(app);
    handleInput(mRawWindow, viewer);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
    //assert(editor->camera != nullptr);

 
    viewer->mCursor.computePosition(xpos, ypos, viewer->getWidth(), viewer->getHeight(), *(viewer->mCamera));


    if (viewer->mMousePressed) {
        if (!viewer->mMouseInit) {
            viewer->mMouseX = xpos;
            viewer->mMouseY = ypos;


            viewer->mMouseInit = true;
        }
        else {
            float dx = xpos - viewer->mMouseX;
            float dy = viewer->mMouseY - ypos;
            viewer->mMouseX = xpos;
            viewer->mMouseY = ypos;

        }
    }
    else {
        viewer->mMouseInit = false;
    }

 
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));



    if (button == GLFW_MOUSE_BUTTON_LEFT) {

        if (!viewer->mMousePressed) {
            viewer->mCurve.addPoint(viewer->mCursor.getPosition());
        }

        if (action == GLFW_PRESS) {
            viewer->mMousePressed = true;
        }
        else if (action == GLFW_RELEASE) {
            viewer->mMousePressed = false;
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));


    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        //viewer->toggleShader();
    }
}

void scroll_callback(GLFWwindow* window, double dx, double dy) {
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));

    viewer->mCamera->zoom(-dy);
}


void handleInput(GLFWwindow* window, Viewer& app) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_A) ==  GLFW_PRESS) {
        app.mCamera->translate(-0.001, 0.0, 0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        app.mCamera->translate(0.0,0.001,0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        app.mCamera->translate(0.0, -0.001, 0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        app.mCamera->translate(0.001, 0.0, 0.0);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        app.mCamera->reset(math::Vec3{0,0,1},1.0);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        app.mCursor.clampPosition();
    }


}
