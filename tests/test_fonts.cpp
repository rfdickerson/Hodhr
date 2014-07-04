#include <iostream>
#include <math.h>
#include <pango/pangocairo.h>

static void
draw_text(cairo_t *cr)
{
  #define FONT "Nimbus Sans Bold 36"
  PangoLayout *layout;
  PangoFontDescription *desc;
  int i;

  /* Create a pango layout */
  layout = pango_cairo_create_layout (cr);

  pango_layout_set_text(layout, "Leveled Up!", -1);
  desc = pango_font_description_from_string (FONT);
  pango_layout_set_font_description (layout, desc);
  pango_font_description_free(desc);

  // draw the text
  cairo_save (cr);
  cairo_set_source_rgb(cr, .2, .2, .2);
  pango_cairo_update_layout( cr, layout);

  pango_cairo_show_layout( cr, layout);

  cairo_restore (cr);

  //delete layout;
  g_object_unref(layout);
  //free (layout);
}


int main(int argc, char **argv)
{

  cairo_t *cr;
  char *filename;
  cairo_status_t status;
  cairo_surface_t *surface;

  if (argc !=2)
    {
      std::cerr << "Usage: testFonts outputFilename\n";
      return 1;
    }

  filename = argv[1];

  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 300, 200);

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
  cairo_paint (cr);
  draw_text (cr);
  cairo_destroy (cr);

  status = cairo_surface_write_to_png (surface, filename);
  cairo_surface_destroy (surface);

  if (status != CAIRO_STATUS_SUCCESS)
    {
      std::cout << "Could not save png to " << filename << std::endl;
    }

  unsigned char* data = cairo_image_surface_get_data (surface);

  

  return 0;
}
