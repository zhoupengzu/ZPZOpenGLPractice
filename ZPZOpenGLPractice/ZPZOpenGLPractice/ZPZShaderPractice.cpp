//
//  ZPZShaderPractice.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/18.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include "ZPZShaderPractice.hpp"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// 让顶点着色器给片段着色器传递颜色

// 顶点着色器原码字符串
const char * vertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"color = vec4(1, 0, 0, 1);\n"
"}\0";

// 片段着色器
const char * fragmentSource = "#version 330 core\n"
"in vec4 color;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"vertexColor = color;\n"
"}\0";

const char * uniformVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main() {\n"
"gl_Position = vec4(position, 1.0);\n"
"}";

const char * uniformFragmentShader = "#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec4 ourColor;\n"
"void main(){\n"
"fragColor = ourColor;\n"
"}";

void ZPZShaderPractice::useBaseShader() {
    // 初始化glfw
    glfwInit();
    // 配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 配置窗口是否可变
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 配置上下文
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 初始化窗口
    GLFWwindow * window = glfwCreateWindow(800, 600, "Shader", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }
    // 设置上下文
    glfwMakeContextCurrent(window);
    // GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return;
    }
    // 可视窗口
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // 设置顶点数据
    GLfloat vertexs[] = {
      -1, -1, 0,
        1, -1, 0,
        0, 1, 0
    };
    
    // 顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    // 绑定
    glBindVertexArray(VAO);
    
    // 顶点缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // 绑定
    /**
     * 第一个参数：缓冲类型，顶点对象的缓冲类型是固定的
     */
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // 复制数据 (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    /**
     * target：目标缓冲类型
     * size：数据大小
     * data: 传输的数据
     * usage:指定显卡管理数据的方式:GL_STATIC_DRAW、GL_DYNAMIC_DRAW、GL_STREAM_DRAW
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
    
    // 设置顶点连接属性 (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    /**
     * index:要配置的顶点属性
     * size:顶点属性大小，即有几个分量（和GLSL有关）
     * type:数据类型
     * normalized:是否希望把顶点数据标准化，如果设置为是，则会被影射到-1到1之间，因为我们提供的就是标准化的数据了，所以不需要
     * stride:步长
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    // 激活连接属性
    glEnableVertexAttribArray(0);
    
    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 添加顶点着色器代码(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
    /**
     * count: 原码字符串个数
     * string：原码字符串
     */
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // 编译
    glCompileShader(vertexShader);
    
    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    // 着色器程序
    GLuint programe = glCreateProgram();
    glAttachShader(programe, vertexShader);
    glAttachShader(programe, fragmentShader);
    glLinkProgram(programe);
    
    glUseProgram(programe);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // 设置背景色
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programe);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}

void ZPZShaderPractice::useUniform() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow * window = glfwCreateWindow(800, 600, "Uniform", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 原码 (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
    glShaderSource(vertexShader, 1, &uniformVertexShader, NULL);
    glCompileShader(vertexShader);
    
    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &uniformFragmentShader, NULL);
    glCompileShader(fragmentShader);
    
    // 着色程序
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
//    glUseProgram(program);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 图形渲染管线
    GLfloat vertexs[] = {
        -1, -1, 0,
        0, -1, 0,
        0, 1, 0
    };
    
    // VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint VBO;
    // (GLsizei n, GLuint* buffers)
    glGenBuffers(1, &VBO);
    // (GLenum target, GLuint buffer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
    
    //(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(program, "ourColor");
        glUniform4f(vertexColorLocation, 0, greenValue, 0, 1);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    
}

const char * colorVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main(){\n"
"gl_Position = vec4(position, 1);\n"
"ourColor = color;\n"
"}";

const char * colorFragmentShader = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec3 color;\n"
"void main(){\n"
"color = ourColor;\n"
"}";

void ZPZShaderPractice::useBaseShaderForColor() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow * window = glfwCreateWindow(800, 600, "color", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
    glShaderSource(vertexShader, 1, &colorVertexShader, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &colorFragmentShader, NULL);
    glCompileShader(fragmentShader);
    
    GLuint progrem = glCreateProgram();
    glAttachShader(progrem, vertexShader);
    glAttachShader(progrem, fragmentShader);
    glLinkProgram(progrem);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLfloat vertices[] = {
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    // (GLuint index);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(progrem);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
}
