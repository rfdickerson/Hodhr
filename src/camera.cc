// Copyright Robert Dickerson 2014

#include <glm/gtc/constants.hpp>
#include "include/common.h"
#include "include/camera.h"

namespace Hodhr {

Camera::Camera(int width, int height) {
  
  // ctor
  fieldOfView = 75.0f;
  horizontalAngle = 0.0f;
  verticalAngle = 0.0f;
  position = glm::vec3(0, 0, 0);
  mouseSpeed = 0.005;

  aspectRatio = static_cast<float> (width) / static_cast<float> (height);

  viewMatrix = glm::lookAt(
      position,
      position+direction,
      up);


  projectionMatrix = glm::perspective(
      fieldOfView,
      aspectRatio,
      0.1f,
      100.0f);

  fprintf(stderr, "Created a camera with FoV of %5.2f\n", fieldOfView);
}


glm::mat4 Camera::getViewMatrix() const {
  return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
  return projectionMatrix;
}

Camera::~Camera() {
  //  dtor
}

void Camera::rotate(float deltaTime, float dx, float dy ) {
  horizontalAngle += mouseSpeed * deltaTime * dx;
  verticalAngle += mouseSpeed * deltaTime * dy;

  /* Direction: spherical coordinates to Cartesian coordinates */
  direction = glm::vec3(
      cos(verticalAngle) * sin(horizontalAngle),
      sin(verticalAngle),
      cos(verticalAngle) * cos(horizontalAngle));

  right = glm::vec3(
      sin(horizontalAngle - glm::pi<float>()/2.0f),
      0,
      cos(horizontalAngle - glm::pi<float>()/2.0f));
  
  up = glm::cross(right, direction);

  viewMatrix = glm::lookAt(
      position,
      position+direction,
      up);


}

void Camera::move(float deltaTime, float speed) {
  position += direction * deltaTime * speed;
  viewMatrix = glm::lookAt(
      position,
      position+direction,
      up);
}

}  // namespace Hodhr
