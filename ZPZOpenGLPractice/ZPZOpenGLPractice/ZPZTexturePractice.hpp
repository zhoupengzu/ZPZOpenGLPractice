//
//  ZPZTexturePractice.hpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/23.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#ifndef ZPZTexturePractice_hpp
#define ZPZTexturePractice_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class ZPZTexturePractice {
public:
    ZPZTexturePractice(char * title);
    ~ZPZTexturePractice();
    void review();
    void textture(); // 纹理
private:
    GLFWwindow * window;
    void initWindow(char * title);
};

#endif /* ZPZTexturePractice_hpp */
