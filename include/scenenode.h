// Copyright Robert Dickerson 2014

#ifndef INCLUDE_SCENENODE_H_
#define INCLUDE_SCENENODE_H_

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>


// #include "Model.h"

namespace Hodhr {



class Model;
class SceneNode;
class Camera;

typedef std::vector<std::unique_ptr<SceneNode>> NodeVector;

class SceneNode {
 private:
Model* asset = NULL;

// std::weak_ptr<SceneNode> parent;

NodeVector children;

glm::vec3 position_;
glm::vec3 scale_;
glm::mat4 mvp_matrix_;
glm::mat4 mv_matrix_;
glm::mat3 normal_matrix_;

std::string name;

 public:
SceneNode(const std::string& name);

// SceneNode(const SceneNode&);
// SceneNode & operator=(const SceneNode &n);
        

virtual ~SceneNode();

void addChild(std::unique_ptr<SceneNode>  node);

void setAsset(Model* model);

//  glm::mat4 getMVMatrix() const;

glm::mat4 getMVPMatrix() const;

glm::mat3 getNormalMatrix() const;

//  glm::mat3 getNormalMatrix() const;

void setPosition(float x, float y, float z);

void setScale(float s);

void draw(void);

void updateLocal(const Camera& c);

void updateAll(const Camera& c);
};

}   //  namespace Hodhr

#endif  // INCLUDE_SCENENODE_H_
