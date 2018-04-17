//
//  ZPZHelloWindow.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/17.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include "ZPZHelloWindow.hpp"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

ZPZHelloWindow::ZPZHelloWindow() {
    this -> windowType = 10;
}
// 使用初始化列表初始化参数
ZPZHelloWindow::ZPZHelloWindow(double type): windowType(type){
    
}

ZPZHelloWindow::~ZPZHelloWindow(){
    cout << "released" << endl;
}
// 带返回值的方法
string ZPZHelloWindow::getLocalIdentifier() {
    return "Identifier";
}

void ZPZHelloWindow::showWindowType() {
    cout << this -> windowType << endl;
}

void ZPZHelloWindow::showWindow() {
    // 初始化GLFW
    int initStatus = glfwInit();
    if (initStatus == GL_FALSE) {
        
        return;
    }
    // 使用glfwWindowHint配置GLFW，只能在主线程调用，第一个参数代表选项名称，第二个参数代表该选项的值
    // 下面两个设置OpenGL的版本，不过也可以不设置，采用的默认的即可
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 设置次版本号
    // 设置选用的配置文件的类型
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 设置是否可自定义尺寸
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 设置兼容性
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 创建窗口对象
    GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW Window" << endl;
        glfwTerminate();  // 终止
        return;
    }
    glfwMakeContextCurrent(window);
    // 设置用来管理OpenGL函数指针的GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        return;
    }
    // 视口
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, 400, 300);
    while (!glfwWindowShouldClose(window)) {  // 检查窗口是否被退出了，如果退出了，就跳出循环
        glfwPollEvents();  // 检查是否有触发的事件
        glfwSwapBuffers(window);  // 交换颜色缓冲
    }
    glfwTerminate();
}
