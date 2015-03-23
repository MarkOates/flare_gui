



// come back to this, Mark, this is a cool idea.

/*
class MessageConsole : public FGUIScreen
{
public:
	class ConsoleTextInput : public FGUITextInput
	{
	public:
		ConsoleTextInput(FGUIParent *parent, ALLEGRO_FONT *font, std::string initial_text, float x, float y, float w, float h)
			: FGUITextInput(parent, font, initial_text, x, y, w, h)
		{}
		void on_draw() override
		{
			placement2d &placement = collision_area->placement;
			//placement.start_transform();

			float padding = 10;
			al_draw_filled_rounded_rectangle(0, 0, placement.w, placement.h, 5, 5, color::color(color::black, 0.3));
			al_draw_rounded_rectangle(0, 0, placement.w, placement.h, 5, 5, color::black, 1);
			if (font && !text.empty()) al_draw_text(font, color::white, padding, placement.h/2 - al_get_font_line_height(font)/2, NULL, text.c_str());
			if (focused) al_draw_rounded_rectangle(0-1, 0-1, placement.w+1, placement.h+1, 5, 5, color::aquamarine, 1);

			//placement.restore_transform();
		}
	};

	class ConsoleMessage
	{
	public:
		enum message_type_t
		{
			MESSAGE_TYPE_UNDEF = 0,
			MESSAGE_TYPE_NOTIFICATION
		};
		int type;
		std::string message;
		ConsoleMessage(std::string message, int type)
			: message(message)
			, type(type)
		{}
		void draw(ALLEGRO_FONT *font, float x, float y)
		{
			//al_draw_text(font, color::white, 20, 20, ALLEGRO_ALIGN_LEFT, "hello world");
			al_draw_text(font, color::white, x, y, ALLEGRO_ALIGN_LEFT, message.c_str());
		}
		static ALLEGRO_COLOR get_color_from_type(int type)
		{
			switch(type)
			{
				case MESSAGE_TYPE_NOTIFICATION:
					return color::dodgerblue;
					break;
				case MESSAGE_TYPE_UNDEF:
				default:
					return color::gray;
					break;
			}
		}
	};

	bool active;
	float visibility_counter;
	//MotionManager motion;
	ALLEGRO_FONT *font;
	int toggle_key;
	std::vector<ConsoleMessage> message;
	Camera camera;
	float console_padding;
	float console_height;
	float text_input_height;
	int current_indexed_past_message;
	ConsoleTextInput *text_input_widget;

	MessageConsole(Display *display)
		: FGUIScreen(display)
		, font((*gimmie_fonts())["DejaVuSansMono.ttf 19"])
		, active(false)
		, visibility_counter(0)
		, toggle_key(ALLEGRO_KEY_TILDE)
		, console_height(200)
		, text_input_widget(NULL)
		, text_input_height(al_get_font_line_height(font)*2)
		, console_padding(20)
		, current_indexed_past_message(0)
	{
		text_input_widget = new ConsoleTextInput(this, font, "", console_padding, -150, display->width()-console_padding*2, text_input_height);
		text_input_widget->gimmie_placement()->align_x = 0.0;
		text_input_widget->gimmie_placement()->align_y = 1.0;
	}

	void key_down_func() override
	{
		if (af::current_event->keyboard.keycode == toggle_key)
			toggle_console();

		if (!active) return;
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_UP)
		{
			current_indexed_past_message--;
		}
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			if (php::trim(text_input_widget->text) != "")
			{
				append_message(text_input_widget->text, 0);
				text_input_widget->set_text("");
			}
		}
	}

	void append_message(std::string text, int type)
	{
		message.push_back(ConsoleMessage(text, type));
	}

	void on_draw() override
	{
		al_draw_filled_rectangle(0, 0, display->width(), console_height * visibility_counter, color::darkblue);

		if (!active) return;

		int message_height = al_get_font_line_height(font);
		//for (int i=(int)message.size()-1; i>=0; i--)
		int message_index = message.size()-1;
		float message_y_start = console_height - console_padding*2 - text_input_height - message_height/2;
		for (int i=0; i<(int)message.size(); i++)
		{
			message[message_index].draw(font, console_padding, message_y_start - message_height*i);
			message_index--;
			//al_draw_text(font, color::white, 20, 20, ALLEGRO_ALIGN_LEFT, "hello world");
		}
	}

	void toggle_console()
	{
		if (active)
		{
			// hide
			motion.canimate(&visibility_counter, visibility_counter, 0, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			motion.canimate(&text_input_widget->gimmie_placement()->y, text_input_widget->gimmie_placement()->y, -150, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			text_input_widget->set_as_unfocused();
		}
		else
		{
			// show
			motion.canimate(&visibility_counter, visibility_counter, 1, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			motion.canimate(&text_input_widget->gimmie_placement()->y, text_input_widget->gimmie_placement()->y, console_height-console_padding, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			text_input_widget->set_as_focused();
		}

		active = !active;
	}

	void receive_signal(std::string const &signal, void *data) override
	{
		if (signal.find("console") == 0)
		{
			std::string *msg = static_cast<std::string *>(data);
			//append_message((*msg), 0);
			//std::cout << (*msg) << message.size() << std::endl;
		}
	}
};

*/