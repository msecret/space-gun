
#ifndef _h_Renderer
#define _h_Renderer

namespace aronnax {

class Renderer
{
  public:
    virtual void render() = 0;
    virtual void beforeRender() = 0;
    virtual void afterRender() = 0;
};

}

#endif
