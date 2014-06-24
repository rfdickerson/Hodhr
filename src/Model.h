#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "SceneNode.h"


/**
Pure virtual class for describing a model
**/

class Shader;
class SceneNode;

class Model
{

protected:

    Shader* shader;

public:

        // no copy
        //Model(const Model&) = delete;

        // no assign
        //Model& operator=(const Model&) = delete;

        //virtual ~Model() = default;
        //virtual ~Model();

        virtual void init() = 0;
        virtual void draw(const SceneNode& n) = 0;

        virtual void setShader(Shader *s) {
            this->shader = s;
        }
};

#endif
