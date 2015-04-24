



#include <flare_gui/button.h>



#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <allegro_flare/motion.h>
#include <allegro_flare/color.h>

#include <flare_gui/widget.h>
#include <flare_gui/collision_box.h>

#include <allegro_flare/allegro_flare.h> // for af::time_now





FGUIButton::FGUIButton(FGUIParent *parent, float x, float y, float w, float h, std::string text)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, text(text)
	, content_alignment(0.5)
	, font(af::fonts["DroidSans.ttf 20"])
	, icon(NULL)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIButton");
	attr.set("id", "Button" + tostring(widget_count));
}



void FGUIButton::on_timer() {}



void FGUIButton::set_icon(ALLEGRO_BITMAP *icon)
{
	if (!icon) return;
	this->icon = icon;
}


#include <flare_gui/widget_screen.h>

void FGUIButton::on_draw()
{
	placement2d &placement = collision_area->placement;

	FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);

	// draw a hilight along the top
	al_draw_filled_rounded_rectangle(4, 4, place.size.x-4, 4+place.size.y/3, 4, 4, color::color(color::white, 0.05));

/*
	// PREVIOUS STYLING:	

	// the bottom shade
	float shade_depth = 5;
	al_draw_filled_rounded_rectangle(0, placement.size.y/2 + shade_depth, placement.size.x, placement.size.y+shade_depth, 2, 2, color::color(color::black, 0.1));

	// the button face
	al_draw_filled_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, color::hex("575962"));

	// the button outline
	al_draw_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, color::color(color::black, 0.2), 2);

	// draw a hilight along the top
	al_draw_line(3.5, 1, placement.size.x-3.5, 1, color::color(color::white, 0.3), 1);

	// draw the shaded bitmap
	// TODO: make this shade_down generated.
	// preload some good stuff into FGUIScreen::bitmap_bin;
	draw_stretched_bitmap(3, 3, placement.size.x-6, placement.size.y-6, af::bitmaps["shade_down.png"], 0, color::color(color::white, 0.2));
*/

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
		al_draw_bitmap(icon, start_x, placement.size.y/2 - al_get_bitmap_height(icon)/2, NULL);
		start_x += al_get_bitmap_width(icon);
	}
	if (font && !text.empty() && icon)
	{
		start_x += 10;
	}
	if (font && !text.empty())
	{
		al_draw_text(font, color::black, start_x, placement.size.y/2-al_get_font_line_height(font)/2+3, ALLEGRO_ALIGN_LEFT, text.c_str());
		al_draw_text(font, color::white, start_x, placement.size.y/2-al_get_font_line_height(font)/2, ALLEGRO_ALIGN_LEFT, text.c_str());
	}
}



void FGUIButton::set_text(std::string text)
{
	text = text;
}



void FGUIButton::on_click()
{
	FGUIWidget::on_click();

	placement2d &placement = collision_area->placement;

	af::motion.clear_animations_on(&placement.scale.x);
	af::motion.clear_animations_on(&placement.scale.y);
	af::motion.animate(&placement.scale.x, placement.scale.x, placement.scale.x*0.9, af::time_now, af::time_now+0.05, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.y, placement.scale.y, placement.scale.y*0.9, af::time_now, af::time_now+0.05, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.x, placement.scale.x*0.9, placement.scale.x, af::time_now+0.05, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
	af::motion.animate(&placement.scale.y, placement.scale.y*0.9, placement.scale.y, af::time_now+0.05, af::time_now+0.1, interpolator::doubleFastIn, NULL, NULL);
}



void FGUIButton::on_mouse_enter()
{
	placement2d &placement = collision_area->placement;

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
		//set_as_focused();
		on_click();
	}
}



void FGUIButton::on_joy_down()
{
	// NOTE! this is similar to the on_key_down button too.
	if (!mouse_over) return;

	if (af::current_event->joystick.button == 0)
	{
		//set_as_focused();
		on_click();
	}
}


//void FGUIButton::click_func() {}
