
#include <flare_gui/surface_areas/column.h>








FGUICollisionColumn::FGUICollisionColumn(float x, float w)
	: FGUICollisionArea(x, 0, w, 0)
{
}





void FGUICollisionColumn::draw_bounding_area()
{
	
}





bool FGUICollisionColumn::collides(float x, float y)
{
	if (x < placement.position.x) return false;
	if (x > placement.position.x + placement.size.x) return false;
	return true;
}

