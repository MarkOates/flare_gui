




#include <flare_gui/text_box.h>
#include <flare_gui/collision_box.h>

#include <allegro_flare/useful.h> // just for tostring, meh




FGUITextBox::word_width_pair::word_width_pair(std::string word, int width)
	: word(word)
	, width(width)
{}





bool FGUITextBox::word_width_pair::is_carriage_return()
{
	if (word == "\n") return true;
	return false;
}




FGUITextBox::FGUITextBox(FGUIParent *parent, ALLEGRO_FONT *font, std::string text, float x, float y, float width, float height)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, width, height))
	, font(font)
	, text(text)
	, text_color(color::black)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUITextBox");
	attr.set("id", "TextBox" + tostring(widget_count));

	no_focus = true;
	create_word_width_pairs(text, font);
}











std::vector<std::string> split_if_any_delim(std::string text, std::string delims)
{
	std::vector<std::string> result;

	size_t last_found_pos = 0;
	size_t found_pos = 0;

	found_pos=text.find_first_of(delims,0);
	while (found_pos!=std::string::npos)
	{
		result.push_back(text.substr(last_found_pos, found_pos-last_found_pos));
		last_found_pos = found_pos+1;
		found_pos=text.find_first_of(delims,found_pos+1);
	}

	result.push_back(text.substr(last_found_pos)); // grab the last token

	return result;
}







#include <allegro_flare/useful_php.h>

void FGUITextBox::create_word_width_pairs(std::string text, ALLEGRO_FONT *font)
{
	lines_of_word_width_pairs.clear();






		std::vector<std::string> lines;
		lines = php::explode("\n", text);
		std::vector<std::string> final_token_list;



		for (unsigned i=0; i<lines.size(); i++)
		{
			std::vector<std::string> words_in_this_line;
			words_in_this_line = split_if_any_delim(lines[i], "\t \n\r");

			final_token_list.insert(final_token_list.end(), words_in_this_line.begin(), words_in_this_line.end());
			final_token_list.push_back("\n");
		}



	std::vector<word_width_pair> _word_width_pairs;
	for (unsigned i=0; i<final_token_list.size(); i++)
	{
		_word_width_pairs.push_back(word_width_pair(final_token_list[i], al_get_text_width(font, final_token_list[i].c_str())));
	}
	lines_of_word_width_pairs.push_back(_word_width_pairs);

}





void FGUITextBox::set_text(std::string text)
{
	this->text = text;
	this->create_word_width_pairs(text, font);
}





std::string FGUITextBox::get_text()
{
	return this->text;
}




void FGUITextBox::set_text_color(ALLEGRO_COLOR col)
{
	this->text_color = col;
}




void FGUITextBox::on_draw()
{
	// this is without letter-spacing

	float width_of_space = al_get_text_width(font, " ");
	float x_cursor = 0;
	float y_cursor = 0;
	float next_x = 0;
	float width = place.size.x;
	float line_height = al_get_font_line_height(font);

	std::vector<word_width_pair> word_width_pairs = lines_of_word_width_pairs[0];


	//al_draw_text(font, color::black, 100, 100, 0, "This is just a test");


	//al_get_text_dimensions(font, 

	for (int i=0; i<(int)word_width_pairs.size(); i++)
	{
		next_x = x_cursor + word_width_pairs[i].width;
		if (next_x > width || word_width_pairs[i].is_carriage_return())
		{
			x_cursor = 0;
			y_cursor += line_height;
			continue;
		}
		al_draw_text(font, text_color, x_cursor, y_cursor, NULL, word_width_pairs[i].word.c_str());
		x_cursor = x_cursor + word_width_pairs[i].width + width_of_space;
	}
}
