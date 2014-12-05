# "include/uiwidget.h"
# "include/uiimage.h"
# "include/texture.h"

#define GLM_FORCE_RADIANS
# <glm/gtc/matrix_transform.hpp>
# <glm/gtx/transform.hpp>

namespace Hodhr {
  
UIImage::UIImage()
{

}

UIImage::~UIImage()
{

}


void UIImage::setImageTexture(Texture* texture)
{
    active_texture_ = texture;
    // texture_id_ = active_texture_->getTextureID();
    
    glm::vec3 Scale = glm::vec3(texture->getWidth()/1280.0f, texture->getHeight()/720.0f, 1);
    glm::vec3 Position = glm::vec3(0.0f, 0.1f, 0.0f);
    mv_matrix_ = glm::translate(
                     glm::mat4(1.0f),
                     Position);

    mv_matrix_ = glm::scale(
                     mv_matrix_,
                     Scale);
    
    createQuad();
}

}
