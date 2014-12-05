// Copyright Robert Dickerson 2014

#ifndef INCLUDE_CAMERA_H_
#define INCLUDE_CAMERA_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace Hodhr {

  class Camera
  {
  public:
    Camera(int width, int height);
    virtual ~Camera();
    void rotate(float deltaTime, float dx, float dy);
    void move(float deltaTime, float speed);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
 
  protected:
 
  private:
  
    float mouseSpeed;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
  
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;
    
    float horizontalAngle;
    float verticalAngle;
    
    float fieldOfView;
    int width;
    int height;
        
    float aspectRatio;


  };

}  // namespace Hodhr

#endif  // INCLUDE_CAMERA_H_
