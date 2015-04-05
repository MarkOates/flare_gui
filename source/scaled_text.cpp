



#include <flare_gui/flare_gui.h>
#include <flare_gui/scaled_text.h>

#include <allegro_flare/useful.h> // for tostring
#include <flare_gui/widget_screen.h>
#include <allegro5/allegro_font.h>
#include <flare_gui/collision_box.h>




std::string FGUIScaledText::_get_font_index_str()
{
	return font_filename + " " + tostring((int)(font_size * render_scale));
}



void FGUIScaledText::refresh_render()
{
	// for easy life
	FGUIScreen *super_parent = static_cast<FGUIScreen *>(gimmie_super_parent());
	ALLEGRO_FONT *scaled_font = af::fonts[_get_font_index_str()];
	//placement2d *placement = gimmie_placement();

	// save the previous state
	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

	// create the bitmap
	if (render) al_destroy_bitmap(render);
	render = al_create_bitmap(al_get_text_width(scaled_font, text.c_str()), al_get_font_line_height(scaled_font));

	// set the target
	al_set_target_bitmap(render);

	// clear and draw the text
	al_clear_to_color(color::transparent);
	al_draw_text(scaled_font, color::white, 0, 0, ALLEGRO_ALIGN_LEFT, text.c_str());

	// restore the state
	al_restore_state(&previous_state);

	// update the placement data
	collision_area->placement.size.x = al_get_bitmap_width(render) / render_scale;
	collision_area->placement.size.y = al_get_bitmap_height(render) / render_scale;
}



FGUIScaledText::FGUIScaledText(FGUIParent *parent, float x, float y, std::string font_filename, int font_size, std::string text)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, 100, 100))
	, font_filename(font_filename)
	, font_size(font_size)
	, render_scale(3.0)
	, render(NULL)
	, text(text)
	, font_color(color::white)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScaledText");
	this->collision_area->placement.align.x = 0.0;
	this->no_focus = true;
	refresh_render();
}



FGUIScaledText::FGUIScaledText(FGUIParent *parent, float x, float y, std::string font_string, std::string text)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, 100, 100))
	, font_filename("")
	, font_size(14)
	, render_scale(3.0)
	, render(NULL)
	, text(text)
	, font_color(color::white)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScaledText");
	attr.set("id", "ScaledText" + tostring(widget_count));

	this->collision_area->placement.align.x = 0.0;
	this->no_focus = true;

	int last_space_pos = font_string.find_last_of(" ");
	if (last_space_pos == std::string::npos) font_filename = font_string;
	else
	{
		font_filename = font_string.substr(0, last_space_pos);
		font_size = atoi(font_string.substr(last_space_pos+1).c_str());
	}

	refresh_render();
}



void FGUIScaledText::on_draw()
{
	if (!render) return;

	al_draw_tinted_scaled_bitmap(render, font_color, 0, 0, al_get_bitmap_width(render), al_get_bitmap_height(render),
		0, 0, place.size.x, place.size.y, NULL);
}



void FGUIScaledText::set_font_color(ALLEGRO_COLOR color)
{
	font_color = color;
}



void FGUIScaledText::set_text(std::string text)
{
	if (this->text.compare(text)==0) return;
	this->text = text;
	refresh_render();
}