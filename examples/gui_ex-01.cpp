


#include <flare_gui/flare_gui.h>
#include <allegro_flare/allegro_flare.h>




#include <flare_gui/progress_bar.h>


#include <flare_gui/music_notation.h>




DataAttr Globals;




#include <allegro_flare/fonts/font_font_awesome.h>

class FGUICircleButton : public FGUIWidget
{
public:
	int32_t icon;
	ALLEGRO_COLOR icon_color;

	FGUICircleButton(FGUIParent *parent, float x, float y, float radius, int32_t icon, std::string message_to_parent)
		: FGUIWidget(parent, new FGUICollisionCircle(x-(radius)+10, y+(radius)-10, radius))
		, icon(icon)
		, icon_color(color::gray)
	{
		attr.set("on_click_send_message", message_to_parent);
	}
	void on_draw() override
	{
		placement2d &place = (*gimmie_placement());
		// this is correct placement for the circle:
		al_draw_filled_circle(place.size.x/2, place.size.y/2, place.size.x/2, color::color(icon_color, mouse_over ? 1.0 : 0.3));

		ALLEGRO_FONT *font = gimmie_fonts()->auto_get("FontAwesome.otf -" + tostring(place.size.x/3));
		int line_height = al_get_font_line_height(font);
		draw_unicode_char(font, color::white, icon, ALLEGRO_ALIGN_CENTER, place.size.x/2, place.size.y/2 - line_height/2-1);
		//font_awesome:
	}
};




/*

class FGUIMessageToParentButton : public FGUIWidget
{
public:
	FGUIMessageToParentButton(FGUIParent *parent, float x, float y, float radius, std::string message_to_parent)
		: FGUIWidget(parent, new FGUICollisionCircle(x, y, radius))
	{
		set("on_click_send_message", message_to_parent);
	}
	void on_draw() override
	{
		placement2d &place = (*gimmie_placement());
		// this is correct placement for the circle:
		al_draw_filled_circle(place.size.x/2, place.size.y/2, place.size.x/2, color::color(color::red, mouse_over ? 1.0 : 0.3));
	}
};

*/



/*
class FGUICloseParentButton : public FGUIButton
{
public:
	FGUICloseParentButton(FGUIParent *parent, float window_right_edge, float window_top_edge)
		: FGUIButton(parent, "", NULL, window_right_edge-10, window_top_edge, 50, 25)
	{
		placement2d &place = (*gimmie_placement());
		place.align.y = 0;
		place.align.x = 1;
		set("on_click_send_message", "close_window");
	}
	//void on_click() override
	//{
	//	send_message_to_parent("close_window");
	//}
	void on_mouse_enter() override {}
	void on_mouse_leave() override {}
	void on_draw() override
	{
		placement2d &place = (*gimmie_placement());
		//al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, mouse_over ? color::red : color::color(color::red, 0.4));

		al_draw_filled_circle(place.size.x/2, place.size.y/2, place.size.x/2, mouse_over ? color::red : color::color(color::red, 0.4));
	}
};
*/



//(*gimmie_fonts())["DroidSans_0.ttf 20"],

#include <allegro_flare/objects/sound_object.h>

class MyMediaPlayer : public FGUIWindow
{
private:
	//(*gimmie_fonts())["DroidSans_0.ttf 20"],
	std::string filename;
	Sound sound;
	FGUIProgressBar *progress_bar;
public:
	MyMediaPlayer(FGUIParent *parent)
		: FGUIWindow(parent, 650, 500, 200, 170)
		, filename("water_4.wav")
		, sound(gimmie_super_screen()->samples[filename])
		, progress_bar(NULL)
	{
		(new FGUIButton(this, "play", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100-45, 120, 80, 50))
			->attr.set("on_click_send_message", "play");

		(new FGUIButton(this, "stop", (*gimmie_fonts())["DroidSans_0.ttf 20"], 190-45, 120, 80, 50))
			->attr.set("on_click_send_message", "stop");

		progress_bar = new FGUIProgressBar(this, 100, 70, 180);
			//->set("", "");

		(new FGUIText(this, 100, 30, (*gimmie_fonts())["DroidSans_0.ttf 20"], filename))
			->collision_area->placement.align.x = 0.5;
	}
	void receive_message(std::string message) override
	{
		if (message == "play") sound.play();
		else if (message == "stop") sound.stop();
		//(*gimmie_fonts())["DroidSans_0.ttf 20"],
	}
	void primary_timer_func() override
	{
		progress_bar->set_val(sound.position(), 0.5);
	}

	// draw the shaded bitmap
	//draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, (gimmie_super_screen()->bitmaps)["shade_down.png"], 0, color::color(color::white, 0.2));
};





/*
class MyGUIButton : public FGUIButton
{
public:
	MyGUIButton(FGUIParent *parent, std::string text, ALLEGRO_FONT *font, float x, float y, float w, float h)
		: FGUIButton(parent, text, font, x, y, w, h)
	{
		//this->collision_area->placement.rotation = random_float(-0.15, 0.15);
		//this->collision_area->placement.scale.x = this->collision_area->placement.scale.y = random_float(0.95, 1.5);
	}
	void on_draw() override
	{
		placement2d &placement = collision_area->placement;

		// the bottom shade
		float shade_depth = 5;
		al_draw_filled_rounded_rectangle(0, placement.size.y/2 + shade_depth, placement.size.x, placement.size.y+shade_depth, 2, 2, color::color(color::black, 0.1));

		// the button face
		al_draw_filled_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, mouse_over ? color::yellow : color::hex("697784"));

		// the button outline
		al_draw_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, color::color(color::black, 0.2), 2);


		// draw the icon and/or the text
		// in this case, the icon is always drawn to the left of the text
		// with a padding of 10px

		// get the width of the inner content
		float inner_content_width = 0;
		float start_x = 0;
		if (icon) inner_content_width += al_get_bitmap_width(icon); // the width of the icon
		if (font && !text.empty() && icon) inner_content_width += 10; // the padding between the icon and the text
		if (font && !text.empty()) inner_content_width += al_get_text_width(font, text.c_str());
		start_x = placement.size.x * content_alignment - inner_content_width * content_alignment;

		// draw the stuff
		if (icon)
		{
			al_draw_bitmap(icon, start_x, placement.size.y/2 - al_get_bitmap_height(icon)/2, NULL);
			start_x += al_get_bitmap_width(icon);
		}
		if (font && !text.empty() && icon)
		{
			start_x += 10;
		}
		if (font && !text.empty())
		{
			al_draw_text(font, color::white, start_x, placement.size.y/2-al_get_font_line_height(font)/2, ALLEGRO_ALIGN_LEFT, text.c_str());
		}
	}
};
*/






class MyTextInput : public FGUITextInput
{
public:
	using FGUITextInput::FGUITextInput;

	MyTextInput(FGUIParent *parent, ALLEGRO_FONT *font, std::string initial_text, float x, float y, float w, float h)
		: FGUITextInput(parent, font, initial_text, x, y, w, h)
	{}

	void on_submit() override
	{
		send_message_to_parent(get_text());
	};
};




#include <cctype>
inline bool is_valid_variable_name(const std::string &str)
{
	return (str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUV_abcdefghijklmnopqrstuvwxyz") == std::string::npos);//(!isupper(str[i])) return false;
}


class MyFGUIWindow : public FGUIWindow
{
private:
	ALLEGRO_DISPLAY *display;
	placement2d &place;
	MyTextInput *primary_text_input;
	FGUIMusicNotation *music_render;
	FGUIProgressBar *progress_bar;
	FGUIText *text;
	MyMediaPlayer *media_player;

	DataAttr virtual_memory;
	std::string virtual_memory_filename;

	FGUINotificationBubble *notification_bubble;

//	std::string window_title;
public:
	MyFGUIWindow(FGUIParent *parent, Display *display)
		: FGUIWindow(parent, 0, 0, display->width(), display->height())
		, display(display->display)
		, place(*gimmie_placement())
		, primary_text_input(NULL)
		, music_render(NULL)
		, progress_bar(NULL)
		, text(NULL)
		, media_player(NULL)
		, notification_bubble(NULL)
		, virtual_memory_filename("virtual_memory_file.txt")
//		, window_title("Window")
	{			
		int button_width = 130;
		int button_height = 80;

		float x = 1;
		float y = 1;



		primary_text_input = new MyTextInput(this, (*gimmie_fonts())["DroidSerif.ttf 25"], "", place.size.x/2, 80, place.size.x-30, 50);
		primary_text_input->set_as_focused();


		music_render = new FGUIMusicNotation(this, this->place.size.x/2, 300);


		FGUIText *title_text = new FGUIText(this, 20, 14, (*gimmie_fonts())["consola.ttf 20"], Globals.get("window_title"));
		title_text->collision_area->placement.align.x = 0;
		title_text->collision_area->placement.align.y = 0;
				
		float window_right = this->collision_area->placement.size.x;


		float radius = 30;
		new FGUICircleButton(this, window_right, 0, radius, font_awesome::remove, "close_window");
		new FGUICircleButton(this, window_right-(radius*2-6), 0, radius, 0xf0c9, "toggle_menu");


		
		(new FGUIButton(this, "0.0", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*0, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.0");

		(new FGUIButton(this, "0.2", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*1, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.2");

		(new FGUIButton(this, "0.5", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*2, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.5");

		(new FGUIButton(this, "1.0", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*3, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 1.0");

		(new FGUIButton(this, "set music", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*4, 110, 50))
			->attr.set("on_click_send_message", "set_music 123456");


		(new FGUIButton(this, "shrink", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100, 200+60*5, 80, 50))
			->attr.set("on_click_send_message", "shrink");

		(new FGUIButton(this, "grow", (*gimmie_fonts())["DroidSans_0.ttf 20"], 100+90, 200+60*5, 80, 50))
			->attr.set("on_click_send_message", "grow");

		
		(new FGUICheckbox(this, 600, 200-40, 24));
			(new FGUIScaledText(this, 600+30, 200-40, "DroidSans_0.ttf 20", "Option 1"));
		(new FGUICheckbox(this, 600, 230-40, 24));
			(new FGUIScaledText(this, 600+30, 230-40, "DroidSans_0.ttf 20", "Option 2"));
		(new FGUICheckbox(this, 600, 260-40, 24));
			(new FGUIScaledText(this, 600+30, 260-40,  "DroidSans_0.ttf 20", "Option 3"));


		text = new FGUIText(this, place.size.x/2, place.size.y-20, (*gimmie_fonts())["consola.ttf 20"], "-last-");
		text->collision_area->placement.scale.x = 0.8;
		text->collision_area->placement.scale.y = 0.8;

		progress_bar = new FGUIProgressBar(this, 500, 400);


		media_player = new MyMediaPlayer(this);
	}
	void spawn_notification_bubble()
	{
		if (!notification_bubble) notification_bubble = new FGUINotificationBubble(this, "Notification Text", this->place.size.x-20, this->place.size.y-20);
	}
	bool parses_as_variable_definition(std::string message)
	{
		message = php::trim(message);
		if (message.empty()) return false;
		size_t pos = message.find_first_of('=');
		if (pos == std::string::npos) return false;
		return is_valid_variable_name(php::trim(message.substr(0, pos)));
	}
	std::pair<std::string, std::string> parse_key_value(std::string message)
	{
		// this function assumes that "message" has already validated
		std::string key="";
		std::string val="";
		size_t pos = message.find_first_of('=');
		key = message.substr(0, pos);
		val = message.substr(pos+1);
		return std::pair<std::string, std::string>(php::trim(key), attempt_to_evaluate(php::trim(val)));
	}
	std::string attempt_to_evaluate(std::string str)
	{
		str = php::trim(str);
		if (str.empty()) return str;
		if (str[0]=='$')
		{
			size_t pos_of_first_non_variable_name_char = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUV_abcdefghijklmnopqrstuvwxyz", 1);
			std::string possible_variable_name = str.substr(1, pos_of_first_non_variable_name_char);
			if (possible_variable_name.empty())
			{
				std::cout << "[error] $ found without any valid symbol names" << std::endl;
				return "";
			}
			else
			{
				if (!virtual_memory.has(possible_variable_name))
				{
					std::cout << "[error] unrecognized symbol \"" << possible_variable_name << "\"" << std::endl;
					return "";
				}
				else
				{
					//TODO: we might need some recursion here, buddy :)
					return virtual_memory.get(possible_variable_name);
				}
			}
		}
		return str;
	}
	virtual void receive_message(std::string message) override
	{
		bool message_caught = false;
		if (message_caught = (parses_as_variable_definition(message)))
		{
			std::pair<std::string, std::string> parsed_key_val = parse_key_value(message);
			std::cout << parsed_key_val.first << "=" << parsed_key_val.second;
			virtual_memory.set(parsed_key_val.first, parsed_key_val.second);
			virtual_memory.save(virtual_memory_filename);
		}
		else if (message_caught = (message == "show_notification")) spawn_notification_bubble();
		else if (message_caught = (message == "close_window")) af::shutdown_program = true;
		else if (message_caught = Screen::signal_has_header("set_progress_bar", message))
		{
			std::string val = php::trim(Screen::strip_signal_header("set_progress_bar", message));
			val = attempt_to_evaluate(val);
			
			if (progress_bar) progress_bar->set_val(atof(val.c_str()));
		}
		else if (message_caught = (message == "shrink"))
		{
			placement2d &place = (*gimmie_placement());
			gimmie_motion()->cmove_to(&place.scale.x, 0.86, 0.3);
			gimmie_motion()->cmove_to(&place.scale.y, 0.86, 0.3);
		}
		else if (message_caught = (message == "grow"))
		{
			placement2d &place = (*gimmie_placement());
			gimmie_motion()->cmove_to(&place.scale.x, 1, 0.3);
			gimmie_motion()->cmove_to(&place.scale.y, 1, 0.3);
		}
		else if (message_caught = (message == "exit"))
		{
			af::shutdown_program = true;
		}
		else if (message_caught = Screen::signal_has_header("set_music", message))
		{
			std::string val = php::trim(Screen::strip_signal_header("set_music", message));
			music_render->content = val;
			//if (progress_bar) progress_bar->set_val(atof(val.c_str()));
		}
		
		if (message_caught)
		{
			text->set_text(message);
		}

		if (!message_caught) std::cout << "Uncaught message: \"" << message << "\"" << std::endl;
	}
	void on_key_down()
	{

	}
	int down_x, down_y;
	void on_mouse_down() override
	{
		//down_x = af::current_event->mouse.x;
		//down_y = af::current_event->mouse.y;
		FGUIWindow::on_mouse_down();
	}
	void mouse_axes_func(float x, float y, float dx, float dy) override
	{
		if (mouse_down_on_over)
		{
			int cx, cy;
			if (al_get_mouse_cursor_position(&cx, &cy))
			{
				//al_set_window_position(display, cx - down_x, cy - down_y);
			}
		}

		FGUIWindow::mouse_axes_func(x, y, dx, dy);

		/*
		FGUIWindow::mouse_axes_func(x, y, dx, dy);
		if (mouse_over && mouse_down_on_over)
		{
			al_get_mouse_cursor_position(
			//int winx, winy;
			//al_get_window_position(display, &winx, &winy);
			//al_set_window_position(display, winx + dx, winy + dy);
		}
		*/
	}
};





class Project : public FGUIScreen
{
public:
	MyFGUIWindow *window;
	int current_focused_ancestor;
	Project(Display *display)
		: FGUIScreen(display)
		, current_focused_ancestor(0)
	{
		window = new MyFGUIWindow(this, display);
		window->collision_area->placement.position.x = display->width()/2;
		window->collision_area->placement.position.y = display->height()/2;

		std::cout << "this widget has " << get_num_ancestors() << " leaves" << std::endl;
	}
	/*
	void on_key_down()
	{
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_EQUALS) current_focused_ancestor++;
		else if (af::current_event->keyboard.keycode == ALLEGRO_KEY_MINUS) current_focused_ancestor--;

		FGUIWidget *widget = get_nth_ancestor(current_focused_ancestor);
		if (widget)
		{
			widget->set_as_focused();
		}
	}
		*/
};





// in theory, this main would become the standard, in-library main file.  The 

#include <allegro_flare/allegro_flare.h>

int main(int argc, char *argv[])
{
	af::initialize();
	Globals.load("gui_example_01_settings.txt");
	Display *display = af::create_display(Globals.get_as_int("screen_width"), Globals.get_as_int("screen_height"));
	al_set_window_title(display->display, Globals.get("window_title").c_str());
	Project *main = new Project(display);
	af::run_loop();
}

