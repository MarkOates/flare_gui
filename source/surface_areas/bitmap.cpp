




#include <flare_gui/surface_areas/alpha_bitmap.h>
#include <allegro_flare/color.h>







FGUISurfaceAreaBitmap::FGUISurfaceAreaBitmap(float x, float y, ALLEGRO_BITMAP *bitmap)
	: FGUISurfaceArea(x, y, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap))
	, bitmap(bitmap)
{}



bool FGUISurfaceAreaBitmap::collides(float x, float y)
{
	if (!placement.collide(x, y)) return false;

	placement.transform_coordinates(&x, &y);

	ALLEGRO_COLOR pixel_color = al_get_pixel(bitmap, x, y);

	if (pixel_color.a < 0.001) return false;
	return true;
}



void FGUISurfaceAreaBitmap::draw_bounding_area()
{
	placement.draw_box(color::color(color::aliceblue, 0.2), true);
}


