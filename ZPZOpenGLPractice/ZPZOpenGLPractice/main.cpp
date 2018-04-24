//
//  main.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/17.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include <iostream>
#include "ZPZHelloWindow.hpp"
#include "ZPZHelloTriangle.hpp"
#include "ZPZShaderPractice.hpp"
#include "ZPZTexturePractice.hpp"

void practiceCLanguage();
void practiceTriangle();
void shaderPractice();
void textturePractice();

int main(int argc, const char * argv[]) {
    textturePractice();
    return 0;
}

void textturePractice() {
    ZPZTexturePractice texture = ZPZTexturePractice("Textture");
    texture.textture();
}

void shaderPractice() {
    ZPZShaderPractice shader;
    shader.useBaseShaderForColor();
}

void practiceCLanguage() {
    ZPZHelloWindow window;
//    window.showWindowType();
    window.showWindow();
}

void practiceTriangle() {
    ZPZHelloTriangle triangle;
    triangle.showTwoTriangle();
}
