

#include <flare_gui/widget.h>


#include <allegro_flare/allegro_flare.h>

#include <flare_gui/gui_screen.h>
#include <flare_gui/family.h>
#include <flare_gui/style_assets.h>



FGUIWidget::FGUIWidget(FGUIWidget *parent, FGUISurfaceArea *surface_area)
	//: parent(parent)
	: family(parent)
	, surface_area(surface_area)
	, place(surface_area->placement)
	, mouse_down_on_over(false)
	, mouse_over(false)
	, focused(false)
	, dragging(false)
	, no_focus(false)
	, delete_me(false)
	, mouse_is_blocked(false)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIWidget");
	attr.set("id", "Widget" + tostring(widget_count));

	if (parent) parent->family.register_as_child(this);
	num_active_widgets++;
	widget_count++;

	if (!FGUIWidget::widget_icon)
		FGUIWidget::widget_icon = FGUIWidget::create_widget_icon(32);
}





FGUIWidget::~FGUIWidget()
{
	family.delete_all(); // from FGUIParent

	if (surface_area) delete surface_area;
	if (family.parent) family.parent->family.unregister_as_child(this);
	num_active_widgets--;
	
	std::cout << "~FGUIWidget() { type=" << attr.get(FGUI_ATTR__FGUI_WIDGET_TYPE) << " }" << std::endl;

	// clear all elements from the motion manager
	// I'm not sure about this.  There isn't really a fast, elegant way to guarantee
	// that all attributes that are potentialy being Motion.animated on are disabled
	// so there aren't any dangling pointers.  This is an attempt to offer one type
	// of solution, but it only covers the widget.placement elements.

	if (surface_area)
	{
		float* _elem[] = {
			&surface_area->placement.position.x, &surface_area->placement.position.y,
			&surface_area->placement.size.x, &surface_area->placement.size.y,
			&surface_area->placement.scale.x, &surface_area->placement.scale.y,
			&surface_area->placement.anchor.x, &surface_area->placement.anchor.y,
			&surface_area->placement.rotation
		};

		std::vector<float*> pacement_elements (_elem, _elem + sizeof(_elem) / sizeof(float*) );
		af::motion.clear_animations_on(pacement_elements);
	}
}






bool FGUIWidget::is_focused()
{
	return focused;
}





bool FGUIWidget::is_mouse_over()
{
	return mouse_over;
}





void FGUIWidget::bring_to_front()
{
	if (!family.parent) return;
		// hmm.. the logic of this should be executed by the parent, not this child
		// TODO: this function should simply call something like family->bring_to_front(this)
		// and not all this stuff:
	for (unsigned i=0; i<family.parent->family.children.size(); i++)
	{
		if (family.parent->family.children[i] == this)
		{
			family.parent->family.children.erase(family.parent->family.children.begin() + i);
			family.parent->family.children.push_back(this);
			return;
		}
	}
}




void FGUIWidget::send_message_to_parent(std::string message)
{
	if (family.parent) family.parent->on_message(this, message);
}




void FGUIWidget::primary_timer_func()
{
	on_timer();

	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->primary_timer_func();
}




void FGUIWidget::draw_func()
{
	if (surface_area) surface_area->placement.start_transform();

	on_draw();

	family.draw_all(); // TODO: should be renamed to draw_children();
	
	// draws the focus rectangle if it's focused
	/*
	if (focused && gimmie_super_screen()->draw_focused_outline)
	{
		al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 3, 3, color::color(color::black, 0.2), 5);
		al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 3, 3, color::mix(gimmie_super_screen()->focused_outline_color, color::purple, 0.6+0.4*sin(af::time_now*3)), 1.5);
	}
	*/

	if (surface_area) surface_area->placement.restore_transform();

	// draws the collision shape (for debugging)
	//surface_area->draw_bounding_area();
}



// widget developer functions:
void FGUIWidget::mouse_axes_func(float x, float y, float dx, float dy)
{
	// start by transforming the coordinates for the children

	float tmx = x;
	float tmy = y;
	float tmdx = dx;
	float tmdy = dy;

	surface_area->placement.transform_coordinates(&tmx, &tmy);
	surface_area->placement.transform_coordinates(&tmdx, &tmdy);

	if (family.parent && family.parent->mouse_is_blocked) mouse_is_blocked = true;
	else mouse_is_blocked = false;

	for (int i=(int)family.children.size()-1; i>=0; i--)
		family.children[i]->mouse_axes_func(tmx, tmy, dx, dy);  // I'm not sure why these are dx/dy, but it works correctly this way



	// then proceed with the execution of the function

	if (surface_area)
	{
		bool mouse_over_now = surface_area->collides(x, y);
		if (family.parent && family.parent->mouse_is_blocked) mouse_over_now = false;

		if (mouse_over_now && !mouse_over) on_mouse_enter();
		else if (!mouse_over_now && mouse_over) on_mouse_leave();

		mouse_over = mouse_over_now;
		if (family.parent && mouse_over) family.parent->mouse_is_blocked = true;
	}

	on_mouse_move(x, y, dx, dy); // TODO I think this needs to be the translated coordinates, and maybe even should be on the on_drag() call below as well
	if (mouse_down_on_over)
	{
		dragging = true;
		on_drag(x, y, dx, dy);
	}

	if (af::current_event->mouse.dz != 0 || af::current_event->mouse.dw != 0) on_mouse_wheel();
}



void FGUIWidget::mouse_down_func()
{
	// call this function on the children first
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->mouse_down_func();

	// now do the execution of the function
	if (mouse_over)
	{
		mouse_down_on_over = true;
		on_mouse_down();
		focused = true;
		on_focus();
	}
	else
	{
		if (focused)
		{
			focused = false;
			on_blur();
		}
	}
}



void FGUIWidget::mouse_up_func()
{
	// call this function on the children first
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->mouse_up_func();

	// then continue with the function on self
	if (mouse_over && mouse_down_on_over)
	{
		// if the widget has a "on_click_send_message" key in its (DataAttr data), then send it to the parent
		if (attr.has("on_click_send_message")) send_message_to_parent(attr.get("on_click_send_message"));
		on_click();
	}
	mouse_down_on_over = false;
	if (dragging)
	{
		dragging = false;
		on_drop();
	}
	on_mouse_up();
}



void FGUIWidget::key_down_func()
{
	// call this function on the children first
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->key_down_func();

	// then call on self
	on_key_down();
}


void FGUIWidget::key_up_func()
{
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->key_up_func();

	on_key_up();
}


void FGUIWidget::key_char_func()
{
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->key_char_func();
	
	on_key_char();
}


void FGUIWidget::joy_up_func()
{
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->joy_up_func();

	on_joy_up();
}


void FGUIWidget::joy_axis_func()
{
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->joy_axis_func();

	on_joy_axis();
}


void FGUIWidget::joy_down_func()
{
	for (unsigned i=0; i<family.children.size(); i++)
		family.children[i]->joy_down_func();


	if (mouse_over && af::current_event->joystick.button == 0)
	{
		set_as_focused();
	}

	on_joy_down();
}


// user functions:
void FGUIWidget::on_focus() {}
void FGUIWidget::on_blur() {}
void FGUIWidget::on_drop() {}

void FGUIWidget::on_mouse_enter() {}
void FGUIWidget::on_mouse_leave() {}
void FGUIWidget::on_mouse_move(float x, float y, float dx, float dy) {}
void FGUIWidget::on_mouse_down() {}
void FGUIWidget::on_mouse_up() {}
void FGUIWidget::on_mouse_wheel() {}
void FGUIWidget::on_click() {}

void FGUIWidget::on_key_down() {}
void FGUIWidget::on_key_up() {}
void FGUIWidget::on_key_char() {}

void FGUIWidget::on_joy_down() {}
void FGUIWidget::on_joy_up() {}
void FGUIWidget::on_joy_axis() {}

void FGUIWidget::on_timer() {}
void FGUIWidget::on_draw()
{
	if (surface_area)
	{
		al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 4, 4, color::color(color::aliceblue, 0.2), 2.0);
		if (FGUIWidget::widget_icon) al_draw_tinted_bitmap(FGUIWidget::widget_icon, color::color(color::white, 0.1), place.size.x/2-al_get_bitmap_width(FGUIWidget::widget_icon)/2, place.size.y/2-al_get_bitmap_height(FGUIWidget::widget_icon)/2, 0);
	}
}
void FGUIWidget::on_drag(float x, float y, float dx, float dy) {}
void FGUIWidget::on_change() {}
void FGUIWidget::on_message(FGUIWidget *sender, std::string message) {};



int FGUIWidget::num_active_widgets = 0;



int FGUIWidget::widget_count = 0;



ALLEGRO_BITMAP *FGUIWidget::widget_icon = NULL;



int FGUIWidget::get_num_created_widgets()
{
	return widget_count;
}



int FGUIWidget::get_num_active_widgets()
{
	return num_active_widgets;
}



void FGUIWidget::set_as_focused()
	// iterates through all siblings and sets all parent's children to unfocused.
	// if the widget is not already focused, then set to focused and on_focus() is called
{
	// todo: this might require that the superparent is iterated
	if (family.parent) family.parent->family.set_focus_to_child(this);
}



void FGUIWidget::set_as_unfocused()
	// if the widget is currently focused, chages the state to !focused and calls on_blur().
{
	if (is_focused())
	{
		focused=false;
		on_blur();
	}
}





// some drawing primitives, I think these should go somewhere else and/or be implemented in a more
// customizable way :)  But for now this will get us started :)

void FGUIWidget::draw_inset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
	// draw the background
	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2));

	// draw a nice shade at the top (maybe this shoud be a 9-patch?... maybe not :)
	//draw_stretched_bitmap(1, 1, w-1, min(h, 16), (gimmie_super_screen()->bitmaps)["shade_down.png"], ::ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.2));


	// draw the top line shadow
	al_draw_line(x+roundness, y, x+w-roundness, y, color::color(color::black, 0.3), 1.0);

	// draw the bottom line hilight
	al_draw_line(x+roundness, y+h+1, x+w-roundness, y+h+1, color::color(color::white, 0.3), 1.0);
}


void FGUIWidget::draw_outset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
	float border_thickness = 2.0;
	float texture_inset = border_thickness/2;

	// the button face
	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, col);//color::hex("575962"));

	// draw a hilight along the top
	al_draw_line(x+1, y+1, x+w-1, y+1, color::color(color::white, 0.1), 1);

	// the button outline
	al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2), border_thickness);

	// draw the shaded bitmap
	ALLEGRO_BITMAP *shade_down = FGUIStyleAssets::get_shade_down_gradient();
	draw_stretched_bitmap(x+texture_inset, y+texture_inset, x+w-texture_inset*2, y+h-texture_inset*2, shade_down, 0, color::color(color::white, 0.2));
}



#include <allegro_flare/image_processing.h>

ALLEGRO_BITMAP *FGUIWidget::create_widget_icon(int size, const ALLEGRO_COLOR &front_color, const ALLEGRO_COLOR &back_color)
{
	float scale = 4.0; // 4.0 is essentially equivelent to 4x FSAA
	size *= scale;

	ALLEGRO_BITMAP *surface = al_create_bitmap(size, size);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(surface);
	al_clear_to_color(back_color);

	// draw stuff here
	float gear_scale = size / 64.0;
	float gear_radius = size/2;
	float inner_gear_thickness = 10.5 * gear_scale;
	float hw = 4 * gear_scale;
	float hh = 2.5 * gear_scale;

	int num_gears = 9;

	placement2d gear_place;
	gear_place.position = vec2d(size/2, size/2);
	gear_place.anchor = vec2d(0, gear_radius);

	al_draw_circle(size/2, size/2, gear_radius-hh*2-inner_gear_thickness/2, front_color, inner_gear_thickness);
	for (auto i=0; i<num_gears; i++)
	{
		gear_place.start_transform();
		al_draw_filled_rectangle(-hw, -hh*2-inner_gear_thickness*0.05, hw, 0, front_color);
		gear_place.restore_transform();
		gear_place.rotation += TAU/num_gears;
	}

	al_restore_state(&state);

	
	ALLEGRO_BITMAP *scaled = create_scaled_render(surface, size/scale, size/scale);

	al_destroy_bitmap(surface);

	return scaled;
}



