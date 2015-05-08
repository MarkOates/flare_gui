#ifndef __AF_TEXT_BOX_OLD_HEADER
#define __AF_TEXT_BOX_OLD_HEADER




#include <string>
#include <flare_gui/widget.h>
#include <allegro5/allegro_font.h>




class FGUITextBox : public FGUIWidget
{
private:
	class word_width_pair
	{
	public:
		std::string word;
		int width;
		word_width_pair(std::string word, int width);
		bool is_carriage_return();
	};

	void create_word_width_pairs(std::string text, ALLEGRO_FONT *font);

	std::vector<std::vector<word_width_pair>> lines_of_word_width_pairs;

	ALLEGRO_FONT *font;
	ALLEGRO_COLOR text_color;
	std::string text;

public:
	FGUITextBox(FGUIWidget *parent, float x, float y, float w, float h, std::string text);

	void set_text(std::string text);
	std::string get_text();
	void set_text_color(ALLEGRO_COLOR color);

	void on_draw() override;
};







#endif
