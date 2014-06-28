#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        
    protected:
    private:

        glm::quat pitch;
        glm::quat bearing;


};

#endif // CAMERA_H
