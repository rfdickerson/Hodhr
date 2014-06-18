#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <vector>
#include <map>
#include <string>

#include "Shader.h"

using namespace std;

class ShaderLibrary
{

private:
    
    ShaderLibrary();
    ShaderLibrary(ShaderLibrary const& copy);
    ShaderLibrary& operator=(ShaderLibrary const& copy);
    
    //static ShaderLibrary *instance;

    map<string, Shader> shaders;

public:

    static ShaderLibrary& getInstance()
    {
        static ShaderLibrary instance;
        return instance;
    }

    void addShader(string vertexShaderSrc, string fragmentShaderSrc);


    ~ShaderLibrary();



};

#endif
