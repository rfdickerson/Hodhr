#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
 public:
  Camera(int width, int height);
  virtual ~Camera();
  
  void rotate( float dx, float dy);
  
  glm::mat4 const& getViewMatrix();
  
  glm::mat4 const& getProjectionMatrix();
  
 protected:
 
 private:
  
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  
  glm::quat pitch;
  glm::quat bearing;
  
  float fieldOfView;
  int width;
  int height;
        
  float aspectRatio;


};

#endif // CAMERA_H
