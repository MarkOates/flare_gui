#ifndef __AF_IMAGE_HEADER
#define __AF_IMAGE_HEADER




#include <flare_gui/widget.h>
#include <flare_gui/collision_box.h>


class FGUIImage : public FGUIWidget
{
private:
	ALLEGRO_COLOR color;
public:
	ALLEGRO_BITMAP *bitmap;

	FGUIImage(FGUIParent *parent, ALLEGRO_BITMAP *bitmap, float x, float y);
	void set_bitmap(ALLEGRO_BITMAP *bitmap);
	void set_color(ALLEGRO_COLOR color);
	void on_draw();
};




#endif