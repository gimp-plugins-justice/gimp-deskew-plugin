// quarl 2007-03-03
//     initial version

#ifndef DESKEW_H
#define DESKEW_H

#include <libgimp/gimp.h>

// #define DEBUG 1

#if DEBUG
#include <glib.h>
#define DEBUGPRINT(x...) g_printerr(x)
#else
#define DEBUGPRINT(x...) ((void)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern double gimp_find_skew(GimpDrawable *drawable);

#ifdef __cplusplus
}
#endif

#endif
