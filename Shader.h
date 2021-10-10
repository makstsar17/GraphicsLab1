//
// Created by makstsar on 27.09.2021.
//

#ifndef LAB1_SHADER_H
#define LAB1_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    unsigned int program;
private:
    void checkErrors(unsigned int shader, std::string type);
};


#endif //LAB1_SHADER_H
