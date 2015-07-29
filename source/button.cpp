



#include <flare_gui/widgets/button.h>



#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <allegro_flare/motion.h>
#include <allegro_flare/color.h>

#include <flare_gui/widget.h>
#include <flare_gui/surface_areas/box.h>
#include <flare_gui/style_assets.h>

#include <allegro_flare/allegro_flare.h> // for af::time_now





FGUIButton::FGUIButton(FGUIWidget *parent, float x, float y, float w, float h, std::string text)
	: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
	, text(text)
	, content_alignment(0.5)
	, font(FGUIStyleAssets::get_ui_font())
	, icon(NULL)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIButton");
	attr.set("id", "Button" + tostring(get_num_created_widgets()));
}



void FGUIButton::set_icon(ALLEGRO_BITMAP *icon)
{
	if (!icon) return;
	this->icon = icon;
}



void FGUIButton::set_content_alignment(float _content_alignment)
{
	content_alignment = _content_alignment;
}



#include <flare_gui/gui_screen.h>

void FGUIButton::on_draw()
{
	placement2d &placement = surface_area->placement;

	FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);

	// draw a gloss along the top
	// al_draw_filled_rounded_rectangle(4, 4, place.size.x-4, 4+place.size.y/3, 4, 4, color::color(color::white, 0.05));

	// draw the icon and/or the text
	// in this case, the icon is always drawn to the left of the text
	// with a padding of 10px

	// get the width of the inner content
	float inner_content_width = 0;
	float start_x = 0;
	if (icon) inner_content_width += al_get_bitmap_width(icon); // the width of the icon
	if (font && !text.empty() && icon) inner_content_width += 10; // the padding between the icon and the text
	if (font && !text.empty()) inner_content_width += al_get_text_width(font, text.c_str());
	start_x = placement.size.x * content_alignment - inner_content_width * content_alignment;

	// draw the stuff
	if (icon)
	{
		al_draw_bitmap(icon, start_x, placement.size.y/2 - al_get_bitmap_height(icon)/2, ALLEGRO_FLAGS_EMPTY);
		start_x += al_get_bitmap_width(icon);
	}
	if (font && !text.empty() && icon)
	{
		start_x += 10;
	}
	if (font && !text.empty())
	{
		al_draw_text(font, color::color(color::black, 0.4), start_x, placement.size.y/2-al_get_font_line_height(font)/2+1, ALLEGRO_ALIGN_LEFT, text.c_str());
		al_draw_text(font, color::white, start_x, placement.size.y/2-al_get_font_line_height(font)/2-1, ALLEGRO_ALIGN_LEFT, text.c_str());
	}
}



void FGUIButton::set_text(std::string text)
{
	text = text;
}



void FGUIButton::on_click()
{
	FGUIWidget::on_click();

	// automatic behavior for FGUIButton, will send an on_click to the parent when clicked this
	// represents a new use-friendly concept where widgets automatically send messages to their
	// parents for their most common purpose event.  In this case, a button. You click it.
	if (family.parent) family.parent->on_message(this, "on_click");

	placement2d &placement = surface_area->placement;

	af::motion.clear_animations_on(&placement.scale.x);
	af::motion.clear_animations_on(&placement.scale.y);
	af::motion.animate(&placement.scale.x, placement.scale.x, placement.scale.x*0.9, af::time_now, af::time_now+0.05, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.y, placement.scale.y, placement.scale.y*0.9, af::time_now, af::time_now+0.05, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.x, placement.scale.x*0.9, placement.scale.x, af::time_now+0.05, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.y, placement.scale.y*0.9, placement.scale.y, af::time_now+0.05, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
}



void FGUIButton::on_mouse_enter()
{
	placement2d &placement = surface_area->placement;

	af::motion.clear_animations_on(&placement.scale.x);
	af::motion.clear_animations_on(&placement.scale.y);
	af::motion.animate(&placement.scale.x, placement.scale.x, 1.1, af::time_now, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.y, placement.scale.y, 1.1, af::time_now, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);

	al_play_sample(af::samples["ui_hover.wav"], 0.2, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}



void FGUIButton::on_mouse_leave()
{
	af::motion.clear_animations_on(&place.scale.x);
	af::motion.clear_animations_on(&place.scale.y);
	af::motion.animate(&place.scale.x, place.scale.x, 1.0, af::time_now, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&place.scale.y, place.scale.y, 1.0, af::time_now, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
}



void FGUIButton::on_key_down()
{
	// NOTE! this is similar to the on_joy_down button too.
	if (!is_focused()) return;

	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_ENTER
		|| af::current_event->keyboard.keycode == ALLEGRO_KEY_SPACE
		)
	{
		on_click();
	}
}



void FGUIButton::on_joy_down()
{
	// NOTE! this is similar to the on_key_down button too.
	if (!mouse_over) return;

	if (af::current_event->joystick.button == 0)
	{
		on_click();
	}
}


