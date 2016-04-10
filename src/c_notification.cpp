
#include <stdexcept>
#include <string>

#include "lib/units.h"

#include "c_notification.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Component;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_NOTIFICATION;

  void Notification::setFontSize(int size)
  {
    fontSize_ = size;
  }

  void Notification::setColor(const Color& color)
  {
    color_ = color;
    for (auto tl : lines_) {
      tl.col = color;
    }
  }

  Color Notification::getColor()
  {
    return color_;
  }

  int Notification::addLine(string msg)
  {
    auto newLine = createNewLine(msg);
    lines_.push_back(newLine);
    return lines_.size() - 1;
  }

  string Notification::getLine(int lineNum)
  {
    return lines_[lineNum].msg;
  }

  void Notification::updateLine(int lineNum, string msg)
  {
    if (lineNum == -1) {
      throw std::logic_error("Trying to update line with -1");
    }
    lines_[lineNum].msg = msg;
  }

  vector<TextLine> Notification::getAllLines()
  {
    return lines_;
  }

  const string Notification::getType()
  {
    return COMPONENT_TYPE_NOTIFICATION;
  }

  TextLine Notification::createNewLine(const string& msg)
  {
    Vector2d newPos;
    newPos.x = startingPosition_.x;
    newPos.y = lines_.back().pos.y + (fontSize_ * 1.2);
    TextLine t(newPos, msg, color_);
    return t;
  }

  TextLine Notification::createNewLine(const string& msg, const Vector2d& pos)
  {
    TextLine t(pos, msg, color_);
    return t;
  }

}
