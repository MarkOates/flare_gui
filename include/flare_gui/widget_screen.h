#ifndef FGUI_WIDGET_SCREEN_HEADER
#define FGUI_WIDGET_SCREEN_HEADER




#include <allegro_flare/screen.h>
#include <flare_gui/widget_parent.h>

#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/bins/sample_bin.h>
#include <allegro_flare/motion.h>

#include <allegro_flare/clipboard_win.h> // should eventually make this just the clipboard



class FGUIScreen : public Screen, public FGUIParent
{
public:
	bool draw_focused_outline;
	ALLEGRO_COLOR focused_outline_color;
	bool use_joystick_as_mouse;
	bool clear_to_background_color;
	// here are some ideas:
	// bool esc_key_unfocuses_all_widgets
	// bool use_joystick_as_mouse_cursor
	// bool allow_tab_to_traverse_widgets

	FGUIScreen(Display *display);

	// for the builder
	void primary_timer_func();
	void mouse_axes_func();
	void mouse_down_func();
	void mouse_up_func();
	void key_down_func();
	void key_up_func();
	void key_char_func();
	void joy_up_func();
	void joy_down_func();
	void joy_axis_func();

	// for the people
	virtual void on_draw();
	virtual void on_draw_after_children();
};





#endif