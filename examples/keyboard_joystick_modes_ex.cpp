#include <flare_gui/flare_gui.h>


#include <allegro_flare/screens/simple_notification_screen.h>

//using namespace FGUIGlobal;










#define FOR(container) for (unsigned i=0; i<container.size(); i++)





class FlareGUIJoystick : public FGUIScreen
{
private:
	SimpleNotificationScreen *notification_screen;
	ALLEGRO_FONT *font;

//	bool joystick_navigation;
//	bool keyboard_navigation;

	//bool hide_mouse_cursor_on_widget_jump; // has some buggy behavior
	//bool joy_as_mouse;
	//float joy_vertical_pos;
	//float joy_horizontal_pos;

	//int last_focused_ancestor;

public:
	FlareGUIJoystick(Display *display)
		: FGUIScreen(display)
		, notification_screen(NULL)
		, font(af::fonts["DroidSerif.ttf 20"])
		//, last_focused_ancestor(0)
		//, joy_as_mouse(false)
		//, joy_vertical_pos(0)
		//, joy_horizontal_pos(0)
		//, hide_mouse_cursor_on_widget_jump(false)
	{
		//FGUIScreen::draw_focused_outline = false;
		notification_screen = new SimpleNotificationScreen(display, af::fonts["DroidSerif.ttf 16"]);

		float button_x = 800/2;
		float button_y = 200;
		float button_spacing = 60;
		int cur = 0;
		new FGUIButton(this, "Button1", button_x, button_y+button_spacing*cur++, 170, 50);
		new FGUIButton(this, "Button2", button_x, button_y+button_spacing*cur++, 170, 50);
		new FGUIButton(this, "Button3", button_x, button_y+button_spacing*cur++, 170, 50);
		new FGUIButton(this, "Button4", button_x, button_y+button_spacing*cur++, 170, 50);
		new FGUIButton(this, "Button5", button_x, button_y+button_spacing*cur++, 170, 50);


		(new ::FGUITextInput(this, "This is a text input", 400, 500, 300, 45))->attr.set("name", "input_val"); 
		(new FGUIButton(this, "send", 400+170+30, 500, 80, 50))->attr.set("on_click_send_message", "submit_input");


		new ::FGUITextArea(this, "This is a textarea", 800, 320, 200, 300);

		new FGUIScaledText(this, 60, 100, "DroidSans.ttf 42", "Widget Selection Example");

		new FGUIText(this, 20, display->height()-70-30, "Use the mouse OR joystick to move the mouse cursor.");
		new FGUIText(this, 20, display->height()-40-30, "Press the joystick SHOULDER BUTTONS or keyboard's TAB to jump to the next GUI widget.");
		new FGUIText(this, 20, display->height()-40, "(you can also hot-swap the joystick)");

		std::cout << "count_complete_lineage: " << get_num_ancestors() << std::endl;
	}
	//void on_draw() override
	//{
	//	FGUIScreen::on_draw();
//
//		if (joy_as_mouse) al_draw_filled_circle(10, 10, 3, color::yellow);
//	}
	void notification(std::string notification)
	{
		notification_screen->spawn_notification(notification);
	}
	void receive_message(std::string message) override
	{
		if (message=="submit_input")
		{
			FGUITextInput *input = static_cast<FGUITextInput *>(children.get_1st_element_with_attr_val("name", "input_val"));
			if (input) notification_screen->spawn_notification(input->get_text());
		}
	}
	

	//void joy_config_func() override
	//{
	//	FGUIScreen::joy_config_func();
	//
	//	std::cout << "joy config change" << std::endl;
	//	notification_screen->spawn_notification("joystick configuration change");
	//}

	//void mouse_axes_func() override
	//{
	//	FGUIScreen::mouse_axes_func();

		//if (hide_mouse_cursor_on_widget_jump)
		//{
		//	al_show_mouse_cursor(display->display);
		//}
	//}
	//void _joy_down_func()
	//{
	//	FGUIScreen::joy_down_func();

		//std::cout << "joy button " << af::current_event->joystick.button << std::endl;

		//if (af::current_event->joystick.button ==  5) jump_focus_to_next_widget(); // XBOX Controller shoulder trigger button
		//if (af::current_event->joystick.button ==  4) jump_focus_to_previous_widget(); // XBOX Controller shoulder trigger button
/*
		if (af::current_event->joystick.button ==  0)
		{
			// does only 1 button
			FOR (children.children)
			{
				if (children.children[i]->is_mouse_over())
				{
					children.children[i]->set_as_focused();
					if (children.children[i]->attr.matches("FGUI_WIDGET_TYPE", "FGUIButton"))
					{
						FGUIButton *button = static_cast<FGUIButton *>(children.children[i]);
						button->on_click();
					}
				}
			}
		}
*/

		/*
		// hmm... doesn't seem to work:

		ALLEGRO_EVENT ev;
		ev.type = ALLEGRO_EVENT_KEY_DOWN;
		ev.any.timestamp = al_get_time();
		ev.any.type = ALLEGRO_EVENT_KEY_DOWN;
		ev.any.source = &af::_user_event_src_for_faking_events;
		ev.keyboard.type = ALLEGRO_EVENT_KEY_DOWN;
		ev.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
		ev.keyboard.display = al_get_current_display();
		al_emit_user_event(&af::_user_event_src_for_faking_events , &ev , NULL); 
		*/
	//}
	//void joy_axis_func() override
	//{
	//	FGUIScreen::joy_axis_func();

		//use_joystick_as_mouse = true;
		//if (af::current_event->joystick.axis == 0) joy_horizontal_pos = af::current_event->joystick.pos;
		//if (af::current_event->joystick.axis == 1) joy_vertical_pos = af::current_event->joystick.pos;


		//if (hide_mouse_cursor_on_widget_jump) al_show_mouse_cursor(display->display);
	//}
	/*
	void key_char_func() override
	{
		FGUIScreen::key_char_func();
	}
	void key_down_func() override
	{
		FGUIScreen::key_down_func();
	}
	*/
};






int main(int argc, char *argv[])
{
	af::initialize();

	//Display *display = af::create_display(1920, 1080, true);
	Display *display = af::create_display(1000, 700);
	FlareGUIJoystick *joystick_ex = new FlareGUIJoystick(display);

	af::run_loop();
}
