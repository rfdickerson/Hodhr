// Copyright Robert Dickerson 2014

#ifndef INCLUDE_UI_H_
#define INCLUDE_UI_H_

#include <vector>
#include <memory>
#include <utility>

#include "common.h"

namespace Hodhr {

  // forward declare
  class UIWidget;

  typedef std::vector<std::unique_ptr<UIWidget>> WidgetVector;

  class UI {
   public:
UI();
UI(unsigned int width, unsigned int height);
    ~UI();

    void addWidget(std::unique_ptr<UIWidget> widget);
    void draw();

   protected:
     unsigned int width_;
     unsigned int height_;
     WidgetVector widgets_;
  };


}  // namespace Hodhr

#endif  // INCLUDE_UI_H_
