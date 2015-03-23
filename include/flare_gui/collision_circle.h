#ifndef FGUI_COLLISION_CIRCLE_HEADER
#define FGUI_COLLISION_CIRCLE_HEADER




#include <flare_gui/collision_area.h>




class FGUICollisionCircle : public FGUICollisionArea
{
public:
	FGUICollisionCircle(float x, float y, float r);

	void draw_bounding_area();
	bool collides(float x, float y);
};




#endif