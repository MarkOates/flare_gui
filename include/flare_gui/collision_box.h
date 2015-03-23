#ifndef FGUI_COLLISION_BOX_HEADER
#define FGUI_COLLISION_BOX_HEADER




#include <flare_gui/collision_area.h>




class FGUICollisionBox : public FGUICollisionArea
{
public:
	FGUICollisionBox(float x, float y, float w, float h);
	~FGUICollisionBox();

	void draw_bounding_area();
	bool collides(float x, float y);
};




#endif