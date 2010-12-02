#ifndef GIMPFACT_H
#define GIMPFACT_H

// quarl 2007-03-03 initial version

#include <raster/bwfactory.h>
#include <libgimp/gimp.h>

using pagetools::CntPtr;
using pagetools::BWFactory;
using pagetools::BWImage;

class GimpFactory: public BWFactory
{
public:
    GimpFactory(GimpDrawable *drawable);
    virtual CntPtr<BWImage> create();
private:
    GimpDrawable *drawable_;
};

#endif//GIMPFACT_H
