#ifndef __FGUI_XY_CONTROLLER_HEADER
#define __FGUI_XY_CONTROLLER_HEADER




#include <flare_gui/flare_gui.h>




class FGUIXYController : public FGUIWidget
{
private:
	vec2d mouse_pos;
	vec2d marker;
	ALLEGRO_COLOR guide_color;
	float guide_opacity;

public:
	FGUIXYController(FGUIWidget *parent, float x, float y, float w, float h);

	void set_point(float x, float y);
	vec2d get_point();

	void on_mouse_down() override;
	void on_mouse_move(float x, float y, float dx, float dy) override;
	void on_draw() override;
	void on_change() override;
};





#endif

