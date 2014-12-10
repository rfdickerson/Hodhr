// Copyright Robert Dickerson 2014

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <utility>
#include <memory>

#include "scenenode.h"
#include "model.h"
#include "camera.h"


namespace Hodhr {

  SceneNode::SceneNode(const std::string& name) {
    this->name = name;
    this->asset = NULL;

  }

  SceneNode::~SceneNode() {
  }

  void SceneNode::draw() {

    if (asset) {
      asset->draw(*this);
    }
    
    for (unsigned int index = 0; index < children.size(); ++index) {
      children[index]->draw();
    }
  }

  void SceneNode::setPosition(float x, float y, float z) {
    this->mPosition = glm::vec3(x, y, z);
  }

  void SceneNode::setScale(float scale) {
    this->mScale = glm::vec3(scale, scale, scale);
  }

  void SceneNode::addChild(SceneNode* pNode) {
    children.push_back(pNode);
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

    glm::mat4 SceneNode::getModelViewMatrix() const {
	    return mv_matrix_;
	}
  
  void SceneNode::updateLocal(const Camera& camera) {
    // std::cout << "Updating transformation matrix" << std::endl;
    glm::mat4 t = glm::translate(
				 glm::mat4(1.0f),
                 mPosition);
    
    glm::mat4 s = glm::scale(glm::mat4(1.0f), mScale);

    glm::mat4 r = glm::toMat4(mQuat);
    
    glm::mat4 model_matrix = t*r*s;

    mv_matrix_ = camera.getViewMatrix() * model_matrix;
    
    mvp_matrix_ = camera.getProjectionMatrix() * mv_matrix_;


    // normal_matrix_ = glm::mat3(glm::transpose(glm::inverse(mv_matrix_)));
    normal_matrix_ = glm::transpose(glm::inverse(glm::mat3(mv_matrix_)));
    // normal_matrix_ = glm::transpose(glm::inverse(glm::mat3(model_matrix)));

    glm::quat rot = glm::angleAxis(0.01f, glm::vec3(1.0f, 1.0f, 0.0f));
    mQuat *= rot;
    glm::normalize(mQuat);

  }

  void SceneNode::updateAll(const Camera& camera) {
    updateLocal(camera);
    
    for (std::vector<SceneNode*>::iterator
	   it = children.begin();
         it != children.end(); ++it) {
      (*it)->updateAll(camera);
    }
  }
  
}  // namespace Hodhr
