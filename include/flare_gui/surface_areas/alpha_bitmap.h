#ifndef FGUI_COLLISION_BITMAP_HEADER
#define FGUI_COLLISION_BITMAP_HEADER




#include <flare_gui/surface_area.h>




class FGUICollisionBitmap : public FGUICollisionArea
{
private:
	ALLEGRO_BITMAP *bitmap;
public:
	FGUICollisionBitmap(float x, float y, ALLEGRO_BITMAP *bitmap);

	void draw_bounding_area();
	bool collides(float x, float y);
};




#endif