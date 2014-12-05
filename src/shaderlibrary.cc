// Copyright Robert Dickerson 2014

// # <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cerrno>
#include <memory>
#include <utility>

#include "shaderlibrary.h"


namespace Hodhr {

ShaderLibrary::ShaderLibrary() { }


ShaderLibrary::~ShaderLibrary() {
  // cout << "Cleaning up shader library" << endl;
  fprintf(stderr, "Cleaning up shader library\n");
}


std::string loadFile(std::string filename)
{
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);

    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }

    throw(errno);
}

void ShaderLibrary::AddShader(std::string shaderName,
                              std::string vertexShaderSrc,
                              std::string fragmentShaderSrc) {

  // cout << "Added shader " << vertexShaderSrc << endl;
  string shaderSrc = loadFile(vertexShaderSrc);
  // cout << "Loaded " << shaderSrc << endl;
  // fprintf(stderr, "vertex shader %s", shaderSrc.c_str());

    const char *c_str = shaderSrc.c_str();

    GLuint vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsid, 1, &c_str, NULL);
    glCompileShader(vsid);

    shaderSrc = loadFile(fragmentShaderSrc);
     // fprintf(stderr, "fragment shader %s", shaderSrc.c_str());
    //  cout << "Loaded " << shaderSrc << endl;

    const char *cf_str = shaderSrc.c_str();

    GLuint fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsid, 1, &cf_str, NULL);
    glCompileShader(fsid);

    GLuint pId = glCreateProgram();
    glAttachShader(pId, vsid);
    glAttachShader(pId, fsid);

    glLinkProgram(pId);

    char logInfo[128];
    glGetProgramInfoLog(pId, 128, NULL, logInfo);
    // cout << "Compiled " << shaderName << endl;
    // cout << logInfo << endl;
    fprintf(stderr, "Compiled %s\n", shaderName.c_str());
    fprintf(stderr, "Compilation result: %s\n", logInfo);
    Shader* newShader = new Shader(shaderName, pId);

    newShader->getActiveUniforms();

    shaders_[std::string(shaderName)] = newShader;
}

Shader* ShaderLibrary::GetShader(std::string shader_name)
{
    return shaders_[shader_name];
}

}
