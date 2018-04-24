//
//  ZPZTexturePractice.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/23.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include "ZPZTexturePractice.hpp"
#include <iostream>
#include <SOIL/SOIL.h>

const char * reviewVShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main() {\n"
"gl_Position = vec4(position, 1.0);\n"
"}";

const char * reviewFShaderSource = "#version 330 core\n"
"out vec4 outColor;\n"
"void main(){\n"
"outColor = vec4(0, 1, 0, 1);\n"
"}";

ZPZTexturePractice::ZPZTexturePractice(char * title) {
    this -> initWindow(title);
}

void ZPZTexturePractice::initWindow(char * title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    this -> window = glfwCreateWindow(800, 600, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        this -> window = nullptr;
        glfwTerminate();
        return;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

ZPZTexturePractice::~ZPZTexturePractice() {
    window = nullptr;
}

void ZPZTexturePractice::review() {
    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    typedef void (GLAPIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
    glShaderSource(vertexShader, 1, &reviewVShaderSource, nullptr);
    glCompileShader(vertexShader);
    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &reviewFShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 顶点
    GLfloat vertexPoints[] = {
      -0.5, -0.5, 0,
        0.5, -0.5, 0,
        0.5, 0.5, 0,
//        -0.5, 0.5,0,
    };
    // VAO,VBO
    GLuint vbo;
    // typedef void (GLAPIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
    glGenBuffers(1, &vbo);
    // typedef void (GLAPIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // typedef void (GLAPIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPoints), vertexPoints, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
const char * textureVShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 texCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main() {\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"
"TexCoord = texCoord;\n"
"}";
// sampler2D是采样器
const char * textureFShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"void main(){\n"
"color = texture(ourTexture, TexCoord);\n"
"}";
void ZPZTexturePractice::textture() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &textureVShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &textureFShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    // 纹理坐标：起于左下角（0，0），终止于右上角（1，1）
//    GLfloat texCoords[] = {
//      0.0,0,
//        1,0,
//        0.5,1,
//    };
    
    GLfloat vertexPoints[] = {
        //---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    GLuint indices[] = {
      0,1,3,
        1,2,3,
    };
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPoints), vertexPoints, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    // 生成纹理
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // 纹理过滤:线性和邻近过滤两种
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // 设置缩小时过滤类型为邻近过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // 设置放大时过滤类型为线性过滤
    // 多级渐远纹理 glGenerateMipmaps，只适用于纹理被缩小的情况下
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载和创建纹理，两种方法：1、选择一个需要的文件格式，自己写一个图像加载器，把图像转化为字节序列；2、使用一个支持多种流行格式的图像加载库来解决
    int sWidth, sHeight;
    // /Users/zhoupengzu/Desktop/ZPZOpenGLPractice/ZPZOpenGLPractice/ZPZOpenGLPractice/container.jpg
    unsigned char * image = SOIL_load_image("/Users/zhoupengzu/Desktop/ZPZOpenGLPractice/ZPZOpenGLPractice/ZPZOpenGLPractice/container.jpg", &sWidth, &sHeight, 0, SOIL_LOAD_RGB);
    cout << SOIL_last_result() << endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sWidth, sHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    //释放
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(program);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
