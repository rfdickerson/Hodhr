#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Model.h"

class Model;
class SceneNode;

typedef std::vector<std::shared_ptr<SceneNode>> NodeVector;

class SceneNode
{
    private:

        std::shared_ptr<Model> asset;

        // std::weak_ptr<SceneNode> parent;

        NodeVector children;

        glm::vec4 Position;

        glm::mat4 MVMatrix;
        glm::mat4 MVPMatrix;
        glm::mat3 NormalMatrix;

    public:

        SceneNode();
        ~SceneNode();

        void addChild(std::shared_ptr<SceneNode> node);

        void setAsset(std::shared_ptr<Model> model);

        //glm::mat4 getMVMatrix() const;

        glm::mat4 getMVPMatrix() const;

        //glm::mat3 getNormalMatrix() const;

        void draw( void);

        void updateLocal();

        void updateAll();

};

#endif
