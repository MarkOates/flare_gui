#ifndef FGUI_COLLISION_ROW_HEADER
#define FGUI_COLLISION_ROW_HEADER




#include <flare_gui/collision_area.h>




class FGUICollisionRow : public FGUICollisionArea
{
public:
	FGUICollisionRow(float y, float h);

	void draw_bounding_area();
	bool collides(float x, float y);
};





#endif