


#include <flare_gui/gui_screen.h>
#include <allegro_flare/allegro_flare.h>

#include <flare_gui/surface_areas/box.h>






FGUIScreen::FGUIScreen(Display *display)
	: Screen(display)
	, FGUIWidget(NULL, new FGUISurfaceAreaBox(0, 0, display->width(), display->height()))
	, draw_focused_outline(true)
	, use_joystick_as_mouse(true)
	, focused_outline_color(color::dodgerblue)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScreen");
	attr.set("id", "Screen" + tostring(widget_count));

	surface_area->placement.align.x = 0;
	surface_area->placement.align.y = 0;
}



void FGUIScreen::primary_timer_func()
{
	if (use_joystick_as_mouse)
	{
		if (af::joystick)
		{
			float sensitivity = 8.0;

			ALLEGRO_MOUSE_STATE mouse_state;
			al_get_mouse_state(&mouse_state);

			ALLEGRO_JOYSTICK_STATE joystick_state;
			al_get_joystick_state(af::joystick, &joystick_state);

			// TODO:
			// right now the joystick axis to use for the mouse emulation is static,
			// this should be fixed so that an axis might be chosen by the user
			// and/or multiple joysticks could also be used
			if (joystick_state.stick[0].axis[0] != 0.0 || joystick_state.stick[0].axis[1] != 0.0)
			{
				al_set_mouse_xy(display->al_display,
					mouse_state.x + joystick_state.stick[0].axis[0]*sensitivity,
					mouse_state.y + joystick_state.stick[0].axis[1]*sensitivity);
			}
		}
	}

	// call the parent's usual functions

	FGUIWidget::primary_timer_func();
	FGUIWidget::draw_func();

	on_draw_after_children();
}



void FGUIScreen::mouse_axes_func()
{
	if (af::current_event->mouse.display != display->al_display) return;

	float mx = af::current_event->mouse.x;
	float my = af::current_event->mouse.y;
	float mdx = af::current_event->mouse.dx;
	float mdy = af::current_event->mouse.dy;

	FGUIWidget::mouse_axes_func(mx, my, mdx, mdy);
}



void FGUIScreen::mouse_down_func()
{
	if (af::current_event->mouse.display != display->al_display) return;
	FGUIWidget::mouse_down_func();
}



void FGUIScreen::mouse_up_func()
{
	if (af::current_event->mouse.display != display->al_display) return;
	FGUIWidget::mouse_up_func();
}



void FGUIScreen::key_down_func()
{
	if (af::current_event->keyboard.display != display->al_display) return;


	// these next two conditionals are for keyboard/joystick navigation of widgets

/*
	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_TAB)
	{
		if (af::key_shift) jump_focus_to_ancestor_by_delta(true);// jump_focus_to_previous_direct_descendent();
		else jump_focus_to_ancestor_by_delta(); //jump_focus_to_next_direct_descendent();
	}
	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		children.unfocus_all();
		al_show_mouse_cursor(display->display); // restore visibility of the cursor here
	}
*/

	FGUIWidget::key_down_func();
}



void FGUIScreen::key_up_func()
{
	if (af::current_event->keyboard.display != display->al_display) return;
	FGUIWidget::key_up_func();
}



void FGUIScreen::key_char_func()
{
	if (af::current_event->keyboard.display != display->al_display) return;

	FGUIWidget::key_char_func();
}



void FGUIScreen::joy_down_func()
{
/*
	// for joystick / keyboard navigation of widgets
	if (af::current_event->joystick.button ==  5) jump_focus_to_ancestor_by_delta(); // XBOX Controller right shoulder trigger button
	if (af::current_event->joystick.button ==  4) jump_focus_to_ancestor_by_delta(true); // XBOX Controller left shoulder trigger button
*/

	FGUIWidget::joy_down_func();
}



void FGUIScreen::joy_up_func()
{
//	if (af::current_event->keyboard.display != display->display) return;
	FGUIWidget::joy_up_func();
}



void FGUIScreen::joy_axis_func()
{
// this stuff is now polled on the timer
//	use_joystick_as_mouse = true;
//	if (af::current_event->joystick.axis == 0) joy_horizontal_pos = af::current_event->joystick.pos;
//	if (af::current_event->joystick.axis == 1) joy_vertical_pos = af::current_event->joystick.pos;

	FGUIWidget::joy_axis_func();
}



void FGUIScreen::on_draw() {}



void FGUIScreen::on_draw_after_children() {}


