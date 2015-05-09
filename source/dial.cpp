

#include <flare_gui/widgets/dial.h>

#include <allegro_flare/allegro_flare.h> // for bins
#include <allegro_flare/useful.h> // for tostring

#include <flare_gui/collision_circle.h>




FGUIDial::FGUIDial(FGUIWidget *parent, float x, float y, float diameter)
	: FGUIWidget(parent, new FGUICollisionCircle(x, y, diameter/2))
	, val(0.4)
	, radius(diameter/2)
	, sensitivity(0.002)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIDial");
	attr.set("id", "Dial" + tostring(get_num_created_widgets()));
}



void FGUIDial::set_value(float unit_val)
{
	float prev_val = val;
	val = limit<float>(0, 1, unit_val);
	if (basically_equal(prev_val, val)) on_change();
}



float FGUIDial::get_value()
{
	return val;
}



void FGUIDial::on_mouse_down()
{
	al_hide_mouse_cursor(af::current_event->mouse.display);
}



void FGUIDial::on_mouse_up()
{
	al_show_mouse_cursor(af::current_event->mouse.display);
}



void FGUIDial::on_drag(float x, float y, float dx, float dy)
{
	float adjusted_val = val;
	adjusted_val -= dy * sensitivity;
	set_value(adjusted_val);

	// prevent the mouse cursor from moving on the screen
	al_set_mouse_xy(af::current_event->mouse.display, x-dx, y-dy);
}



void FGUIDial::on_draw()
{
	// some visual styling
	ALLEGRO_COLOR button_color = al_color_html("575962");
	ALLEGRO_COLOR back_color = al_color_html("404040");
	ALLEGRO_COLOR front_color = color::dodgerblue;
	float bar_thickness = 7;
	float inner_radius = radius - bar_thickness*2;
	float wideness = 0.74; // value from [0 - 1].  default is 0.74

	// calculate the positions of the arcs and arc points
	float min_theta = -FULL_ROTATION/4 - FULL_ROTATION*(wideness/2);
	float max_theta = -FULL_ROTATION/4 + FULL_ROTATION*(wideness/2);
	float full_theta = max_theta - min_theta;
	// get a vector pointing from the center to the value on this dial 
	float dial_point_x = cos(min_theta+val*full_theta);
	float dial_point_y = sin(min_theta+val*full_theta);

	// draw the body
	al_draw_filled_circle(radius, radius, radius, button_color);

	// draw the background slider
	al_draw_arc(radius, radius,
		inner_radius + (bar_thickness)/2,
		min_theta, full_theta, back_color, bar_thickness);

	// draw the foreground slider
	al_draw_arc(radius, radius,
		inner_radius + (bar_thickness)/2,
		min_theta, full_theta*val, front_color, bar_thickness);

	// if the dial is at 0, then the dot color should be the OFF color
	ALLEGRO_COLOR marker_color = front_color;
	if (val==0) marker_color = back_color;

	// draw a line, from the center of the dial to the value
	//al_draw_line(radius, radius,
	//	radius + dial_point_x*inner_radius,
	//	radius + dial_point_y*inner_radius,
	//	marker_color, 3.0);

	// draw a dot, marking the position of the dial
	al_draw_filled_circle(
		radius + dial_point_x*(inner_radius - bar_thickness),
		radius + dial_point_y*(inner_radius - bar_thickness),
		bar_thickness*0.5, marker_color);

	// draw outlines (and inner-outlines) for the circle buton
	//al_draw_circle(radius, radius,
	//	inner_radius-1, al_color_name("white"), 1.0);
	al_draw_circle(radius, radius,
		inner_radius, color::color(color::black, 0.2), 2);

	// draw the shade down
	float shade_inset = 3;
	ALLEGRO_BITMAP *shade = af::bitmaps["shade_down_circle.png"];
	al_draw_tinted_scaled_bitmap(shade, color::color(color::white, 0.2),
		0, 0, al_get_bitmap_width(shade), al_get_bitmap_height(shade),
		shade_inset + radius-inner_radius, shade_inset + radius-inner_radius,
		inner_radius*2 - shade_inset*2, inner_radius*2 - shade_inset*2, 0);

	// draw a bounding rectangle
	//al_draw_rectangle(0, 0, place.size.x, place.size.y, color::dodgerblue, 1.0);
}



void FGUIDial::on_change()
{
	send_message_to_parent("on_change");
}



