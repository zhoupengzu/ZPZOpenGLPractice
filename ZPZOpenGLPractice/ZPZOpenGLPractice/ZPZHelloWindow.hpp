//
//  ZPZHelloWindow.hpp
//  ZPZOpenGLPractice
//
//  Created by zhoupengzu on 2018/4/17.
//  Copyright © 2018年 zhoupengzu. All rights reserved.
//

#ifndef ZPZHelloWindow_hpp
#define ZPZHelloWindow_hpp

#include <stdio.h>
#include <string>

using namespace std;

class ZPZHelloWindow {
public:
    ZPZHelloWindow();  // 定义构造函数
    ZPZHelloWindow(double type); // 携带一个参数的构造函数
    ~ZPZHelloWindow();  // 析构函数
    void showWindow(); // 定义一个无参的方法
    string getLocalIdentifier();
    void showWindowType();
private:
    double windowType;  // 私有成员变量
};

#endif /* ZPZHelloWindow_hpp */
