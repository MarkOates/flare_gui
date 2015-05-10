#ifndef FGUI_COLLISION_COLUMN_HEADER
#define FGUI_COLLISION_COLUMN_HEADER




#include <flare_gui/surface_area.h>




class FGUISurfaceAreaColumn : public FGUISurfaceArea
{
public:
	FGUISurfaceAreaColumn(float x, float w);

	void draw_bounding_area();
	bool collides(float x, float y);
};




#endif