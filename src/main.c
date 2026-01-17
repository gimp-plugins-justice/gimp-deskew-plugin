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

#include "config.h"

#include <string.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include "main.h"
#include "interface.h"
#include "render.h"
#include "deskew.h"

#include "plugin-intl.h"

#define PROCEDURE_NAME "gimp-deskew-plugin"

/* Declare the GimpPlugIn subclass */
G_DECLARE_FINAL_TYPE (Deskew, deskew, DESKEW, PLUGIN, GimpPlugIn)

#define DESKEW_TYPE_PLUGIN (deskew_get_type ())

/* GObject boilerplate for the plugin type */
struct _Deskew
{
  GimpPlugIn parent_instance;
};

G_DEFINE_TYPE (Deskew, deskew, GIMP_TYPE_PLUG_IN)

/* Function prototypes */
static GList          * deskew_query_procedures (GimpPlugIn           *plug_in);
static GimpProcedure  * deskew_create_procedure (GimpPlugIn           *plug_in,
                                                 const gchar          *name);
static GimpValueArray * deskew_run              (GimpProcedure        *procedure,
                                                 GimpRunMode           run_mode,
                                                 GimpImage            *image,
                                                 GimpDrawable        **drawables,
                                                 GimpProcedureConfig  *config,
                                                 gpointer              run_data);
static gboolean         deskew_set_i18n         (GimpPlugIn           *plug_in,
                                                 const gchar          *procedure_name,
                                                 gchar               **gettext_domain,
                                                 gchar               **catalog_dir);

/* GObject class initialization */
static void
deskew_class_init (DeskewClass *klass)
{
  GimpPlugInClass *plug_in_class = GIMP_PLUG_IN_CLASS (klass);

  plug_in_class->query_procedures = deskew_query_procedures;
  plug_in_class->create_procedure = deskew_create_procedure;
  plug_in_class->set_i18n         = deskew_set_i18n;
}

/* GObject instance initialization */
static void
deskew_init (Deskew *deskew)
{
}

static gboolean
deskew_set_i18n (GimpPlugIn  *plug_in,
                 const gchar *procedure_name,
                 gchar      **gettext_domain,
                 gchar      **catalog_dir)
{
  return FALSE;
}

/* Returns a list of procedure names implemented by this plugin */
static GList *
deskew_query_procedures (GimpPlugIn *plug_in)
{
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");

  return g_list_append (NULL, g_strdup (PROCEDURE_NAME));
}

/* Creates and configures a GimpProcedure for the plugin */
static GimpProcedure *
deskew_create_procedure (GimpPlugIn  *plug_in,
                         const gchar *name)
{
  GimpProcedure *procedure = NULL;

  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");

  if (g_strcmp0 (name, PROCEDURE_NAME) == 0)
    {
      procedure = gimp_image_procedure_new (plug_in, name,
                                            GIMP_PDB_PROC_TYPE_PLUGIN,
                                            deskew_run,
                                            NULL, NULL);

      gimp_procedure_set_menu_label (procedure, N_("Deskew"));
      gimp_procedure_add_menu_path (procedure, "<Image>/Layer/Transform");
      gimp_procedure_set_documentation (procedure,
                                        N_("Automatically straighten the rotated image"),
                                        N_("This plug-in automatically straightens (deskews) rotated images"),
                                        PROCEDURE_NAME);
      gimp_procedure_set_attribution (procedure,
                                      "Karl Chen <quarl@cs.berkeley.edu>",
                                      "Karl Chen <quarl@cs.berkeley.edu>",
                                      "2008");
    }

  return procedure;
}

static GimpValueArray *
deskew_run (GimpProcedure       *procedure,
            GimpRunMode          run_mode,
            GimpImage           *image,
            GimpDrawable       **drawables,
            GimpProcedureConfig *config,
            gpointer             run_data)
{
  GimpDrawable *drawable;
  
  DEBUGPRINT("deskew_run: starting\n");

  if (drawables == NULL || drawables[0] == NULL)
    {
      GList *selected = gimp_image_list_selected_layers (image);
      if (selected)
        {
          drawable = GIMP_DRAWABLE (selected->data);
          g_list_free (selected);
        }
      else
        {
          GError *error = g_error_new (GIMP_PLUG_IN_ERROR, 0, "No drawable selected");
          return gimp_procedure_new_return_values (procedure, GIMP_PDB_CALLING_ERROR, error);
        }
    }
  else
    {
      drawable = drawables[0];
    }

  render (image, drawable, NULL, NULL, NULL);

  gimp_displays_flush ();

  return gimp_procedure_new_return_values (procedure, GIMP_PDB_SUCCESS, NULL);
}

GIMP_MAIN (DESKEW_TYPE_PLUGIN)