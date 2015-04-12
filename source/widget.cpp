

#include <flare_gui/widget.h>
#include <flare_gui/widget_parent.h>
#include <allegro_flare/allegro_flare.h>
#include <flare_gui/widget_screen.h>
#include <allegro_flare/motion.h>




FGUIWidget::FGUIWidget(FGUIParent *parent, FGUICollisionArea *collision_area)
	: parent(parent)
	, collision_area(collision_area)
	, place(collision_area->placement)
	, mouse_down_on_over(false)
	, mouse_over(false)
	, focused(false)
	, dragging(false)
	, no_focus(false)
	, delete_me(false)
	//, fonts(*gimmie_fonts()) // < this means you will never be able to re-assign the widget to another parent
			  // lest you risk the previous owner's font bin being deleted.
			  // this may allude to the need of a global resource
{
	//std::cout << "FGUIWidget()" << std::endl;
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIWidget");
	attr.set("id", "Widget" + tostring(widget_count));

	if (parent) parent->children.register_as_child(this);
	num_active_widgets++;
	widget_count++;
	//std::cout << "FGUIWidget().num_active_widgets == " << num_active_widgets << std::endl;
}




FGUIWidget::~FGUIWidget()
{
	if (collision_area) delete collision_area;
	if (parent) parent->children.unregister_as_child(this);
	num_active_widgets--;
	
	std::cout << "~FGUIWidget() { type=" << attr.get(FGUI_ATTR__FGUI_WIDGET_TYPE) << " }" << std::endl;

	// clear all elements from the motion manager
	// I'm not sure about this.  There isn't really a fast, elegant way to guarantee
	// that all attributes that are potentialy being Motion.animated on are disabled
	// so there aren't any dangling pointers.  This is an attempt to offer one type
	// of solution, but it only covers the widget.placement elements.

	float* _elem[] = {
		&place.position.x, &place.position.y,
		&place.size.x, &place.size.y,
		&place.scale.x, &place.scale.y,
		&place.anchor.x, &place.anchor.y,
		&place.rotation
	};

	std::vector<float*> pacement_elements (_elem, _elem + sizeof(_elem) / sizeof(float*) );
	af::motion.clear_animations_on(pacement_elements);
}





bool FGUIWidget::is_focused()
{
	return focused;
}





bool FGUIWidget::is_mouse_over()
{
	return mouse_over;
}





FGUIWidget *FGUIWidget::gimmie_super_parent()
{
	FGUIWidget *widget = this;
	while(widget->parent) widget = widget->parent;
	return static_cast<FGUIWidget *>(widget);
}




FGUIScreen *FGUIWidget::gimmie_super_screen()
{
	return static_cast<FGUIScreen *>(gimmie_super_parent());
}




void FGUIWidget::bring_to_front()
{
	if (!parent) return;
	for (unsigned i=0; i<parent->children.children.size(); i++)
	{
		if (parent->children.children[i] == this)
		{
			parent->children.children.erase(parent->children.children.begin() + i);
			parent->children.children.push_back(this);
			return;
		}
	}
}




void FGUIWidget::send_message_to_parent(std::string message)
{
	if (parent) parent->receive_message(message);
}




void FGUIWidget::primary_timer_func()
{
	on_timer();
}




void FGUIWidget::draw_func()
{
	//placement2d *placement = gimmie_placement();
	place.start_transform();

	on_draw();
	
	// draws the focus rectangle if it's focused
	if (focused && gimmie_super_screen()->draw_focused_outline)
	{
		al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2), 5);
		al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::mix(gimmie_super_screen()->focused_outline_color, color::purple, 0.6+0.4*sin(af::time_now*3)), 1.5);
	}

	place.restore_transform();

	// draws the collision shape (for debugging)
	//collision_area->draw_bounding_area();
}



// widget developer functions:
void FGUIWidget::mouse_axes_func(float x, float y, float dx, float dy)
{
	bool mouse_over_now = collision_area->collides(x, y);
	if (parent && parent->mouse_blocked) mouse_over_now = false;

	if (mouse_over_now && !mouse_over) on_mouse_enter();
	else if (!mouse_over_now && mouse_over) on_mouse_leave();

	mouse_over = mouse_over_now;
	if (parent && mouse_over) parent->mouse_blocked = true;

	on_mouse_move(x, y, dx, dy);
	if (mouse_down_on_over)
	{
		dragging = true;
		on_drag(x, y, dx, dy);
	}

	if (af::current_event->mouse.dz != 0 || af::current_event->mouse.dw != 0) on_mouse_wheel();
}



void FGUIWidget::mouse_down_func()
{
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
	if (mouse_over && mouse_down_on_over) on_click();
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
	on_key_down();
}


void FGUIWidget::key_up_func()
{
	on_key_up();
}


void FGUIWidget::key_char_func()
{
	on_key_char();
}


void FGUIWidget::joy_up_func()
{
	on_joy_up();
}


void FGUIWidget::joy_axis_func()
{
	on_joy_axis();
}


void FGUIWidget::joy_down_func()
{
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

void FGUIWidget::on_click()
{
	// if the widget has a "on_click_send_message" key in its (DataAttr data), then send it to the parent
	if (attr.has("on_click_send_message")) send_message_to_parent(attr.get("on_click_send_message"));
}

void FGUIWidget::on_key_down() {}
void FGUIWidget::on_key_up() {}
void FGUIWidget::on_key_char() {}

void FGUIWidget::on_joy_down() {}
void FGUIWidget::on_joy_up() {}
void FGUIWidget::on_joy_axis() {}

void FGUIWidget::on_timer() {}
void FGUIWidget::on_draw()
{
	al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 4, 4, color::color(color::aliceblue, 0.2), 2.0);
}
void FGUIWidget::on_drag(float x, float y, float dx, float dy) {}



int FGUIWidget::num_active_widgets = 0;



int FGUIWidget::widget_count = 0;



int FGUIWidget::get_num_active_widgets()
{
	return num_active_widgets;
}



void FGUIWidget::set_as_focused()
	// iterates through all siblings and sets all parent's children to unfocused.
	// if the widget is not already focused, then set to focused and on_focus() is called
{
	// todo: this might require that the superparent is iterated
	if (parent) parent->set_focus_to(this);
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




FGUIWidget *FGUIWidget::get_element_by_id(std::string id, std::vector<FGUIWidget *> &widgets)
{
	for (unsigned i=0; i<widgets.size(); i++)
		if (widgets[i]->attr.matches("id", id)) return widgets[i];

	return NULL;
}



// some drawing primitives, I think these should go somewhere else and/or be implemented in a more
// customizable way :)  But for now this will get us started :)

void FGUIWidget::draw_inset(float x, float y, float w, float h)
{
	float roundness = 2;

	// draw the background
	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2));

	// draw a nice shade at the top (maybe this shoud be a 9-patch?... maybe not :)
	//draw_stretched_bitmap(1, 1, w-1, min(h, 16), (gimmie_super_screen()->bitmaps)["shade_down.png"], ::ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.2));


	// draw the top line shadow
	al_draw_line(x+roundness, y, x+w-roundness, y, color::color(color::black, 0.3), 1.0);

	// draw the bottom line hilight
	al_draw_line(x+roundness, y+h+1, x+w-roundness, y+h+1, color::color(color::white, 0.3), 1.0);
}


void FGUIWidget::draw_outset(float x, float y, float w, float h)
{
	// the bottom shade
	float shade_depth = 5;
	al_draw_filled_rounded_rectangle(0, place.size.y/2 + shade_depth, place.size.x, place.size.y+shade_depth, 2, 2, color::color(color::black, 0.1));

	// the button face
	al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::hex("3a3c47"));//color::hex("575962"));

	// the button outline
	al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2), 2);

	// draw a hilight along the top
	al_draw_line(3.5, 1, place.size.x-3.5, 1, color::color(color::white, 0.3), 1);

	// draw the shaded bitmap
	draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, af::bitmaps["shade_down.png"], 0, color::color(color::white, 0.2));
}
