#include <iostream>

#include "Camera.h"



Camera::Camera(int width, int height)
{
  
    
  //ctor
  fieldOfView = 80.0f;
    
  aspectRatio = (float) width / (float) height;
    
  viewMatrix = glm::lookAt(
			   glm::vec3(4,3,3),
			   glm::vec3(0,0,0),
			   glm::vec3(0,1,0)
			   );
    
    
  projectionMatrix = glm::perspective(
				      fieldOfView,
				      aspectRatio,
				      0.1f,
				      100.0f
				      );
        
  std::cout << "Created a camera with field of view " << fieldOfView << std::endl;
    
}


glm::mat4 const& Camera::getViewMatrix()
{
  return viewMatrix;
}

glm::mat4 const& Camera::getProjectionMatrix()
{
  return projectionMatrix;
}

Camera::~Camera()
{
  //dtor
}

void Camera::rotate( float dx, float dy )
{


}
