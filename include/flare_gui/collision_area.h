#ifndef FGUI_COLLISION_AREA_HEADER
#define FGUI_COLLISION_AREA_HEADER




#include <allegro_flare/placement2d.h>




class FGUICollisionArea
{
public:
	placement2d placement;
	FGUICollisionArea(float x, float y, float w, float h);
	virtual ~FGUICollisionArea();

	virtual void draw_bounding_area() = 0;
	virtual bool collides(float x, float y) = 0;
};





#endif