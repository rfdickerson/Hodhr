#include <iostream>


#include "Camera.h"



Camera::Camera(int width, int height)
{
  
    
  //ctor
  fieldOfView = 80.0f;
  horizontalAngle = 3.14f;
  verticalAngle = 0.0f;
  position = glm::vec3(0,0,0);
  mouseSpeed = 0.005;
    
  aspectRatio = (float) width / (float) height;
    
  viewMatrix = glm::lookAt(
			   position,
			   position+direction,
			   up
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

void Camera::rotate( float deltaTime, float dx, float dy )
{

  horizontalAngle += mouseSpeed * deltaTime * dx;
  verticalAngle += mouseSpeed * deltaTime * dy;

  /* Direction: spherical coordinates to Cartesian coordinates */
  direction = glm::vec3 (
		      cos(verticalAngle) * sin(horizontalAngle),
		      sin(verticalAngle),
		      cos(verticalAngle) * cos(horizontalAngle)
		      );

  right = glm::vec3(
		    sin(horizontalAngle - 3.14f/2.0f),
		    0,
		    cos(horizontalAngle - 3.14f/2.0f)
		    );

  up = glm::cross( right, direction );

  viewMatrix = glm::lookAt(
			   position,
			   position+direction,
			   up
			   );

  // std::cout << "direction x:" << direction.x << ", y: " << direction.y << std::endl;

}

void Camera::move( float deltaTime, float speed)
{
  position += direction * deltaTime * speed;
  viewMatrix = glm::lookAt(
			   position,
			   position+direction,
			   up
			   );

}
