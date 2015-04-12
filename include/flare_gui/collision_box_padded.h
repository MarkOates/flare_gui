#ifndef FGUI_COLLISION_BOX_PADDED_HEADER
#define FGUI_COLLISION_BOX_PADDED_HEADER




#include <flare_gui/collision_area.h>




class FGUICollisionBoxPadded : public FGUICollisionArea
{
private:
	float padding_top;
	float padding_right;
	float padding_bottom;
	float padding_left;

public:
	FGUICollisionBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl);
	~FGUICollisionBoxPadded();

	void draw_bounding_area();
	bool collides(float x, float y);

	void get_padding(float *pt, float *pr, float *pb, float *pl);
	void set_padding(float pt, float pr, float pb, float pl);
};




#endif
