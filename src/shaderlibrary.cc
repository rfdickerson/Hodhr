#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cerrno>
#include <memory>
#include <utility>

#include "shaderlibrary.h"

using namespace std;

namespace Hodhr {

ShaderLibrary::ShaderLibrary()
{


}


ShaderLibrary::~ShaderLibrary()
{
    cout << "Cleaning up shader library" << endl;
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

    throw (errno);
}

void ShaderLibrary::addShader(std::string shaderName, std::string vertexShaderSrc, std::string fragmentShaderSrc)
{

  //cout << "Added shader " << vertexShaderSrc << endl;
  string shaderSrc = loadFile(vertexShaderSrc);
  //cout << "Loaded " << shaderSrc << endl;

    const char *c_str = shaderSrc.c_str();

    GLuint vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsid, 1, &c_str, NULL);
    glCompileShader(vsid);

    shaderSrc = loadFile(fragmentShaderSrc);
    //  cout << "Loaded " << shaderSrc << endl;

    const char *cf_str = shaderSrc.c_str();

    GLuint fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsid, 1, &cf_str, NULL);
    glCompileShader(fsid);

    GLuint pId = glCreateProgram();
    glAttachShader(pId, vsid);
    glAttachShader(pId, fsid);

    glLinkProgram(pId);

    char logInfo[20];
    glGetProgramInfoLog(pId, 20, NULL, logInfo);
    cout << logInfo << endl;

    auto newShader = make_unique<Shader>(shaderName, pId);

    shaders[std::string(shaderName)] = move(newShader);

}

Shader* ShaderLibrary::getShader(std::string shaderName)
{
    return shaders[shaderName].get();

}

}
