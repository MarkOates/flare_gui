

#include <allegro_flare/allegro_flare.h>

#include <flare_gui/widgets/scrollbar.h>

#include <allegro5/allegro_primitives.h>

#include <flare_gui/collision_box.h>

#include <allegro_flare/useful.h> // for limit



FGUIScrollBar::ScrollUpButton::ScrollUpButton(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIButton(parent, x, y, w, h, "") {}
void FGUIScrollBar::ScrollUpButton::on_click()
{
	FGUIButton::on_click();
	static_cast<FGUIScrollBar *>(family.parent)->step_up();
}



FGUIScrollBar::ScrollDownButton::ScrollDownButton(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIButton(parent, x, y, w, h, "") {}
void FGUIScrollBar::ScrollDownButton::on_click()
{
	FGUIButton::on_click();
	static_cast<FGUIScrollBar *>(family.parent)->step_down();
}



FGUIScrollBar::ScrollRail::ScrollRail(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, current_mouse_y(0)
{}
void FGUIScrollBar::ScrollRail::on_draw()
{
	al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::mix(color::transparent, color::hex("3a3c47"), 0.4));
	al_draw_rectangle(0.5, 0.5, place.size.x-0.5, place.size.y-0.5, color::color(color::black, 0.2), 1.0);
}
void FGUIScrollBar::ScrollRail::on_mouse_move(float x, float y, float dx, float dy)
{
	current_mouse_y = y;
}
void FGUIScrollBar::ScrollRail::on_click()
{
	// find the direction of the jump based on the handle's position
	FGUIScrollBar *slider_parent = static_cast<FGUIScrollBar *>(family.parent);
	if (slider_parent->handle->place.position.y < current_mouse_y) slider_parent->jump_down();	
	else slider_parent->jump_up();	
}



FGUIScrollBar::ScrollHandle::ScrollHandle(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, min_y(0)
	, max_y(0)
{
}
void FGUIScrollBar::ScrollHandle::set_min_max_coordinate_position(float min_val, float max_val)
{
	min_y = min_val;
	max_y = max_val;
}
void FGUIScrollBar::ScrollHandle::on_drag(float x, float y, float dx, float dy)
{
	place.position.y = limit<float>(min_y+place.size.y/2, max_y-place.size.y/2, place.position.y+dy);
	family.parent->on_change();
}
void FGUIScrollBar::ScrollHandle::on_draw()
{
	FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
}
float FGUIScrollBar::ScrollHandle::get_position()
{
	return (place.position.y - min_y - place.size.y/2.0) / (max_y - min_y - place.size.y);
}
void FGUIScrollBar::ScrollHandle::set_position(float position_in_unit_value)
{
	// TODO: check and see if an on_change is necessairy
	// float previous_pos = place.position.y;

	float previous_pos = place.position.y;

	position_in_unit_value = limit<float>(0.0, 1.0, position_in_unit_value);
	float new_pos = position_in_unit_value * (max_y - min_y - place.size.y) + (min_y + place.size.y/2.0);
	place.position.y = new_pos; 

	if (place.position.y != previous_pos) family.parent->on_change();
}




FGUIScrollBar::FGUIScrollBar(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, rail(NULL)
	, handle(NULL)
	, up_button(NULL)
	, down_button(NULL)
{
	// create the rail
	rail = new ScrollRail(this, 0, 0, w, h);
	rail->place.align = vec2d(0, 0);

	// create the up and down buttons
	up_button = new ScrollUpButton(this, w/2, w/2, w, w);
	down_button = new ScrollDownButton(this, w/2, h-w/2, w, w);

	// create the handle
	handle = new ScrollHandle(this, w/2, h/2, w, w*3);
	handle->set_min_max_coordinate_position(w, h-w);
}
float FGUIScrollBar::get_position()
{
	return handle->get_position();
}
void FGUIScrollBar::jump_down()
{
	float jump_rate = 0.3;
	handle->set_position(handle->get_position() + jump_rate);
}
void FGUIScrollBar::jump_up()
{
	float jump_rate = 0.3;
	handle->set_position(handle->get_position() - jump_rate);
}
void FGUIScrollBar::step_up()
{
	float step_rate = 0.1;
	handle->set_position(handle->get_position() - step_rate);
}
void FGUIScrollBar::step_down()
{
	float step_rate = 0.1;
	handle->set_position(handle->get_position() + step_rate);
}
void FGUIScrollBar::set_position(float position_in_unit_value)
{
	handle->set_position(position_in_unit_value);
}
void FGUIScrollBar::on_key_down()
{
	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_DOWN) step_down();
	else if (af::current_event->keyboard.keycode == ALLEGRO_KEY_UP) step_up();
}
void FGUIScrollBar::on_draw() {}





