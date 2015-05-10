




#include <flare_gui/surface_areas/box.h>
#include <allegro_flare/color.h>





#include <iostream>

FGUICollisionBox::FGUICollisionBox(float x, float y, float w, float h)
	: FGUICollisionArea(x, y, w, h)
{
	//std::cout << "FGUICollisionBox()" << std::endl;
}



FGUICollisionBox::~FGUICollisionBox()
{
	//std::cout << "~FGUICollisionBox()" << std::endl;
}



bool FGUICollisionBox::collides(float x, float y)
{
	return placement.collide(x, y);
}



void FGUICollisionBox::draw_bounding_area()
{
	placement.draw_box(color::color(color::aliceblue, 0.2), true);
}


