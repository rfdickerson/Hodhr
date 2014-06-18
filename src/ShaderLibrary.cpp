#include <iostream>
#include <string>

#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
{


}


ShaderLibrary::~ShaderLibrary()
{

}

void ShaderLibrary::addShader(string vertexShaderSrc, string fragmentShaderSrc)
{

    cout << "Added shader " << vertexShaderSrc << endl;
}
