



// come back to this, Mark, this is a cool idea.

/*

class MessageConsole : public FGUIScreen
{
public:

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
	ALLEGRO_FONT *font;
	int toggle_key;
	std::vector<ConsoleMessage> message;
	float console_padding;
	float console_height;
	float text_input_height;
	int current_indexed_past_message;
	FGUITextInput *text_input_widget;

	MessageConsole(Display *display)
		: FGUIScreen(display)
		, font(af::fonts["DroidSerif.ttf 19"])
		, active(false)
		, visibility_counter(0)
		, toggle_key(ALLEGRO_KEY_TILDE)
		, console_height(200)
		, text_input_widget(NULL)
		, text_input_height(al_get_font_line_height(font)*2)
		, console_padding(20)
		, current_indexed_past_message(0)
	{
		text_input_widget = new FGUITextInput(this, font, "", console_padding, -150, display->width()-console_padding*2, text_input_height);
		text_input_widget->place.align.x = 0.0;
		text_input_widget->place.align.y = 1.0;
	}

	void key_down_func() override
	{
		if (af::current_event->keyboard.keycode == toggle_key)
		{
			toggle_console();
		}
		else
		{
			switch(af::current_event->keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				current_indexed_past_message--;
			break;
			case ALLEGRO_KEY_ENTER:
				if (php::trim(text_input_widget->get_text()) != "")
				{
					append_message(text_input_widget->get_text(), 0);
					text_input_widget->set_text("");
				}
			break;
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

	bool toggle_console()
	{
		if (active)
		{
			// hide
			af::motion.canimate(&visibility_counter, visibility_counter, 0, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			af::motion.canimate(&text_input_widget->place.position.y, text_input_widget->place.position.y, -150, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			text_input_widget->set_as_unfocused();
		}
		else
		{
			// show
			af::motion.canimate(&visibility_counter, visibility_counter, 1, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			af::motion.canimate(&text_input_widget->place.position.y, text_input_widget->place.position.y, console_height-console_padding, af::time_now, af::time_now+0.2, interpolator::fastIn, NULL, NULL);
			text_input_widget->set_as_focused();
		}

		active = !active;

		return active;
	}

	void receive_signal(std::string const &signal, void *data) override
	{
		if (signal.find("console") == 0)
		{
			std::string *msg = static_cast<std::string *>(data);
		}
	}
};

*/