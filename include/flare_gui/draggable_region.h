#ifndef FGUI_DRAGGABLE_REGION_HEADER
#define FGUI_DRAGGABLE_REGION_HEADER





#include <flare_gui/widget.h>



class FGUIDraggableRegion : public FGUIWidget
{
public:
	FGUIDraggableRegion(FGUIParent *parent, float x, float y, float w, float h);

	void on_draw();
	void on_drag(float x, float y, float dx, float dy);
};





#endif