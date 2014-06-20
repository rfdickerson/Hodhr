#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>

#include <glm/glm.hpp>

#include "Model.h"

class SceneNode
{
    private:

        Model* modelAsset;

        SceneNode* parent;

        std::vector<SceneNode*> children;

        glm::vec4 Position;

        glm::mat4 MVMatrix;
        glm::mat4 MVPMatrix;
        glm::mat3 NormalMatrix;

    public:

        SceneNode();
        ~SceneNode();


};

#endif
