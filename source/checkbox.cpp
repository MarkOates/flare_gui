


#include <allegro_flare/allegro_flare.h>

#include <flare_gui/widgets/checkbox.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>
#include <flare_gui/collision_box.h>

#include <flare_gui/widget_screen.h>

#include <allegro_flare/fonts/font_font_awesome.h>




FGUICheckbox::FGUICheckbox(FGUIWidget *parent, float x, float y, float size)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, size, size))
	, checked(false)
	, check_placement(0, 0, size, size, -0.4, 0.0, 0.0, 0.45, 0.75)
	, check_color(color::color(color::mix(color::deepskyblue, color::cyan, 0.9)))
	, check_opacity(0)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUICheckbox");
	attr.set("id", "Checkbox" + tostring(widget_count));
}



bool FGUICheckbox::is_checked()
{
	return checked;
}



void FGUICheckbox::set_color(ALLEGRO_COLOR col)
{
	check_color = col;
}



void FGUICheckbox::toggle()
{
	checked = !checked;

	float speed = 0.2;
	if (checked)
	{
		// check reveals
		af::motion.cmove_to(&check_opacity, 1.0, speed * 0.5, interpolator::doubleFastIn);
		af::motion.cmove_to(&check_placement.scale.x, 1.0, speed*0.85, interpolator::fastOut);
		af::motion.cmove_to(&check_placement.scale.y, 1.0, speed*0.85, interpolator::fastOut);
		af::motion.cmove_to(&check_placement.rotation, -0.1, speed, interpolator::fastOut);
	}
	else
	{
		// check removes
		af::motion.cmove_to(&check_opacity, 0.0, speed, interpolator::doubleFastOut);
		af::motion.cmove_to(&check_placement.scale.x, 0.0, speed, interpolator::slowIn);
		af::motion.cmove_to(&check_placement.scale.y, 0.0, speed, interpolator::slowIn);
		af::motion.cmove_to(&check_placement.rotation, -0.4, speed, interpolator::linear);
	}

	on_change();
}



void FGUICheckbox::on_mouse_down()
{
	toggle();
}



void FGUICheckbox::on_key_char()
{
	if (!focused) return;
	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_SPACE
		|| af::current_event->keyboard.keycode == ALLEGRO_KEY_ENTER)
	{
		toggle();
	}
}



void FGUICheckbox::on_joy_down()
{
	if (!mouse_over) return;

	// TODO: this should not be hard-coded as button 0, it should be coded
	// as the "ENTER" button or "ACTIVATE" or whatever in the joystick config
	if (af::current_event->joystick.button == 0)
		toggle();
}



void FGUICheckbox::on_draw()
{
	float check_inset = place.size.x*0.2;
	ALLEGRO_BITMAP *gradient = af::bitmaps["shade_down.png"];
	

	// draw the background shape
	al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2));
	al_draw_rounded_rectangle(1, 1, place.size.x-1, place.size.y-1, 3, 3, color::color(color::black, 0.2), 2.0);
	al_draw_line(2, place.size.y, place.size.x-2, place.size.y, color::color(color::white, 0.2), 1.0);


	// draw the gradient
	if (gradient)
		al_draw_tinted_scaled_bitmap(gradient, color::color(color::white, 1.0), 0, 0, al_get_bitmap_width(gradient), al_get_bitmap_height(gradient),
			check_inset, check_inset, place.size.x-check_inset*2, place.size.y-check_inset*2, ALLEGRO_FLIP_VERTICAL);


	// draw the check
	ALLEGRO_FONT *font_awesome = af::fonts["FontAwesome.otf " + tostring(((int)(place.size.x*1.75)))];

	static ALLEGRO_USTR *ustr = al_ustr_new("");
	al_ustr_set_chr(ustr, 0, font_awesome::ok);
	check_placement.position.x = place.size.x/2 + place.size.x*0.1;
	check_placement.position.y = place.size.y/2 + place.size.y*0.3;
	check_placement.size.x = al_get_ustr_width(font_awesome, ustr);
	check_placement.size.y = al_get_font_line_height(font_awesome);
	
	if (checked)
	{
		float boxfade_opacity = 1.0 - check_opacity;
		al_draw_filled_rectangle(check_inset, check_inset, place.size.x-check_inset, place.size.y-check_inset, color::color(check_color, boxfade_opacity));
	}
	check_placement.start_transform();

	al_draw_ustr(font_awesome, color::color(color::black, 0.3), 0, 3, NULL, ustr);
	al_draw_ustr(font_awesome, check_color, 0, 0, NULL, ustr);

	check_placement.restore_transform();
}






