// GIMP deskew plug-in
//
// Copyright (C) 2007 Karl Chen <quarl@cs.berkeley.edu>

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

#include "config.h"

#include <gtk/gtk.h>

#include <libgimp/gimp.h>

#include "main.h"
#include "render.h"

#include "plugin-intl.h"

#define DEBUG 1
#include "deskew.h"

/*  Public functions  */

const double deskew_threshold = 0.01/57.295;

void
render (gint32              image_ID,
	GimpDrawable       *drawable,
	PlugInVals         *vals,
	PlugInImageVals    *image_vals,
	PlugInDrawableVals *drawable_vals)
{
    double angle = gimp_find_skew(drawable); // in radians

    DEBUGPRINT("deskew: angle=%.2f\n",
               57.295779513082320876798154814105*angle);

    if (fabs(angle) < deskew_threshold) {
        // nothing to do; already straightened.
        return;
    }
    gimp_context_push ();
    gimp_context_set_interpolation (GIMP_INTERPOLATION_CUBIC);
    gimp_context_set_transform_resize (GIMP_TRANSFORM_RESIZE_ADJUST);

    drawable->drawable_id =
        gimp_item_transform_rotate(drawable->drawable_id,
                                               angle,
                                               TRUE,    // auto_center
                                               -1, -1  // center_x, center_y
            );
    gimp_context_pop ();
}
