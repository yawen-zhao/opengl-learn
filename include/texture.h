#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class Texture 
{
public:
    unsigned int ID;
    int width;
    int height;
    int channels;
    unsigned char* data;
    bool is_loaded;

    Texture(const std::string texture_pth, int format=GL_RGB)
    {
        is_loaded = false;
        glGenTextures(1, &ID);
        std::cout << ID << std::endl;
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        data = stbi_load(texture_pth.c_str(), &width, &height, &channels, 0);
        stbi_set_flip_vertically_on_load(true);
        if (data)
        {
            is_loaded = true;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;        
        }
        //配置图片未填满区域颜色
    //    float border_color[] = {1.0f, 1.0f, 0.0f, 1.0f};
    //    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
     //   stbi_image_free(data);
    }

    ~Texture()
    {
        glDeleteTextures(1, &ID);
        if(data)
            stbi_image_free(data);
    }
};

#endif