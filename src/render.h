#ifndef __RENDER_H__
#define __RENDER_H__


/*  Public functions  */

void   render (GimpImage          *image,
	       GimpDrawable       *drawable,
	       PlugInVals         *vals,
	       PlugInImageVals    *image_vals,
	       PlugInDrawableVals *drawable_vals);


#endif /* __RENDER_H__ */