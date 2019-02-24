#include "stdafx.h"

#include <cairo.h>

void triangle(cairo_t* cr)
{
	cairo_move_to(cr, 100, 100);
	cairo_line_to(cr, 100, 200);
	cairo_line_to(cr, 200, 200);
	cairo_line_to(cr, 100, 100);
}

void triangleStroke(cairo_t* cr)
{
	triangle(cr);
	cairo_stroke(cr);
}

void triangleFill(cairo_t* cr)
{
	triangle(cr);
	cairo_fill(cr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cairo_surface_t* surface = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32,
		500,
		500);

	cairo_t* cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0.5, 0.8, 0.8);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 1, 1, 0);
	triangleFill(cr);

	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_set_line_width(cr, 5);
	triangleStroke(cr);

	cairo_surface_write_to_png(surface, "output.png");

	cairo_destroy(cr);

	cairo_surface_destroy(surface);

	return 0;
}
