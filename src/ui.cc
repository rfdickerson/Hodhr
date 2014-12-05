// Copyright Robert Dickerson 2014

# <memory>
# <utility>
# <vector>

# "include/common.h"
# "include/ui.h"
# "include/uiwidget.h"

namespace Hodhr {

  UI::UI() {}

  UI::UI(unsigned int width, unsigned int height) {
      this->width_ = width;
      this->height_ = height;
  }

  UI::~UI() {
  }

  void UI::addWidget(std::unique_ptr<UIWidget> widget) {
    widgets_.push_back(std::move(widget));
    fprintf(stderr, "Adding widget to UI, total widgets is %ld\n",
              widgets_.size());
  }

  void UI::draw() {
    for (unsigned int index = 0; index < widgets_.size(); ++index) {
      widgets_[index]->draw();
      widgets_[index]->update();
      }
  }

}  // namespace Hodhr
