
#ifndef _h_Events
#define _h_Events

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_EVENTED;
  
  class Events: public aronnax::System 
  {
    public:
      Events() {};
      void init(aronnax::Entities& entities) {};
      void update(const uint32_t dt, aronnax::Entities& entities);
      void render(const uint32_t dt, aronnax::Entities& entities) {};
      void onAddEntity(aronnax::Entity& entity) {};
      const string& getType();
      
    private:
      void poll(const uint32_t dt, aronnax::Entities& entities);

  };
}

#endif
