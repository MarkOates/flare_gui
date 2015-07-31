


#include <flare_gui/widgets/toggle_button.h>


#include <allegro_flare/allegro_flare.h> // for af::fonts

#include <flare_gui/surface_areas/box.h>
#include <flare_gui/style_assets.h>





FGUIToggleButton::FGUIToggleButton(FGUIWidget *parent, float x, float y, float w, float h, std::string _text)
	: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
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




bool FGUIToggleButton::toggle()
	// returns true if the button is pressed
{
	pressed = !pressed;
	on_change();
	return pressed;
}



bool FGUIToggleButton::set_as_pressed()
	// returns true if the state was changed,
	// returns false if it stayed the same
{
	if (!pressed)
	{
		toggle();
		return true;
	}
	return false;
}



bool FGUIToggleButton::set_as_unpressed()
	// returns true if the state was changed,
	// returns false if it stayed the same
{
	if (pressed)
	{
		toggle();
		return true;
	}
	return false;
}



void FGUIToggleButton::silently_set_as_pressed()
{
	pressed = true;
}



void FGUIToggleButton::silently_set_as_unpressed()
{
	pressed = false;
}



void FGUIToggleButton::on_draw()
{
	if (pressed) FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y);
	else FGUIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
	
	ALLEGRO_FONT *font = FGUIStyleAssets::get_ui_font();
	al_draw_text(font, color::white, place.size.x/2, place.size.y/2-al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTRE, text.c_str());
}




void FGUIToggleButton::on_click() { toggle(); }




void FGUIToggleButton::on_change()
{
	send_message_to_parent("on_change");
}



