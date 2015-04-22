


#include <flare_gui/flare_gui.h>
#include <allegro5/allegro_primitives.h>

#include <flare_gui/progress_bar.h>

#include <allegro_flare/color.h>
#include <allegro_flare/useful.h>

#include <flare_gui/collision_box.h>


#include <flare_gui/widget_screen.h>




FGUIProgressBar::FGUIProgressBar(FGUIParent *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, val(0)
	, update_speed(0.4)
	, current_color(color::dodgerblue)
	, normal_color(color::dodgerblue)
	, update_color(color::aquamarine)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIProgressBar");
	attr.set("id", "ProgressBar" + tostring(widget_count));
}



void FGUIProgressBar::set_val(float normalized_val)
{
	normalized_val = limit<float>(0, 1, normalized_val);
	af::motion.cmove_to(&val, normalized_val, update_speed, interpolator::doubleFastIn);

	current_color = color::mix(update_color, normal_color, 0.5);
	af::motion.cmove_to(&current_color.r, normal_color.r, update_speed);
	af::motion.cmove_to(&current_color.g, normal_color.g, update_speed);
	af::motion.cmove_to(&current_color.b, normal_color.b, update_speed);
}



void FGUIProgressBar::set_val(float _val, float min, float max)
{
	float normalized_val = (_val - min) / (max - min);
	set_val(normalized_val);
}



void FGUIProgressBar::on_draw()
{
	float roundness = place.size.y/4;
	float inset_padding = 3;

	// draw the background
	al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, color::color(color::black, 0.2));

	// draw the background outline
	al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, color::color(color::black, 0.2), 2.0);
		


	// because of the rounded corners, the min drawing
	// width of the bar
	float min_width = 15/place.size.x; // 15 pixels
	float _val = val;
	if (_val < min_width) _val = min_width;

	// draw the progress bar
	al_draw_filled_rounded_rectangle(inset_padding, inset_padding,
		place.size.x*_val - inset_padding, place.size.y - inset_padding,
		roundness, roundness, color::color(current_color, 0.8));

	// draw the shaded bitmap
	draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, af::bitmaps["shade_down.png"], 0, color::color(color::white, 0.2));

	// draw the progress bar outline
	//al_draw_rounded_rectangle(inset_padding, inset_padding,
	//	place.size.x*val - inset_padding*2, place.size.y - inset_padding,
	//	roundness, roundness, color::color(color::aliceblue, 0.3), 2.0);
}


