#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "SceneNode.h"

/**
Pure virtual class for describing a model
**/

class SceneNode;

class Model
{
    public:
        virtual ~Model() {}
        virtual void init() = 0;
        virtual void draw(const SceneNode& n) = 0;

};

#endif
