#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <vector>
#include <map>
#include <string>

#include "Shader.h"


class ShaderLibrary
{

private:

    ShaderLibrary();
    ShaderLibrary(ShaderLibrary const& copy);
    ShaderLibrary& operator=(ShaderLibrary const& copy);

    //static ShaderLibrary *instance;

    std::map<std::string, Shader*> shaders;

public:

    static ShaderLibrary& getInstance()
    {
        static ShaderLibrary instance;
        return instance;
    }

    void addShader(std::string shaderName, std::string vertexShaderSrc, std::string fragmentShaderSrc);

    Shader* getShader(std::string shaderName);


    ~ShaderLibrary();



};

#endif
