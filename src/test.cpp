#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float alpha = 0.2;
int main()
{
    int screen_width = 800;
    int screen_height = 600;
    class Window{
    public:
        GLFWwindow* window;
        int is_success;
        Window(int screen_width, int screen_height){
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window =
                glfwCreateWindow(screen_width, screen_height, "learn opengl", nullptr, nullptr);
            is_success = true;
            if (nullptr == window) {
                is_success = false;
                std::cout << "Failed to create glfw window" << std::endl;
                return;
            }
            glfwMakeContextCurrent(window);
        }
        ~Window()
        {
            if(is_success)
                glfwTerminate();
        }

    };

    Window cur_window(800, 600);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(cur_window.window, framebuffer_size_callback);

//    float vertices[] = {
//         0.5f,  0.5f, 0.0f, /*vertex point*/ 1.0f, 0.0f, 0.0f, /*color*/ 1.0f, 1.0f, /*texCoord*/
//         0.5f, -0.5f, 0.0f, /*vertex point*/ 0.0f, 1.0f, 0.0f, /*color*/ 1.0f, 0.0f, /*texCoord*/
//        -0.5f, -0.5f, 0.0f, /*vertex point*/ 0.0f, 0.0f, 1.0f, /*color*/ 0.0f, 0.0f, /*texCoord*/
//        -0.5f,  0.5f, 0.0f, /*vertex point*/ 1.0f, 1.0f, 0.0f, /*color*/ 0.0f, 1.0f /*texCoord*/
    //};
    
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                    GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                    GL_STATIC_DRAW);

        //描述的是当前绑定的GL_ARRAY_BUFFER的VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    glBindVertexArray(0);


    //获取当前opengl顶点着色器支持的顶点属性大小
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    const char* vertex_shader_src =
        "#version 330 core \n"
        "layout (location = 0) in vec3 aPos; \n"
        "layout (location = 1) in vec2 aTexCoord; \n"
        "out vec2 TexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 proj;\n"
        "void main() \n"
        "{\n"
        "   gl_Position = proj*view*model* vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
        "   TexCoord = aTexCoord; \n"
        "}\0";

    const char* fragment_shader_src =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D texture1;\n"
        "uniform sampler2D texture2;\n"
        "uniform float alpha;\n"
        "void main()\n"
        "{\n"
        "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), alpha) ;\n"
        "}\0";


    std::string container_pth = "/home/wy-zyw/work/opengl/opengl/resource/container.jpg";
    Texture texture1(container_pth);

    std::string face_pth = "/home/wy-zyw/work/opengl/opengl/resource/awesomeface.png";
    Texture texture2(face_pth, GL_RGBA);


    Shader shader(vertex_shader_src, fragment_shader_src, false);
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    shader.setFloat("alpha", alpha);

//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, (float)glfwGetTime()*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//    shader.setMat4("model", model);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    shader.setMat4("view", view);

    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), float(screen_width/screen_height), 0.1f, 100.0f);
    shader.setMat4("proj", proj);

    while (!glfwWindowShouldClose(cur_window.window)) {
        processInput(cur_window.window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.ID);

        shader.use(); 
        shader.setFloat("alpha", alpha);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime()*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);        
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);

        glfwSwapBuffers(cur_window.window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.ID);

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        alpha += 0.01f;
        if(alpha >= 1.0f)
            alpha = 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        alpha -= 0.01f;
        if(alpha <= 0.0f)
            alpha = 0.0f;
    }
}
