


#include <flare_gui/flare_gui.h>
#include <allegro_flare/allegro_flare.h>




#include <flare_gui/progress_bar.h>


#include <flare_gui/music_notation.h>





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
		ALLEGRO_FONT *font = af::fonts["FontAwesome.otf -" + tostring(place.size.x/3)];
		int line_height = al_get_font_line_height(font);
		draw_unicode_char(font, color::white, icon, ALLEGRO_ALIGN_CENTER, place.size.x/2, place.size.y/2 - line_height/2-1);
	}
};






#include <allegro_flare/objects/sound_object.h>

class MyMediaPlayer : public FGUIWindow
{
private:
	std::string filename;
	Sound sound;
	FGUIProgressBar *progress_bar;
	FGUIButton *play_button;
	FGUIButton *stop_button;
	FGUIText *filename_label;
	FGUIText *media_player_title;
public:
	MyMediaPlayer(FGUIParent *parent)
		: FGUIWindow(parent, 650, 500, 200, 170)
		, filename("water_4.wav")
		, sound(af::samples[filename])
		, progress_bar(NULL)
		, play_button(NULL)
		, stop_button(NULL)
		, media_player_title(NULL)
	{
		ALLEGRO_FONT *text_font = af::fonts["DroidSans.ttf 20"];

		//media_player_title = new FGUIText(this, 10, 20, af::fonts["DroidSans.ttf 20"], "Media Player");


		filename_label = new FGUIText(this, 100, 34, af::fonts["DroidSans.ttf 20"], filename);
		filename_label->collision_area->placement.align.x = 0.5;
		filename_label->set_font_color(color::white);

		new FGUIDraggableRegion(this, place.size.x/2, place.size.y/2, place.size.x, place.size.y);

		play_button = new FGUIButton(this, "play", text_font, 100-45, 120+4, 80, 50);
		play_button->attr.set("on_click_send_message", "play");

		stop_button = new FGUIButton(this, "stop", af::fonts["DroidSans.ttf 20"], 190-45, 120+4, 80, 50);
		stop_button->attr.set("on_click_send_message", "stop");

		progress_bar = new FGUIProgressBar(this, 100, 70+4, 180);
	}
	void receive_message(std::string message) override
	{
		if (message == "play") sound.play();
		else if (message == "stop") sound.stop();
	}
	void primary_timer_func() override
	{
		progress_bar->set_val(sound.position(), 0.5);
	}
};






#include <cctype>
inline bool is_valid_variable_name(const std::string &str)
{
	return (str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUV_abcdefghijklmnopqrstuvwxyz") == std::string::npos);
}


class MyFGUIWindow : public FGUIWindow
{
private:
	ALLEGRO_DISPLAY *display;
	FGUITextInput *text_input;
	FGUIMusicNotation *music_render;
	FGUIProgressBar *progress_bar;
	FGUIText *text;
	MyMediaPlayer *media_player;

	DataAttr virtual_memory;
	std::string virtual_memory_filename;

	FGUINotificationBubble *notification_bubble;

	int mouse_down_x, mouse_down_y;

public:
	MyFGUIWindow(FGUIParent *parent, Display *display)
		: FGUIWindow(parent, 0, 0, display->width(), display->height())
		, display(display->display)
		, text_input(NULL)
		, music_render(NULL)
		, progress_bar(NULL)
		, text(NULL)
		, media_player(NULL)
		, notification_bubble(NULL)
		, virtual_memory_filename("virtual_memory_file.txt")
		, mouse_down_x(0)
		, mouse_down_y(0)
	{			
		int button_width = 130;
		int button_height = 80;

		float x = 1;
		float y = 1;


		text_input = new FGUITextInput(this, af::fonts["DroidSans.ttf 25"], "", place.size.x/2, 80, place.size.x-30, 50);
		text_input->set_as_focused();
		text_input->attr.set("on_submit_send_text", "true");
		text_input->attr.set("default_text_when_empty", "type a command");

		text = new FGUIText(this, 27, text_input->place.position.y + text_input->place.size.y + 4, af::fonts["consola.ttf 20"], "last:");



		music_render = new FGUIMusicNotation(this, this->place.size.x/2, 300);


		FGUIScaledText *title_text = new FGUIScaledText(this, 20, 12, "DroidSans.ttf 18", "FlareGUI Example");
		title_text->collision_area->placement.align.x = 0;
		title_text->collision_area->placement.align.y = 0;
				
		float window_right = this->collision_area->placement.size.x;


		float radius = 30;
		new FGUICircleButton(this, window_right - 14, 0, radius, font_awesome::remove, "close_window");
		//new FGUICircleButton(this, window_right - 14 -(radius*2-6), 0, radius, 0xf0c9, "toggle_menu");


		
		(new FGUIButton(this, "0.0", af::fonts["DroidSans.ttf 20"], 100, 200+60*0, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.0");

		(new FGUIButton(this, "0.2", af::fonts["DroidSans.ttf 20"], 100, 200+60*1, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.2");

		(new FGUIButton(this, "0.5", af::fonts["DroidSans.ttf 20"], 100, 200+60*2, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 0.5");

		(new FGUIButton(this, "1.0", af::fonts["DroidSans.ttf 20"], 100, 200+60*3, 80, 50))
			->attr.set("on_click_send_message", "set_progress_bar 1.0");

		(new FGUIButton(this, "set music", af::fonts["DroidSans.ttf 20"], 100, 200+60*4+20, 110, 50))
			->attr.set("on_click_send_message", "set_music 123456");


		(new FGUIButton(this, "shrink", af::fonts["DroidSans.ttf 20"], 100, 200+60*5+40, 80, 50))
			->attr.set("on_click_send_message", "shrink");

		(new FGUIButton(this, "grow", af::fonts["DroidSans.ttf 20"], 100, 200+60*6+40, 80, 50))
			->attr.set("on_click_send_message", "grow");

		
		(new FGUICheckbox(this, 600, 200-40, 24));
			(new FGUIScaledText(this, 600+30, 200-40, "DroidSans.ttf 20", "Option 1"));
		(new FGUICheckbox(this, 600, 230-40, 24));
			(new FGUIScaledText(this, 600+30, 230-40, "DroidSans.ttf 20", "Option 2"));
		(new FGUICheckbox(this, 600, 260-40, 24));
			(new FGUIScaledText(this, 600+30, 260-40,  "DroidSans.ttf 20", "Option 3"));


		progress_bar = new FGUIProgressBar(this, 225, 400);
		progress_bar->place.rotation = TAU * 0.25;


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
			af::motion.cmove_to(&place.scale.x, 0.86, 0.3);
			af::motion.cmove_to(&place.scale.y, 0.86, 0.3);
		}
		else if (message_caught = (message == "grow"))
		{
			af::motion.cmove_to(&place.scale.x, 1, 0.3);
			af::motion.cmove_to(&place.scale.y, 1, 0.3);
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
			text->set_text("last: " + message);
		}

		if (!message_caught) std::cout << "Uncaught message: \"" << message << "\"" << std::endl;
	}
	void on_mouse_down() override
	{
		FGUIWindow::on_mouse_down();
		mouse_down_x = af::current_event->mouse.x;
		mouse_down_y = af::current_event->mouse.y;
	}
	void on_drag(float x, float y, float mx, float my) override
	{
		FGUIWindow::on_drag(x, y, mx, my);

		if (mouse_down_y > 40) return;

		int cx, cy;
		if (al_get_mouse_cursor_position(&cx, &cy))
		al_set_window_position(display, cx - mouse_down_x, cy - mouse_down_y);
	}
	void on_draw() override
	{
		FGUIWindow::on_draw();

		ALLEGRO_COLOR frame_color = color::color(color::hex("8e283e"));
		al_draw_filled_rectangle(0, 0, place.size.x, 40, frame_color);

		float frame_thickness = 6;
		al_draw_filled_rectangle(0, 0, frame_thickness, place.size.y, frame_color);
		al_draw_filled_rectangle(0, place.size.y-frame_thickness, place.size.x, place.size.y, frame_color);
		al_draw_filled_rectangle(place.size.x-frame_thickness, 0, place.size.x, place.size.y, frame_color);

		// white outline
		ALLEGRO_COLOR frame_border_color = color::color(color::black, 0.7);
		al_draw_line(0, 0, place.size.x, 0, frame_border_color, 2.0);
		al_draw_line(place.size.x, 0, place.size.x, place.size.y, frame_border_color, 2.0);
		al_draw_line(0, place.size.y, place.size.x, place.size.y, frame_border_color, 2.0);
		al_draw_line(0, 0, 0, place.size.y, frame_border_color, 2.0);
	}
};






class Project : public FGUIScreen
{
public:
	MyFGUIWindow *window;
	Project(Display *display)
		: FGUIScreen(display)
	{
		draw_focused_outline = false;

		window = new MyFGUIWindow(this, display);
		window->collision_area->placement.position.x = display->width()/2;
		window->collision_area->placement.position.y = display->height()/2;

		std::cout << "this widget has " << get_num_ancestors() << " leaves" << std::endl;
	}
};




#include <allegro_flare/allegro_flare.h>

int main(int argc, char *argv[])
{
	af::initialize();
	//Display *display = af::create_display(800, 720);

	Display *display = new Display(800, 720, ALLEGRO_NOFRAME);
	al_register_event_source(af::event_queue, al_get_display_event_source(display->display));

	Project *main = new Project(display);
	af::run_loop();
}

