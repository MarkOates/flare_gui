

#include <flare_gui/widgets/toggle_button.h>

#include <allegro_flare/allegro_flare.h> // for af::fonts

#include <flare_gui/surface_areas/box.h>





FGUIToggleButton::FGUIToggleButton(FGUIWidget *parent, float x, float y, float w, float h, std::string _text)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, pressed(false)
	, text(_text)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIToggleButton");
	attr.set("id", "ToggleButton" + tostring(get_num_created_widgets()));
}




void FGUIToggleButton::set_text(std::string text)
{
	this->text = text;
}




void FGUIToggleButton::toggle()
{
	pressed = !pressed;
	on_change();
}




void FGUIToggleButton::on_draw()
{
	if (pressed) FGUIWidget::draw_inset(0, 0, place.size.x, place.size.y);
	else FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
	
	ALLEGRO_FONT *font = af::fonts["DroidSans.ttf 18"];
	al_draw_text(font, color::white, place.size.x/2, place.size.y/2-al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTRE, text.c_str());
}




void FGUIToggleButton::on_click() { toggle(); }




void FGUIToggleButton::on_change()
{
	send_message_to_parent("on_change");
}



