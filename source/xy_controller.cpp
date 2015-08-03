


#include <flare_gui/widgets/xy_controller.h>


#include <flare_gui/style_assets.h>




FGUIXYController::FGUIXYController(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
	, mouse_pos(0)
	, marker(0.5, 0.5)
	, guide_color(color::white)
	, guide_opacity(0.3)
{
}




void FGUIXYController::set_point(float x, float y)
{
	vec2d prev_marker = marker;
	marker = vec2d(limit<float>(0.0f, 1.0f, x), limit<float>(0.0f, 1.0f, y));

	// check if there was a change
	if (basically_equal(marker.x, prev_marker.x) || !basically_equal(marker.y, prev_marker.y))
		on_change();
}




vec2d FGUIXYController::get_point()
{
	return marker;
}




void FGUIXYController::on_mouse_down()
{
	set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);	
}




void FGUIXYController::on_mouse_move(float x, float y, float dx, float dy)
{
	place.transform_coordinates(&x, &y);
	mouse_pos = vec2d(x, y);
	
	if (mouse_down_on_over)
		set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);	
}




void FGUIXYController::on_draw()
{
	FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, color::color(color::black, 0.1));

	// draw the guides
	vec2d local_marker = vec2d(marker.x * place.size.x, marker.y * place.size.y);

	ALLEGRO_COLOR guide_mixed_color = color::color(color::white, guide_opacity);
	al_draw_line(local_marker.x, 0, local_marker.x, place.size.y, color::color(color::white, guide_opacity), 1.0);
	al_draw_line(0, local_marker.y, place.size.x, local_marker.y, color::color(color::white, guide_opacity), 1.0);

	al_draw_circle(local_marker.x, local_marker.y, 10, color::color(color::dodgerblue, 0.2), 6);
}



void FGUIXYController::on_change()
{
	this->send_message_to_parent("on_change");
}




