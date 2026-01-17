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

#include <formats/gimpfact.h>
#include "deskew.h"
#include <gegl.h>

GimpFactory::GimpFactory(GimpDrawable *drawable)
    :drawable_(drawable)
{
}

// read a BWImage (packed black&white image) from Gimp

CntPtr<BWImage>
GimpFactory::create() {
    DEBUGPRINT("GimpFactory::create: entering\n");
    //     TODO: this could be a parameter, but for now I don't think we need it.
    gint black_threshold = 100;
    gint x1, y1, x2, y2;

    if (!gimp_drawable_mask_bounds (drawable_, &x1, &y1, &x2, &y2)) {
        DEBUGPRINT("GimpFactory::create: gimp_drawable_mask_bounds failed, using full drawable\n");
        x1 = 0;
        y1 = 0;
        x2 = gimp_drawable_get_width(drawable_);
        y2 = gimp_drawable_get_height(drawable_);
    }

    gint w = x2 - x1;
    gint h = y2 - y1;

    gboolean has_alpha = gimp_drawable_has_alpha(drawable_);
    
    GeglBuffer *buffer = gimp_drawable_get_buffer (drawable_);
    const Babl *format = gegl_buffer_get_format (buffer);
    gint bpp = babl_format_get_bytes_per_pixel (format);

    DEBUGPRINT("GimpFactory::create(): bounds: x1=%d, x2=%d, y1=%d, y2=%d, w=%d, h=%d, bpp=%d\n",
               x1, x2, y1, y2, w, h, bpp);

    if (w <= 0 || h <= 0) {
        DEBUGPRINT("GimpFactory::create(): invalid dimensions\n");
        return CntPtr<BWImage>(NULL);
    }

    gint max_bpp_check = bpp;
    if (has_alpha) {
        // ignore last channel (XXX this assumes 1 byte per channel and alpha
        // channel is last byte!)
        max_bpp_check --;
    }

    CntPtr<BWImage> image = CntPtr<BWImage>(new BWImage(w, h));
    image->zeroAll();

    DEBUGPRINT("GimpFactory::create(): image allocated\n");

    GeglRectangle roi = { x1, y1, w, h };
    GeglBufferIterator *iter = gegl_buffer_iterator_new (buffer, &roi, 0, format,
                                                         GEGL_ACCESS_READ, GEGL_ABYSS_NONE, 1);

    DEBUGPRINT("GimpFactory::create(): iterator created\n");

    while (gegl_buffer_iterator_next (iter)) {
        guchar *data = (guchar *)iter->items[0].data;
        GeglRectangle *rect = &iter->items[0].roi;

        for (int y = 0; y < rect->height; y++) {
            for (int x = 0; x < rect->width; x++) {
                guchar *pixel = data + (y * rect->width + x) * bpp;
                for (int k = 0; k < max_bpp_check; k++) {
                    if (pixel[k] < black_threshold) {
                        int py = rect->y + y - y1;
                        int px = rect->x + x - x1;
                        if (py >= 0 && py < h && px >= 0 && px < w) {
                            image->setPixelOn(py, px);
                        } else {
                            DEBUGPRINT("GimpFactory::create(): out of bounds: %d, %d\n", py, px);
                        }
                        break;
                    }
                }
            }
        }
    }

    g_object_unref (buffer);

    DEBUGPRINT("GimpFactory::create(): done\n");

    return image;
}