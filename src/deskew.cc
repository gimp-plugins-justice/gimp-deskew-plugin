
// quarl 2007-03-03
//     initial version

#include "deskew.h"
#include "formats/gimpfact.h"
#include "raster/deskewer.h"

// TODO: de-objectize - remove namespaces, factories, etc.

double gimp_find_skew(GimpDrawable *drawable)
{
    DEBUGPRINT("gimp_find_skew: starting\n");
    if (!drawable) {
        DEBUGPRINT("gimp_find_skew: NULL drawable!\n");
        return 0;
    }
    GimpFactory f(drawable);
    DEBUGPRINT("gimp_find_skew: factory created\n");
    CntPtr<BWImage> b = f.create();
    DEBUGPRINT("gimp_find_skew: image created from factory\n");
    if (!b) {
        DEBUGPRINT("gimp_find_skew: factory returned NULL image\n");
        return 0;
    }
    double alpha = pagetools::Deskewer::findSkew(*b);
    DEBUGPRINT("gimp_find_skew: angle found: %f\n", alpha);
    return alpha;
}
