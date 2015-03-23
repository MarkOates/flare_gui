#ifndef FGUI_TEXT_HEADER
#define FGUI_TEXT_HEADER



#include <flare_gui/widget.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>




class FGUIText : public FGUIWidget
{
private:
	ALLEGRO_FONT *font;
	std::string text;
	ALLEGRO_COLOR font_color;
public:
	FGUIText(FGUIParent *parent, float x, float y, ALLEGRO_FONT *font, std::string text);

	// used by this
	void on_draw();

	// for you
	void set_font_and_text(ALLEGRO_FONT *font, std::string text); // used to be set()
	void set_text(std::string text);
	void set_font(ALLEGRO_FONT *font);
	void set_font_color(const ALLEGRO_COLOR &color);
};




#endif