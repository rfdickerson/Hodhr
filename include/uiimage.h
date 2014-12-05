#ifndef INCLUDE_UIIMAGE_H_
#define INCLUDE_UIIMAGE_H_

#include "common.h"
#include "uiwidget.h"

namespace Hodhr {

// forward define  
class Texture;  

class UIImage : public UIWidget {
public:
  
  UIImage();
  virtual ~UIImage();
  void setImageTexture(Texture* texture);
  
  
private:
  
  // Texture* active_texture_;
  
  
};

}  // namespace Hodhr

#endif // INCLUDE_UIIMAGE_H_
