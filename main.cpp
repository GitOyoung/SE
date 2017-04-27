//
// Created by 欧阳建华 on 2017/4/25.
//

#include <string>
#include <se/string.h>
#include <iostream>

int main(int argc, char **argv)
{

    se::String string("Haha, what's your name");

    std::cout<<string.toStdString()<<std::endl;
    string.append("\tI'm Jake");
    std::cout<<string.toStdString()<<std::endl;
    string += "\tYes?";
    std::cout<<string.toStdString()<<std::endl;
    string -= 5;
    std::cout<<string.toStdString()<<std::endl;
    string.clear();
    string << 1;
    string << true;
    string << "Test";
    std::cout<<string.toStdString()<<std::endl;

    return 0;
}