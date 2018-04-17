//
//  ZPZHelloWindow.cpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/17.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#include "ZPZHelloWindow.hpp"
#include <iostream>

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
