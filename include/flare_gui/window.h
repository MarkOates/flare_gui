#ifndef FGUI_WINDOW_HEADER
#define FGUI_WINDOW_HEADER




#include <flare_gui/widget_parent.h>
#include <allegro_flare/vec2d.h>
#include <deque>



#include <flare_gui/widget.h>
#include <flare_gui/collision_box.h>
#include <allegro_flare/color.h>
#include <allegro5/allegro_primitives.h>



//class FGUIParent;

class FGUIWindow : public FGUIParent
{
public:
	ALLEGRO_COLOR border_color;
	ALLEGRO_COLOR background_color;

	vec2d local_mouse;

	FGUIWindow(FGUIParent *parent, float x, float y, float w, float h);


	// developer functions
	/*
	void timer_func();
	void mouse_down_func();
	void mouse_up_func();
	void key_down_func();
	void key_up_func();
	void key_char_func();
	*/

	void on_drag(float x, float y, float dx, float dy);

	// user functions
	void on_focus();
	void on_mouse_enter();
	void on_mouse_leave();
	void on_timer();
	void on_draw();
};




#endif