




#include <flare_gui/collision_box_padded.h>
#include <allegro_flare/color.h>





#include <iostream>

FGUICollisionBoxPadded::FGUICollisionBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl)
	: FGUICollisionArea(x, y, w, h)
	, padding_top(pt)
	, padding_right(pr)
	, padding_bottom(pb)
	, padding_left(pl)
{
}



FGUICollisionBoxPadded::~FGUICollisionBoxPadded()
{
}



bool FGUICollisionBoxPadded::collides(float x, float y)
{
	return placement.collide(x, y, padding_top, padding_right, padding_bottom, padding_left);
}



void FGUICollisionBoxPadded::draw_bounding_area()
{
	placement.draw_box_with_padding(color::color(color::aliceblue, 0.2), true,
		padding_top, padding_right, padding_bottom, padding_left);
}



void FGUICollisionBoxPadded::get_padding(float *pt, float *pr, float *pb, float *pl)
{
	*pt = padding_top;
	*pr = padding_right;
	*pb = padding_bottom;
	*pl = padding_left;
}



void FGUICollisionBoxPadded::set_padding(float pt, float pr, float pb, float pl)
{
	padding_top = pt;
	padding_right = pr;
	padding_bottom = pb;
	padding_left = pl;
}




