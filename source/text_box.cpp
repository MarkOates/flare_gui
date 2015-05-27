




#include <flare_gui/widgets/text_box.h>
#include <flare_gui/surface_areas/box.h>

#include <allegro_flare/allegro_flare.h> // for af::fonts







FGUITextBox::FGUITextBox(FGUIWidget *parent, float x, float y, float w, float h, std::string text)
	: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
	, font(af::fonts["DroidSans.ttf 20"])
	, text(text)
	, text_color(color::black)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUITextBox");
	attr.set("id", "TextBox" + tostring(get_num_created_widgets()));

	no_focus = true;
}







void FGUITextBox::set_font(ALLEGRO_FONT *font)
{
	this->font = font;
}





void FGUITextBox::set_text(std::string text)
{
	this->text = text;
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
	if (font) al_draw_multiline_text(font, text_color, 0, 0, place.size.x, ALLEGRO_ALIGN_LEFT, text.c_str());
}



