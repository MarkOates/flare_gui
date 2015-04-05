



#include <flare_gui/text.h>

#include <allegro_flare/color.h>
#include <flare_gui/collision_box.h>

#include <allegro_flare/useful.h>



FGUIText::FGUIText(FGUIParent *parent, float x, float y, ALLEGRO_FONT *font, std::string text)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, al_get_text_width(font, text.c_str()), al_get_font_line_height(font)))
	, text(text)
	, font(font)
	, font_color(color::white)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIText");
	attr.set("id", "Text" + tostring(widget_count));

	no_focus = true;
	this->collision_area->placement.align.x = 0.0;
}



void FGUIText::on_draw()
{
	al_draw_text(font, font_color, 0, 0, ALLEGRO_ALIGN_LEFT, text.c_str());
}



void FGUIText::set_font_and_text(ALLEGRO_FONT *font, std::string text)
{
	this->text = text;
	this->font = font;
	place.size.x = al_get_text_width(font, text.c_str());
	place.size.y = al_get_font_line_height(font);
}



void FGUIText::set_text(std::string text)
{
	set_font_and_text(this->font, text);
}



void FGUIText::set_font(ALLEGRO_FONT *font)
{
	set_font_and_text(font, this->text);
}



void FGUIText::set_font_color(const ALLEGRO_COLOR &font_color)
{
	this->font_color = font_color;
}