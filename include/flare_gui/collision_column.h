#ifndef FGUI_COLLISION_COLUMN_HEADER
#define FGUI_COLLISION_COLUMN_HEADER




#include <flare_gui/collision_area.h>




class FGUICollisionColumn : public FGUICollisionArea
{
public:
	FGUICollisionColumn(float x, float w);

	void draw_bounding_area();
	bool collides(float x, float y);
};




#endif