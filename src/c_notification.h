
#ifndef _h_Notification
#define _h_Notification

#include <cstdint>
#include <string>
#include <vector>

#include "lib/component.h"
#include "lib/units.h"

#include "c_base_shaped.h"

namespace spacegun {
  using std::string;
  using std::vector;
  using aronnax::Color;
  using aronnax::Component;
  using aronnax::Vector2d;

  const string COMPONENT_TYPE_NOTIFICATION = "notification";

  struct TextLine {
    Vector2d pos;
    string msg;
    Color col;

    TextLine(const Vector2d& pos, string msg, const Color& color) :
      pos(pos),
      msg(msg),
      col(color)
    { }
  };

  class Notification: public Component
  {
    public:
      Notification(const Vector2d& initialPos, const string& name,
          Color color) :
        startingPosition_(initialPos),
        name_(name),
        color_(color),
        fontSize_(16),
        lines_()
      {
        auto newLine = createNewLine(name, initialPos);
        lines_.push_back(newLine);
      }
      void setFontSize(int size);
      void setColor(const Color& color);
      Color getColor();
      int addLine(string msg);
      string getLine(int lineNum);
      void updateLine(int lineNum, string msg);
      vector<TextLine> getAllLines();
      const string getType();

    private:
      vector<TextLine> lines_;
      Vector2d startingPosition_;
      string name_;
      int fontSize_;
      Color color_;
      TextLine createNewLine(const string& msg);
      TextLine createNewLine(const string& msg, const Vector2d& pos);

  };
}

#endif
