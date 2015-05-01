#ifndef __FGUI_FRAMED_WINDOW_HEADER
#define __FGUI_FRAMED_WINDOW_HEADER



#include <flare_gui/widget.h>
#include <flare_gui/widgets/draggable_region.h>
#include <flare_gui/widgets/button.h>



class FGUIFramedWindow : public FGUIWidget
{
private:

	FGUIDraggableRegion *titlebar_dragger;
	float titlebar_height;
	float frame_thickness;
	std::string window_title;
	FGUIButton *close_button;

	void draw_window_frame_around(float x1, float y1, float x2, float y2);

public:

	FGUIFramedWindow(FGUIWidget *parent, float x, float y, float w, float h);

	void on_message(FGUIWidget *sender, std::string message) override;
	void on_draw() override;
	void on_focus() override;

	void set_title(std::string title);
};




#endif
