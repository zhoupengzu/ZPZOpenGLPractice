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

void practiceCLanguage();
void practiceTriangle();

int main(int argc, const char * argv[]) {
//    practiceCLanguage();
    practiceTriangle();
    return 0;
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
