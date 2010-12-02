// GIMP deskew plug-in
//
// Copyright (C) 2007, 2008 Karl Chen <quarl@cs.berkeley.edu>

// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

// quarl 2007-03-03 initial version

#include <formats/gimpfact.h>
#include "deskew.h"

GimpFactory::GimpFactory(GimpDrawable *drawable)
    :drawable_(drawable)
{
}

// read a BWImage (packed black&white image) from Gimp

CntPtr<BWImage>
GimpFactory::create() {

    // quarl 2007-03-03
    //     TODO: this could be a parameter, but for now I don't think we need it.
    gint black_threshold = 100;

    gint x1, y1, x2, y2;

    gimp_drawable_mask_bounds (drawable_->drawable_id,
                               &x1, &y1,
                               &x2, &y2);

    gint bpp = gimp_drawable_bpp (drawable_->drawable_id);

    gboolean has_alpha = gimp_drawable_has_alpha(drawable_->drawable_id);

    gint w = x2 - x1;
    gint h = y2 - y1;

    DEBUGPRINT("GimpFactory::create(): bounds: x1=%d, x2=%d, y1=%d, y2=%d, w=%d, h=%d, bpp=%d\n",
               x1, x2, y1, y2, w, h, bpp);

    gint max_bpp_check = bpp;
    if (has_alpha) {
        // ignore last channel (XXX this assumes 1 byte per channel and alpha
        // channel is last byte!)
        max_bpp_check --;
    }

    CntPtr<BWImage> image = CntPtr<BWImage>(new BWImage(w, h));

    GimpPixelRgn rgn;
    gimp_pixel_rgn_init (&rgn,
                         drawable_,
                         x1, y1,
                         w, h,
                         FALSE, FALSE);

    unsigned int bytewidth = image->bytewidth();
    unsigned char padmask=0xFF<<((w+7)%8);

#if DEBUG
    fprintf(stderr, "## writing to /tmp/t.pbm\n");
    FILE *D = fopen("/tmp/t.pbm", "w");
    fprintf(D, "P4\n%d %d\n", w, h);
#endif

    double total_pixels = double(w) * double(h);
    double prev_show_progress = -99;
    double pixels_seen = 0;

    image->zeroAll();

    for (gpointer pr = gimp_pixel_rgns_register (1, &rgn);
         pr != NULL;
         pr = gimp_pixel_rgns_process (pr))
    {
        pixels_seen += double(rgn.w) * double(rgn.h);
        // fprintf(stderr, "## pixels_seen = %ld\n", (long)pixels_seen);

        for (int y = 0; y < rgn.h; ++y) {
            for (int x = 0; x < rgn.w; ++x) {
                for (int k = 0; k < max_bpp_check; ++k) {
                    if (rgn.data[y * rgn.rowstride + x * bpp + k] < black_threshold) {
                        image->setPixelOn( rgn.y + y - y1, rgn.x + x - x1 );
                        break;
                    }
                }
            }
        }

        double progress = pixels_seen / total_pixels;
        if (progress > prev_show_progress + 0.01) {
            gimp_progress_update(progress);
            prev_show_progress = progress;
        }
    }


    DEBUGPRINT("GimpFactory::create(): done\n");

    return image;
}
