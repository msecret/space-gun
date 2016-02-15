
#ifndef _h_Movement
#define _h_Movement

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;
  
  class Movement: public aronnax::System 
  {
    public:
      Movement() {};
      ~Movement() {};
      void init(aronnax::Entities entities) {};
      void update(const uint32_t dt, aronnax::Entities entities);
      void render(const uint32_t dt, aronnax::Entities entities) {};
      void onAddEntity(aronnax::Entity& entity) {};
      const string& getType();
      
    private:
      void processMovement(const uint32_t dt, aronnax::Entity& entity);

  };
}

#endif
