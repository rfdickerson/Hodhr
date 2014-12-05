#ifndef INCLUDE_PANEL_H_
#define INCLUDE_PANEL_H_

#include "common.h"
#include "uiwidget.h"

namespace Hodhr {

class UIPanel : public UIWidget {
  
public:
  UIPanel(GLuint width, GLuint height);
  virtual ~UIPanel();
  
  
private:
  void createCairoPanel(GLuint width, GLuint height);
  
  
  
};


}


#endif 	// INCLUDE_PANEL_H_
