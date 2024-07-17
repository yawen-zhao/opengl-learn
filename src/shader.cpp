#include "shader.h"

Shader::Shader(const std::string vertex_path, const std::string fragment_path, bool read_from_file)
{
    const char* v_shader_code;
    const char* f_shader_code;
    if(read_from_file)
    {
        std::string vs_code;
        std::string fs_code;
        std::ifstream vs_file;
        std::ifstream fs_file;

        vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try{
            vs_file.open(vertex_path);
            fs_file.open(fragment_path);
            std::stringstream vs_stream, fs_stream;
            vs_stream << vs_file.rdbuf();
            fs_stream << fs_file.rdbuf();

            vs_file.close();
            fs_file.close();

            vs_code = vs_stream.str();
            fs_code = fs_stream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        v_shader_code = vs_code.c_str();
        f_shader_code = fs_code.c_str();
    }
    else{
        v_shader_code = vertex_path.c_str();
        f_shader_code = fragment_path.c_str();
    }

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (bool)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), (float)value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
} 

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl \
            << infoLog << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl \
            << infoLog << std::endl;
        }
    }

}