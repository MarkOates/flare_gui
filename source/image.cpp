


#include <flare_gui/image.h>
#include <allegro_flare/color.h>
#include <allegro_flare/useful.h> // for tostring



FGUIImage::FGUIImage(FGUIParent *parent, ALLEGRO_BITMAP *bitmap, float x, float y)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, bitmap ? al_get_bitmap_width(bitmap) : 0, bitmap ? al_get_bitmap_height(bitmap) : 0))
	, bitmap(bitmap)
	, color(color::white)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIImage");
	attr.set("id", "Image" + tostring(widget_count));
}




void FGUIImage::on_draw()
{
	if (bitmap) al_draw_tinted_bitmap(bitmap, color, 0, 0, NULL);
}




void FGUIImage::set_bitmap(ALLEGRO_BITMAP *bitmap)
{
	this->bitmap = bitmap;
	place.size.x = bitmap ? al_get_bitmap_width(bitmap) : 0;
	place.size.y = bitmap ? al_get_bitmap_height(bitmap) : 0;
}



void FGUIImage::set_color(ALLEGRO_COLOR color)
{
	this->color = color;
}
