
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include "lib/entity.h"
#include "lib/renderer.h"
#include "lib/units.h"

#include "c_notification.h"
#include "s_notify.h"

namespace spacegun {
  using std::endl;
  using std::ostringstream;
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::IRenderer;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_NOTIFICATION;

  void Notify::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->writeText(*e);
    }
  }

  void Notify::writeText(Entity& e)
  {
    if (renderer_) {
      auto c = e.getComponent<Notification>(COMPONENT_TYPE_NOTIFICATION);

      for (auto line : c->getAllLines()) {
        renderer_->drawText(
            line.pos,
            line.msg,
            line.col);
      }
    }
  }

  const string& Notify::getType()
  {
    return COMPONENT_TYPE_NOTIFICATION;
  }

}
