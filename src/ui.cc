// Copyright Robert Dickerson 2014

#include <memory>
#include <utility>
#include <vector>

#include "include/common.h"
#include "include/ui.h"
#include "include/uilabel.h"

namespace Hodhr {

  UI::UI() {}

  UI::UI(unsigned int width, unsigned int height) {
      this->width_ = width;
      this->height_ = height;
  }

  UI::~UI() {
  }

  void UI::addWidget(std::unique_ptr<UILabel> widget) {
    widgets_.push_back(std::move(widget));
    fprintf(stderr, "Adding widget to UI, total widgets is %ld\n",
              widgets_.size());
  }

  void UI::draw() {
    for (unsigned int index = 0; index < widgets_.size(); ++index) {
      widgets_[index]->draw();
      }
  }

}  // namespace Hodhr
