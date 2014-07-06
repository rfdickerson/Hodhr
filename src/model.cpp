#include "Model.h"

namespace Hodhr {

Model::~Model()
{
    // Compulsory virtual destructor definition

}



void Model::setShader(Shader *s)
{
    this->shader = s;
}

}
