#include <utility>
#include <memory>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "SceneNode.h"
#include "Model.h"
#include "Camera.h"

using namespace std;

SceneNode::SceneNode (const std::string& name)
{
  this->name = name;
  this->asset = NULL;
}

SceneNode::~SceneNode()
{



}

void SceneNode::draw()
{
    
  //cout << "drawing node " << name << endl;
  if (asset) 
    {
      cout << "drawing asset in " << name << endl;
      asset->draw(*this);
    }

  

  for (int index=0; index< children.size(); ++index)
    {
      children[index]->draw();
    }
  
}

void SceneNode::addChild(unique_ptr<SceneNode> node)
{
    //auto tnode = unique_ptr<SceneNode>(node);
    children.push_back( move(node) );

}

void SceneNode::setAsset(Model* model)
{
  cout << "Setting asset for " << name << endl;
    asset = model;
}

glm::mat4 SceneNode::getMVPMatrix() const
{
    return MVPMatrix;
}

void SceneNode::updateLocal(Camera& camera)
{
    //std::cout << "Updating transformation matrix" << std::endl;
    glm::mat4 Model = glm::mat4(1.0f);
    
    MVPMatrix = camera.getProjectionMatrix() * camera.getViewMatrix() * Model;
}

void SceneNode::updateAll(Camera& camera)
{
    updateLocal(camera);
    for (std::vector<unique_ptr<SceneNode>>::iterator it = children.begin(); it != children.end(); ++it)
    {
        (*it)->updateAll(camera);
    }
}
