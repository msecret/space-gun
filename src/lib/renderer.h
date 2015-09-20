
#ifndef _h_Renderer
#define _h_Renderer

namespace aronnax {

class Renderer
{
  public:
    virtual void render(const uint32_t dt) = 0;
};

}

#endif
