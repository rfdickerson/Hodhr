// Copyright Robert Dickerson 2014

#include "model.h"

namespace Hodhr {

  Model::~Model() {
    // Compulsory virtual destructor definition
  }



  void Model::setShader(Shader *s) {
    this->shader = s;
  }
  
}  // namespace Hodhr
