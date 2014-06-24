#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "Shader.h"

using namespace std;

class ShaderLibrary
{

    private:

    //static ShaderLibrary *instance;

    std::map<std::string, unique_ptr<Shader>> shaders;

public:


    ShaderLibrary();
    ShaderLibrary(ShaderLibrary const& copy) = delete;
    ShaderLibrary& operator=(ShaderLibrary const& copy) = delete;


    void addShader(std::string shaderName, std::string vertexShaderSrc, std::string fragmentShaderSrc);

    Shader* getShader(std::string shaderName);


    ~ShaderLibrary();



};

#endif
