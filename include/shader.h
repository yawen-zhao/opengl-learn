#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader(const std::string vertex_path, const std::string fragmeng_path, bool read_from_file);

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif