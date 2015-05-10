





#include <flare_gui/surface_area.h>






#include <iostream>

FGUICollisionArea::FGUICollisionArea(float x, float y, float w, float h)
	: placement(x, y, w, h)
{
	//std::cout << "FGUICollisionArea()" << std::endl;
}



FGUICollisionArea::~FGUICollisionArea()
{
	//std::cout << "~FGUICollisionArea()" << std::endl;
}
