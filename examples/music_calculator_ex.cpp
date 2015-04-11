

#include <flare_gui/flare_gui.h>
#include <flare_gui/music_notation.h>
#include <allegro_flare/drawing_interfaces/drawing_interface_allegro5.h>

#include <algorithm>



class Project : public FGUIScreen
{
public:
	ALLEGRO_BITMAP *music_render;
	FGUITextInput *text_input;
	FGUIText *notation_text;
	Project() : FGUIScreen(af::create_display())
		, music_render(al_create_bitmap(200, 80))
		, text_input(NULL)
		, notation_text(NULL)
	{
		text_input = new FGUITextInput(this, af::fonts["DroidSans.ttf 20"], "0 1 2 3 4 5", display->center(), display->height()*2/3, 300, 40);
		notation_text = new FGUIText(this, display->center()-text_input->place.size.x/2, display->height()*2/3+45,
			af::fonts["DroidSans.ttf 20"], "[notation_string]");
	}
	void primary_timer_func() override
	{
		static int last_width = 0;
		DrawingInterfaceAllegro5 drawing_interface;
		MusicNotation music_notation(&drawing_interface);

		FGUIScreen::primary_timer_func();
		last_width = music_notation.draw(display->center() - last_width/2, display->height()/3,
			"{staff_color=white color=white spacing=fixed}" + convert_cell_format_to_notation(text_input->get_text()));

		std::string result_text = convert_cell_format_to_notation(text_input->get_text()).c_str();

		notation_text->set_text(result_text);
	}
	static std::string convert_cell_format_to_notation(std::string cell)
	{
		// each note is in the format "[0q 6 2h 8 1 0]" which is
		// accidental scale_degree octave duration dots is_rest
		//b7q. 

		// format
		//optional b* = num of flats
		//optional #* = optional numf of sharps
		//optional n == natural
		//optional v* == octave down
		//optional ^* == octave up
		//optional duration w=whole h=half q=quarter e=eighth s=16th t=32nd i=64th o=128th (default is q)
		//optional (\.)* number of dots
		//find each of the notes (regex would be perfect for this)

		std::string notation_string;

		std::vector<std::string> notes = php::explode(" ", cell);

		for (unsigned i=0; i<notes.size(); i++)
		{
			if (notes[i].empty()) continue;
			size_t duration_find = notes[i].find_last_of("whqestio");
			std::string duration_char = ((duration_find==std::string::npos) ? "q" : notes[i].substr(duration_find, 1));

			int scale_degree = 0;
			size_t scale_degree_pos = notes[i].find_first_of("0123456789");
			if (scale_degree_pos != std::string::npos) scale_degree = atoi(notes[i].substr(scale_degree_pos, 1).c_str());

			notation_string += duration_char + tostring(scale_degree);
		}

		return notation_string;
	}
};


int main(int argc, char **argv)
{
	af::initialize();
	Project *p = new Project();
	af::run_loop();
}
