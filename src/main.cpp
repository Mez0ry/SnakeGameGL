#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"

#include "Window.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

#include "Color.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    if(!glfwInit()){
        // handle initialization error
    }

    Window window("Api test", 800, 800);

    window.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    window.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window.SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window.SetWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window.SetSelfAsContext();

    if (!window)
    {
        //std::cout << "Failed to create GLFW window" << std::endl;
        //glfwTerminate();
        return -1; 
    }

    window.SetKeyCallback([&](int key, int scancode, int action, int mode){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
            window.Close();
        }
    });

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        //std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    //std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    glViewport(0, 0, WIDTH, HEIGHT);

    float verticies[] ={
        -0.5f, -0.5f, /*texture:*/ 0.0f, 0.0f,
        0.5f, -0.5f,  /*texture:*/ 1.0f, 0.0f,
        0.5f, 0.5f,  /*texture:*/ 1.0f, 1.0f,

        -0.5f, 0.5f,  /*texture:*/ 0.0f, 1.0f,
    };
    
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("C:/Users/aleks/source/vscode_repos/SnakeGameOpengl/shader.shader");
    shader.UseShader();
    Texture texture("C:\\Users\\aleks\\source\\vscode_repos\\SnakeGameOpengl\\google.png");
    texture.Bind();
    Uniform::SetShaderUniformInt1(shader, "u_texture", 0);
    Uniform::SetShaderUniformFloat4(shader, "u_Color", 1, 0, 0, 1);

    VertexArray va;
    va.Bind();
    VertexBufferLayout vb_layout;
    vb_layout.Push<float>(2);
    vb_layout.Push<float>(2);

    va.AddBuffer(VertexBuffer(verticies, sizeof(verticies)), vb_layout);

    IndexBuffer ib(indicies, 6);

    Renderer renderer;

    float x{0}, y{};
    const float offset_factor = 0.01;

    while (!window.IsClosed())
    {
        //auto curr_time = glfwGetTime();

        renderer.SetClearColor(Color("#0e0d1f"));
        renderer.Clear();
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            y -= offset_factor;
            Uniform::SetShaderUniformFloat2(shader, "u_pos_offset", x, y);
        }
        shader.UseShader();

        texture.Bind();
        renderer.Render(va, ib, shader);
        renderer.SwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}