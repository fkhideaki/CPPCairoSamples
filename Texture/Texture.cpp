#include "stdafx.h"

#include <cairo.h>

class CairoPattern
{
public:
	cairo_surface_t* surface;
	cairo_pattern_t* pattern;

public:
	CairoPattern() :
		surface(NULL),
		pattern(NULL)
	{
	}

	virtual ~CairoPattern()
	{
		release();
	}

	void loadImage(const char* filename)
	{
		surface = cairo_image_surface_create_from_png(filename);
		pattern = cairo_pattern_create_for_surface(surface);

		cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REPEAT);
	}

	void release()
	{
		if (pattern)
			cairo_pattern_destroy(pattern);
		if (surface)
			cairo_surface_destroy(surface);

		pattern = NULL;
		surface = NULL;
	}

	void setSource(cairo_t* cr)
	{
		if (pattern)
			cairo_set_source(cr, pattern);
	}
};

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

	CairoPattern pattern;
	pattern.loadImage("T.png");

	cairo_set_source_rgb(cr, 0.5, 0.8, 0.8);
	cairo_paint(cr);
	
	pattern.setSource(cr);
	triangleFill(cr);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 5);
	triangleStroke(cr);

	cairo_surface_write_to_png(surface, "output.png");

	pattern.release();

	cairo_destroy(cr);

	cairo_surface_destroy(surface);

	return 0;
}
