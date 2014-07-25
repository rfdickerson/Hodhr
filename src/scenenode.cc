// Copyright Robert Dickerson 2014

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <utility>
#include <memory>

#include "include/scenenode.h"
#include "include/model.h"
#include "include/camera.h"


namespace Hodhr {

SceneNode::SceneNode(const std::string& name) {
  this->name = name;
  this->asset = NULL;
}

SceneNode::~SceneNode() {
}

void SceneNode::draw() {
  // cout << "drawing node " << name << endl;
  if (asset) {
    // cout << "drawing asset in " << name << endl;
    asset->draw(*this);
  }
  
  for (unsigned int index = 0; index < children.size(); ++index) {
    children[index]->draw();
  }
}

void SceneNode::setPosition(float x, float y, float z) {
  this->position_ = glm::vec3(x, y, z);
}

void SceneNode::setScale(float scale) {
  this->scale_ = glm::vec3(scale, scale, scale);
}

void SceneNode::addChild(std::unique_ptr<SceneNode> node) {
  children.push_back(move(node));
}

void SceneNode::setAsset(Model* model) {
  asset = model;
}

glm::mat4 SceneNode::getMVPMatrix() const {
    return mvp_matrix_;
}

glm::mat3 SceneNode::getNormalMatrix() const {
  return normal_matrix_;
}

void SceneNode::updateLocal(const Camera& camera) {
  // std::cout << "Updating transformation matrix" << std::endl;
  glm::mat4 t = glm::translate(
      glm::mat4(1.0f),
      position_);

  glm::mat4 s = glm::scale(glm::mat4(1.0f), scale_);
  
  glm::mat4 model_matrix = t*s;

  // mv_matrix_ = camera.getViewMatrix() * model_matrix;
  mv_matrix_ = camera.getViewMatrix() * model_matrix;
    
  mvp_matrix_ = camera.getProjectionMatrix() * mv_matrix_;

  // normal_matrix_ = glm::mat3(glm::transpose(glm::inverse(mv_matrix_)));
  // normal_matrix_ = glm::transpose(glm::inverse(glm::mat3(mv_matrix_)));
  normal_matrix_ = glm::transpose(glm::inverse(glm::mat3(model_matrix)));
}

void SceneNode::updateAll(const Camera& camera) {
    updateLocal(camera);

    for (std::vector<std::unique_ptr<SceneNode>>::iterator
             it = children.begin();
         it != children.end(); ++it) {
      (*it)->updateAll(camera);
    }
}

}  // namespace Hodhr
