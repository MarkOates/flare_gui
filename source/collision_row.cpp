
#include <flare_gui/surface_areas/row.h>








FGUICollisionRow::FGUICollisionRow(float y, float h)
	: FGUICollisionArea(0, y, 0, h)
{
}





void FGUICollisionRow::draw_bounding_area()
{
	
}





bool FGUICollisionRow::collides(float x, float y)
{
	if (y < placement.position.y) return false;
	if (y > placement.position.y + placement.size.y) return false;
	return true;
}

