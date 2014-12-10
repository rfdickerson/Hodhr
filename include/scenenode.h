// Copyright Robert Dickerson 2014

#ifndef INCLUDE_SCENENODE_H_
#define INCLUDE_SCENENODE_H_

#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>


// #include "Model.h"

namespace Hodhr {

  // forward defines
  class Model;
  class SceneNode;
  class Camera;

  /* holds a list of scenenodes to traverse */
  typedef std::vector<SceneNode*> NodeVector;

  class SceneNode {
    
  private:
    Model* asset;
    
    NodeVector children;

    glm::vec3 mPosition;
    glm::vec3 mScale;

    glm::quat mQuat;

    glm::mat4 mvp_matrix_;
    glm::mat4 mv_matrix_;
    glm::mat3 normal_matrix_;

    
    std::string name;

  public:

    SceneNode(const std::string& name);

    virtual ~SceneNode();
    
    void addChild(SceneNode* node);
    
    void setAsset(Model* model);
    
    glm::mat4 getMVPMatrix() const;

    glm::mat4 getModelViewMatrix() const;
    
    glm::mat3 getNormalMatrix() const;
    
    void setPosition(float x, float y, float z);

    void setScale(float s);

    void draw(void);

    void updateLocal(const Camera& c);

    void updateAll(const Camera& c);
  };
  
}   //  namespace Hodhr

#endif  // INCLUDE_SCENENODE_H_
