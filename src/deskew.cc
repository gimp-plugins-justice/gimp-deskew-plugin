
// quarl 2007-03-03
//     initial version

#include "deskew.h"
#include "formats/gimpfact.h"
#include "raster/deskewer.h"

// TODO: de-objectize - remove namespaces, factories, etc.

double gimp_find_skew(GimpDrawable *drawable)
{
    GimpFactory f(drawable);
    CntPtr<BWImage> b = f.create();
    double alpha = pagetools::Deskewer::findSkew(*b);
    return alpha;
}
