//
//  ZPZHelloTriangle.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/17.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include "ZPZHelloTriangle.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void ZPZHelloTriangle::showTriangle() {
    // 初始化GLFW
    glfwInit();
    // 配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 设置次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 创建窗口对象
    GLFWwindow * window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW Window" << endl;
        glfwTerminate();  // 终止
        return;
    }
    // 设置当前窗口为当前上下文
    glfwMakeContextCurrent(window);
    // 初始化GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return;
    }
    // 可视化窗口
    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // 顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    // 绑定VAO
    glBindVertexArray(VAO);
    
    // 顶点输入
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    // 生成顶点缓冲对象VBO，顶点缓冲对象用来管理发送到显卡上的数据的内存。生成一个独一无二的ID
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // 设置缓冲对象类型，顶点缓冲对象类型为GL_ARRAY_BUFFER，如果有多个不同的缓冲类型，都可以分开绑定上去
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 把之前定义的顶点数据复制到缓冲的内存中
    // 第四个参数表示希望显卡如何管理给定的数据：GL_STATIC_DRAW基本不会改变数据、GL_DYNAMIC_DRAW数据会改变很多、GL_STREAM_DRAW每次绘制时都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 编译着色器
    // 创建一个着色器对象
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // 片段着色器
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // 着色器程序 合并多个着色器
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 激活着色器程序对象
    glUseProgram(shaderProgram);
    
    // 删除编译着色器和片段着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 设置连接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}

void ZPZHelloTriangle::showTwoTriangle() {
    // 初始化GLFW
    glfwInit();
    // 配置版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 配置窗口是否可变
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 配置上下文
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 创建窗口对象
    GLFWwindow * window = glfwCreateWindow(800, 600, "Two Triangle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }
    // 将当前窗口设置为上下文
    glfwMakeContextCurrent(window);
    // GLEW
    glewExperimental = GLEW_OK;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return;
    }
    // 可视窗口
    GLsizei width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //图形渲染管线
    // 创建顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    // 绑定
    glBindVertexArray(VAO);
    
    // 顶点输入
    GLfloat vertex[] = {
       -1, 0, 0,
        0, 0, 0,
        -0.5, 1, 0,
        
        0, 0, 0,
        1, 0, 0,
        0.5, -1, 0,
    };
    // 管理顶点数据
    // 创建顶点缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // 绑定缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 添加数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    
    // 设置顶点连接属性 (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    
    // 顶点着色器
    GLuint veterxShader = glCreateShader(GL_VERTEX_SHADER);
    // 添加顶点着色器原码 (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
    glShaderSource(veterxShader, 1, &vertexShaderSource, NULL);
    // 编译顶点着色器
    glCompileShader(veterxShader);
    
    // 片段着色器
    GLuint fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 添加片段着色器原码
    glShaderSource(fragementShader, 1, &fragmentShaderSource, NULL);
    // 编译
    glCompileShader(fragementShader);
    
    // 着色器程序，用来管理着色器
    GLuint shaderPrograme = glCreateProgram();
    // 添加着色器
    glAttachShader(shaderPrograme, veterxShader);
    glAttachShader(shaderPrograme, fragementShader);
    // 连接
    glLinkProgram(shaderPrograme);
    // 激活
//    glUseProgram(shaderPrograme);
    
    // 删除着色器
    glDeleteShader(veterxShader);
    glDeleteShader(fragementShader);
    
    // 绘制
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // 背景色
        glClearColor(0, 0, 1.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        // 激活
        glUseProgram(shaderPrograme);
        // 绑定VAO
        glBindVertexArray(VAO);
        // 根据图元类型绘制
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // 交换缓冲
        glfwSwapBuffers(window);
    }
    
}
