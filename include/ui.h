// Copyright Robert Dickerson 2014

#ifndef INCLUDE_UI_H_
#define INCLUDE_UI_H_

#include <vector>
#include <memory>
#include <utility>

#include "include/common.h"

namespace Hodhr {

  // forward declare
  class UILabel;

  typedef std::vector<std::unique_ptr<UILabel>> WidgetVector;

  class UI {
   public:
UI();
UI(unsigned int width, unsigned int height);
    ~UI();

    void addWidget(std::unique_ptr<UILabel> widget);
    void draw();

   protected:
     unsigned int width_;
     unsigned int height_;
     WidgetVector widgets_;
  };


}  // namespace Hodhr

#endif  // INCLUDE_UI_H_
