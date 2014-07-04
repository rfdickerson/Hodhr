#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

//#include "Model.h"

class Model;
class SceneNode;
class Camera;

typedef std::vector<std::unique_ptr<SceneNode>> NodeVector;

class SceneNode
{
    private:

        Model* asset = NULL;

        // std::weak_ptr<SceneNode> parent;

        NodeVector children;

        glm::vec3 Position;
        
        glm::mat4 MVMatrix;
        glm::mat4 MVPMatrix;
        glm::mat3 NormalMatrix;

	std::string name;

    public:

        SceneNode(const std::string& name);

        // SceneNode(const SceneNode&);
        // SceneNode & operator=(const SceneNode &n);
        

        virtual ~SceneNode();

        void addChild(std::unique_ptr<SceneNode>  node);

        void setAsset(Model* model);

        //glm::mat4 getMVMatrix() const;

        glm::mat4 getMVPMatrix() const;

        //glm::mat3 getNormalMatrix() const;

	void setPosition(float x, float y, float z);

        void draw( void);

        void updateLocal(Camera& c);

        void updateAll(Camera& c);

};

#endif
