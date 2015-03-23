




#include <flare_gui/text_box.h>
#include <flare_gui/collision_box.h>
#include <boost/algorithm/string.hpp>

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
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUITextBox");
	attr.set("id", "TextBox" + tostring(widget_count));

	no_focus = true;
	create_word_width_pairs(text, font);
}




#include <allegro_flare/useful_php.h>

void FGUITextBox::create_word_width_pairs(std::string text, ALLEGRO_FONT *font)
{
	lines_of_word_width_pairs.clear();


	std::vector<std::string> word;




	boost::split(word, text, boost::is_any_of("\t \n\r")); ////// TODO:
															///// NOTE NOTE NOTE!!1
														   ////// THIS is the ONLY occourance of a boost function in
															///// flare_gui, requiring the inclusion of boost
															///// it should be replaced with an inhouse function




		std::vector<std::string> lines;
		lines = php::explode("\n", text);
		std::vector<std::string> final_token_list;

		//std::

		for (unsigned i=0; i<lines.size(); i++)
		{
			std::vector<std::string> words_in_this_line;
			boost::split(words_in_this_line, lines[i], boost::is_any_of(" ")); ////// TODO:
																///// NOTE NOTE NOTE!!1
															   ////// THIS is the ONLY occourance of a boost function in
																///// flare_gui, requiring the inclusion of boost
																///// it should be replaced with an inhouse function
			///final_word_width_list.(words_in_this_line);
			final_token_list.insert(final_token_list.end(), words_in_this_line.begin(), words_in_this_line.end());
			final_token_list.push_back("\n");
		}



	std::vector<word_width_pair> _word_width_pairs;
	for (unsigned i=0; i<final_token_list.size(); i++)
	{
		_word_width_pairs.push_back(word_width_pair(final_token_list[i], al_get_text_width(font, final_token_list[i].c_str())));
	}
	lines_of_word_width_pairs.push_back(_word_width_pairs);



	return;

	std::vector<word_width_pair> word_width_pairs;
	for (int i=0; i<(int)word.size(); i++)
	{
		word_width_pairs.push_back(word_width_pair(word[i], al_get_text_width(font, word[i].c_str())));
	}
	lines_of_word_width_pairs.push_back(word_width_pairs);
}





void FGUITextBox::set_text(std::string text)
{
	this->text = text;
	this->create_word_width_pairs(text, font);
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
	float width = gimmie_placement()->size.x;
	float line_height = al_get_font_line_height(font);

	std::vector<word_width_pair> word_width_pairs = lines_of_word_width_pairs[0];

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
