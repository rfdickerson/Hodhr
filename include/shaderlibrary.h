#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "shader.h"

using namespace std;

namespace Hodhr {

class ShaderLibrary
{

    private:

    //static ShaderLibrary *instance;

    std::map<std::string, unique_ptr<Shader>> shaders_;

public:


    ShaderLibrary();
    ShaderLibrary(ShaderLibrary const& copy) = delete;
    ShaderLibrary& operator=(ShaderLibrary const& copy) = delete;


    void AddShader(std::string shader_name, std::string vs_src, std::string fs_src);

    Shader* GetShader(std::string shader_name) ;


    ~ShaderLibrary();



};

}

#endif
