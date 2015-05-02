

#include "ui.h"

#include <iostream>


/* UIEntity */


int UIEntity::next_id = 0;

static const float FULL_ROTATION = 6.28318531;


UIEntity::UIEntity()
{
	id = next_id;
	next_id++;

	type = UI_ENTITY;

	/* these should be used by the widget developer */
	mouse_axes_func = ui_default_mouse_axes;
	mouse_up_func = ui_default_mouse_up;
	mouse_down_func = ui_default_mouse_down;
	set_disabled_func = ui_default_set_disabled;
	set_enabled_func = ui_default_set_enabled;
	timer_func = ui_default_timer;

	/* these should be null for the programmer to use */
	mouse_enter_func = NULL;
	mouse_leave_func = NULL;
	mouse_click_func = NULL;
	draw_func = NULL;

	click_in = false;

	display = al_get_current_display();

	disabled = false;

	mouse_over = false;
	mouse_enter = false;
	mouse_leave = false;
}

void ui_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	UIEntity *entity = static_cast<UIEntity *>(obj);
	if (entity->disabled) return;

	entity->mouse_enter = false;
	entity->mouse_leave = false;

	//todo: display
	bool over = true;
	if (ev->x < entity->x) over = false;
	else if (ev->x > entity->x+entity->w) over = false;
	else if (ev->y < entity->y) over = false;
	else if (ev->y > entity->y+entity->h) over = false;

	if (over && !entity->mouse_over) entity->mouse_enter = true;
	if (!over && entity->mouse_over) entity->mouse_leave = true;
	entity->mouse_over = over;

	if (entity->mouse_enter && entity->mouse_enter_func) entity->mouse_enter_func(entity, ev, user);
	if (entity->mouse_leave && entity->mouse_leave_func) entity->mouse_leave_func(entity, ev, user);
}

void ui_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	UIEntity *entity = static_cast<UIEntity *>(obj);
	if (entity->disabled) return;

	if (entity->mouse_over && entity->click_in && entity->mouse_click_func)
		entity->mouse_click_func(obj, e, user);
	
	entity->click_in = false;
}

void ui_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	UIEntity *entity = static_cast<UIEntity *>(obj);
	if (entity->disabled) return;
	if (entity->mouse_over) entity->click_in = true;
}

void ui_default_timer(void *obj, ALLEGRO_TIMER_EVENT *e, void *user)
{
	UIEntity *entity = static_cast<UIEntity *>(obj);
	if (entity->draw_func) entity->draw_func(obj, user);
}

void ui_default_set_disabled(void *obj, void *user)
{
	UIEntity *e = static_cast<UIEntity *>(obj);
	e->disabled = true;
}

void ui_default_set_enabled(void *obj, void *user)
{
	UIEntity *e = static_cast<UIEntity *>(obj);
	e->disabled = false;
}

int UIEntity::get_id() { return id; }




/* UIButton */

UIButton::UIButton(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string label)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->label = label;
	this->font = font;

	type = UI_BUTTON;

	background_color = al_color_html("f7f7f7");
	border_color = al_color_html("bdbdbd");
	inner_border_color = al_color_html("ffffff");
	text_color = al_color_name("black");
	hilight_color = al_map_rgba_f(0.6, 0.6, 0.6, 0.6);

	float AAAH_fade = 0;
	bool AAAH_direction = true;

	roundness = 3;
	label_displacement_x = 0;
	label_displacement_y = 0;

	//mouse_enter_func = ui_button_default_mouse_enter;
	//mouse_leave_func = ui_button_default_mouse_leave;
	mouse_axes_func = ui_button_default_mouse_axes;
	mouse_down_func = ui_button_default_mouse_down;
	mouse_up_func = ui_button_default_mouse_up;
	draw_func = ui_button_default_draw;

	set_disabled_func = ui_button_default_set_disabled;
	set_enabled_func = ui_button_default_set_enabled;
}


/* UIButton defaults */

void ui_button_default_set_disabled(void *obj, void *user)
{
	UIButton *button = static_cast<UIButton *>(obj);
	ui_default_set_disabled(obj, user);
	button->text_color = al_color_name("gray");
	button->border_color = al_color_html("f7f7f7");
	button->background_color = al_color_html("f7f7f7");
}

void ui_button_default_set_enabled(void *obj, void *user)
{
	ui_default_set_enabled(obj, user);
	UIButton *button = static_cast<UIButton *>(obj);
	button->text_color = al_color_name("black");
	button->border_color = al_color_html("bdbdbd");
	button->background_color = al_color_html("f7f7f7");
}
/*
void ui_button_default_mouse_enter(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	//ui_default_mouse_enter(obj, e);
	UIButton *button = static_cast<UIButton *>(obj);
	if (button->disabled) return;

	button->background_color = al_color_html("fffde5");

	if (button->click_in)
	{
		button->background_color = al_color_html("fefab3");
		button->label_displacement_x = 1;
		button->label_displacement_y = 1;
	}
}

void ui_button_default_mouse_leave(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	UIButton *button = static_cast<UIButton *>(obj);
	if (button->disabled) return;

	button->background_color = al_color_html("f7f7f7");

	if (button->click_in)
	{
		button->background_color = al_color_html("f7f7f7");
		button->label_displacement_x = 0;
		button->label_displacement_y = 0;
	}
}
*/

void ui_button_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	ui_default_mouse_axes(obj, e, user);
	UIButton *button = static_cast<UIButton *>(obj);
	if (button->disabled) return;

	if (button->mouse_enter)
	{
		button->background_color = al_color_html("fffde5");

		if (button->click_in)
		{
			button->background_color = al_color_html("fefab3");
			button->label_displacement_x = 1;
			button->label_displacement_y = 1;
		}
	}
	if (button->mouse_leave)
	{
		button->background_color = al_color_html("f7f7f7");

		if (button->click_in)
		{
			button->background_color = al_color_html("f7f7f7");
			button->label_displacement_x = 0;
			button->label_displacement_y = 0;
		}
	}
}

void ui_button_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	ui_default_mouse_down(obj, e, user);
	UIButton *button = static_cast<UIButton *>(obj);

	if (button->click_in)
	{
		button->background_color = al_color_html("fefab3");
		button->label_displacement_x = 1;
		button->label_displacement_y = 1;
	}
}

void ui_button_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	UIButton *button = static_cast<UIButton *>(obj);

	if (button->mouse_over && button->click_in)
	{
		button->background_color = al_color_html("fffde5");
		button->label_displacement_x = 0;
		button->label_displacement_y = 0;
	}

	ui_default_mouse_up(obj, e, user);
}

void ui_button_default_draw(void *obj, void *user)
{
	UIButton *b = static_cast<UIButton *>(obj);
	al_draw_filled_rounded_rectangle(b->x+0.5, b->y+0.5, b->x+b->w+0.5, b->y+b->h+0.5, b->roundness, b->roundness, b->background_color);
	al_draw_rounded_rectangle(b->x+0.5, b->y+0.5, b->x+b->w+0.5, b->y+b->h+0.5, b->roundness, b->roundness, b->border_color, 1.0);
	al_draw_rounded_rectangle(b->x+0.5+1, b->y+0.5+1, b->x+b->w+0.5-1, b->y+b->h+0.5-1, b->roundness, b->roundness, b->inner_border_color, 1.0);
	al_draw_filled_rectangle(b->x+3.5, b->y+3.5, b->x+b->w-3.5, b->y+b->h/2, b->hilight_color);

	if (b->font) al_draw_text(b->font, b->text_color,
		b->x+b->w/2+b->label_displacement_x, b->y+b->h/2-al_get_font_ascent(b->font)/2+b->label_displacement_y,
		ALLEGRO_ALIGN_CENTRE, b->label.c_str());

	if (b->click_in)
		al_draw_rounded_rectangle(b->x+0.5+1, b->y+0.5+1, b->x+b->w+0.5-1, b->y+b->h+0.5-1, b->roundness, b->roundness, al_color_name("yellow"), 1.0);
}




/* UIButton */

UIToggleButton::UIToggleButton(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string label)
	: UIButton(x, y, w, h, font, label)
{
	type = UI_TOGGLE_BUTTON;

	pressed = false;
	mouse_up_func = ui_toggle_button_default_mouse_up;
}

void ui_toggle_button_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user)
{
	UIToggleButton *button = static_cast<UIToggleButton *>(obj);

	if (button->mouse_over && button->click_in)
	{
		button->pressed = !button->pressed;
		if (!button->pressed) { button->label = "UnPressed"; }
		else { button->label = "Pressed"; }
		button->background_color = al_color_html("fffde5");
		button->label_displacement_x = 0;
		button->label_displacement_y = 0;
	}

	ui_default_mouse_up(obj, e, user);
}




/* UIHSlider */

UIHSlider::UIHSlider(float x, float y, float w)
//	: UIEntity()
{
	type = UI_SLIDER;

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = 24;

	val = 0.0f;
	handle_width = 0.0f;
	axis_padding = 12.0;

	mouse_down_func = ui_hslider_default_mouse_down;
	draw_func = ui_hslider_default_draw;
	mouse_axes_func = ui_hslider_default_mouse_axes;
	value_change_func = NULL;
}

void ui_hslider_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	ui_default_mouse_down(obj, ev, user);
	UIHSlider *slider = static_cast<UIHSlider *>(obj);
	if (slider->mouse_over)
	{
		float prev = slider->val;
		slider->val = max(0, min(1.0, (ev->x-slider->axis_padding-slider->x)/(slider->w-slider->axis_padding*2)));
		if (slider->value_change_func) slider->value_change_func(obj, slider->val, prev, user);
	}
}

void ui_hslider_default_draw(void *obj, void *user)
{
	UIHSlider *slider = static_cast<UIHSlider *>(obj);

	al_draw_filled_rounded_rectangle(slider->x, slider->y, slider->x+slider->w, slider->y+slider->h,
		5, 5, al_color_html("f9f9f9"));
	al_draw_rounded_rectangle(slider->x+0.5, slider->y+0.5, slider->x+slider->w+0.5, slider->y+slider->h+0.5,
		5, 5, al_color_html("f0f0f0"), 1.0);

	float radius = 6.5;

	al_draw_filled_rectangle(slider->x+slider->axis_padding, slider->y+slider->h/2-2,
		slider->x+slider->w-slider->axis_padding, slider->y+slider->h/2+2,
		al_color_name("lightgrey"));

	al_draw_rectangle(slider->x+0.5, slider->y+0.5+slider->h/2-2,
		slider->x+0.5+slider->w, slider->y+0.5+slider->h/2+2,
		al_color_html("f7f7f7"), 1.0);

	float circle_center = slider->x+slider->axis_padding+(slider->w-slider->axis_padding*2)*slider->val;
	al_draw_filled_circle(circle_center, slider->y+slider->h/2, radius, al_color_html("629f4a")); //f7f7f7

	ALLEGRO_COLOR hilight_color = al_map_rgba_f(0.6, 0.6, 0.6, 0.6);
	ALLEGRO_COLOR border_color = al_color_html("4e8638");

	al_draw_filled_rectangle(slider->x+3.5, slider->y+3.5, slider->x+slider->w-3.5, slider->y+slider->h/2, hilight_color);

	al_draw_circle(circle_center, slider->y+slider->h/2, radius-1, al_color_html("87bf70"), 1.0);
	al_draw_circle(circle_center, slider->y+slider->h/2, radius, border_color, 1.0);
}

void ui_hslider_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	ui_default_mouse_axes(obj, ev, user);
	UIHSlider *slider = static_cast<UIHSlider *>(obj);
	if (slider->click_in)
	{
		float prev = slider->val;
		slider->val = max(0, min(1.0, (ev->x-slider->axis_padding-slider->x)/(slider->w-slider->axis_padding*2)));
		if (slider->value_change_func) slider->value_change_func(obj, slider->val, prev, user);
	}
		
	al_draw_filled_rectangle(slider->x, slider->y,
		slider->x+slider->w, slider->y+slider->h,
		al_color_name("lightgrey"));
}





/* UIImage */

UIImage::UIImage(float x, float y, ALLEGRO_BITMAP *image)
{
	type = UI_IMAGE;

	this->x = x;
	this->y = y;
	this->w = al_get_bitmap_width(image);
	this->h = al_get_bitmap_height(image);
	this->image = image;
	this->opacity = 1.0;
	this->scale = 1.0;

	draw_func = ui_image_default_draw;
}

void ui_image_default_draw(void *obj, void *user)
{
	UIImage *img = static_cast<UIImage *>(obj);
	if (img->image) al_draw_tinted_scaled_bitmap(img->image,
						al_map_rgba_f(img->opacity, img->opacity, img->opacity, img->opacity),
						0, 0, al_get_bitmap_width(img->image), al_get_bitmap_height(img->image),
						img->x, img->y,
						al_get_bitmap_width(img->image)*img->scale,
						al_get_bitmap_height(img->image)*img->scale, NULL);
}




/* UIText */

UIText::UIText(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string text)
{
	type = UI_TEXT;

	this->x = x;
	this->y = y;
	this->text = text;
	this->font = font;
	this->w = w;
	this->h = h;
	color = al_color_name("black");
	draw_func = ui_text_default_draw;

	text_align = ALLEGRO_ALIGN_LEFT;
}

const ALLEGRO_FONT *UIText::get_font() { return font; }

std::string UIText::get_text() { return text; }

void UIText::set_text(std::string text)
{
	this->text = text;
}

void ui_text_default_draw(void *obj, void *user)
{
	UIText *t = static_cast<UIText *>(obj);
	
	if (!t->font) return;

	//al_draw_rectangle(t->x+0.5, t->y+0.5, t->x+t->w+0.5,
	//	t->y+t->h+0.5, al_color_name("lightgrey"), 1.0);

	float al = 0.0;
	if (t->text_align == ALLEGRO_ALIGN_RIGHT) al = 1.0;
	else if (t->text_align == ALLEGRO_ALIGN_CENTRE) al = 0.5;
	al_draw_text(t->get_font(), t->color, t->x+t->w*al, t->y,
		t->text_align, t->get_text().c_str());
}




/* UIDial */

UISliderDial::UISliderDial(float x, float y, float diameter)
{
	type = UI_SLIDER_DIAL;

	this->x = x;
	this->y = y;
	this->w = diameter;
	this->h = diameter;

	front_color = al_color_html("f11f8b");
	back_color = front_color;
	back_color.a = 0.1;
	back_color.r *= back_color.a;
	back_color.g *= back_color.a;
	back_color.b *= back_color.a;

	this->radius = diameter/2;
	this->inner_radius_percent = 0.6;
	this->circle_color = al_color_html("f7f7f7");

	this->val = 0.5;

	value_change_func = NULL;
	this->mouse_axes_func = ui_slider_dial_default_mouse_axes;
	this->draw_func = ui_slider_dial_default_draw;
}

void ui_slider_dial_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	ui_default_mouse_axes(obj, ev, user);
	UISliderDial *d = static_cast<UISliderDial *>(obj);
	float prev_val = d->val;
	if (d->click_in)
	{
		d->val -= (ev->dy * 0.004);
		if (d->val < 0) d->val = 0;
		if (d->val > 1) d->val = 1;
		std::cout << d->val << std::endl;
	}
	if (d->value_change_func) d->value_change_func(obj, d->val, prev_val, user);
}

void ui_slider_dial_default_draw(void *obj, void *user)
{
	UISliderDial *d = static_cast<UISliderDial *>(obj);
	//al_draw_filled_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5, d->radius, d->circle_color);

	float min_theta = -FULL_ROTATION/4 - FULL_ROTATION*0.5;
	float max_theta = -FULL_ROTATION/4 + FULL_ROTATION*0.5;
	float full_theta = max_theta - min_theta;

	al_draw_arc(d->x+d->radius+0.5, d->y+d->radius+0.5,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta, d->back_color, d->radius-d->radius*d->inner_radius_percent);

	al_draw_arc(d->x+d->radius+0.5, d->y+d->radius+0.5,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta*d->val, d->front_color, d->radius-d->radius*d->inner_radius_percent);

	float dial_point_x = cos(min_theta+d->val*full_theta);
	float dial_point_y = sin(min_theta+d->val*full_theta);

	//al_draw_line(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->x+d->w/2+0.5 + dial_point_x*d->radius*d->inner_radius_percent,
	//	d->y+d->h/2+0.5 + dial_point_y*d->radius*d->inner_radius_percent,
	//	d->front_color, 3.0);

	//background_color = al_color_html("f7f7f7");
	//border_color = al_color_html("bdbdbd");
	//inner_border_color = al_color_html("ffffff");
	//text_color = al_color_name("black");

	al_draw_filled_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5, d->radius*d->inner_radius_percent, d->circle_color);

	// the dot	
	al_draw_filled_circle(
		d->x+d->w/2+0.5 + dial_point_x*d->radius*d->inner_radius_percent*0.75,
		d->y+d->h/2+0.5 + dial_point_y*d->radius*d->inner_radius_percent*0.75,
		d->radius*d->inner_radius_percent*0.1, al_color_html("c0c0c0"));

	al_draw_filled_circle(
		d->x+d->w/2+0.5 + dial_point_x*d->radius*d->inner_radius_percent*0.75,
		d->y+d->h/2+0.5 + dial_point_y*d->radius*d->inner_radius_percent*0.75,
		d->radius*d->inner_radius_percent*0.1, al_color_html("c0c0c0"));

	// borders
	al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
		d->radius*d->inner_radius_percent-1, al_color_name("white"), 1.0);
	al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
		d->radius*d->inner_radius_percent, al_color_html("bdbdbd"), 1.0);
}




/* UIMeter */

UIMeter::UIMeter(float x, float y, float w, float h)
{
	type = UI_METER;

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	steps = 20;
	val = 0.1f;

	front_color = al_color_html("61d6fc");
	back_color = front_color;
	back_color.a = 0.1;
	back_color.r *= back_color.a;
	back_color.g *= back_color.a;
	back_color.b *= back_color.a;

	draw_func = ui_meter_default_draw;
}

void ui_meter_default_draw(void *obj, void *user)
{
	UIMeter *m = static_cast<UIMeter *>(obj);
	
	float spacing = m->h/m->steps/2.0;

	//al_draw_rectangle(m->x, m->y, m->x+m->w, m->y+m->h, al_color_name("pink"), 1.0);
	ALLEGRO_COLOR col = m->back_color;

	for (int i=0; i<(m->steps*2); i++)
	{
		if (i%2 == 1) continue;
		if (spacing*i > m->val*m->h) col = m->front_color;
		al_draw_filled_rectangle(m->x, m->y+spacing*i,
			m->x+m->w, m->y+spacing*i+spacing, col);
	}
}



/* UICoordinatePlotter */

UICoordinatePlotter::UICoordinatePlotter(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	x_val = 0.6;
	y_val = 0.6;

	this->point_color = al_color_html("386bc2");
	this->background_color = al_color_html("f6f6f6");
	this->line_color = al_color_html("a0a0a0");

	this->mouse_axes_func = ui_coordinate_plotter_default_mouse_axes;
	this->draw_func = ui_coordinate_plotter_default_draw;
	this->mouse_down_func = ui_coordinate_plotter_default_mouse_down;
}

void ui_coordinate_plotter_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	ui_default_mouse_down(obj, ev);
	UICoordinatePlotter *cp = static_cast<UICoordinatePlotter *>(obj);
	if (cp->click_in)
	{
		cp->x_val = (ev->x - cp->x)/cp->w;
		cp->y_val = (ev->y - cp->y)/cp->h;
		if (cp->x_val <= 0) cp->x_val = 0;
		if (cp->x_val >= 1) cp->x_val = 1;
		if (cp->y_val <= 0) cp->y_val = 0;
		if (cp->y_val >= 1) cp->y_val = 1;
	}
}

void ui_coordinate_plotter_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	ui_default_mouse_axes(obj, ev);
	UICoordinatePlotter *cp = static_cast<UICoordinatePlotter *>(obj);
	if (cp->click_in)
	{
		cp->x_val = (ev->x - cp->x)/cp->w;
		cp->y_val = (ev->y - cp->y)/cp->h;
		if (cp->x_val <= 0) cp->x_val = 0;
		if (cp->x_val >= 1) cp->x_val = 1;
		if (cp->y_val <= 0) cp->y_val = 0;
		if (cp->y_val >= 1) cp->y_val = 1;
	}
}

void ui_coordinate_plotter_default_draw(void *obj, void *user)
{
	UICoordinatePlotter *cp = static_cast<UICoordinatePlotter *>(obj);
	
	al_draw_filled_rectangle(cp->x, cp->y, cp->x+cp->w, cp->y+cp->h, cp->background_color);

	ALLEGRO_COLOR soft_line_color = cp->line_color;
	soft_line_color.a = 0.2;
	soft_line_color.r *= soft_line_color.a;
	soft_line_color.g *= soft_line_color.a;
	soft_line_color.b *= soft_line_color.a;

	al_draw_line(cp->x+0.5, cp->y+cp->y_val*cp->h+0.5, cp->x+cp->w+0.5, cp->y+cp->y_val*cp->h+0.5, soft_line_color, 1.0);
	al_draw_line(cp->x+cp->x_val*cp->w+0.5, cp->y+0.5, cp->x+cp->x_val*cp->w+0.5, cp->y+cp->h+0.5, soft_line_color, 1.0);

	al_draw_rectangle(cp->x+0.5, cp->y+0.5, cp->x+cp->w+0.5, cp->y+cp->h+0.5, cp->line_color, 1.0);
	al_draw_rectangle(cp->x+1.5, cp->y+1.5, cp->x+cp->w-0.5, cp->y+cp->h-0.5, al_color_name("white"), 1.0);
	
	al_draw_circle(cp->x+cp->x_val*cp->w+0.5, cp->y+cp->y_val*cp->h+0.5, 4.5, cp->point_color, 1.0);
	al_draw_circle(cp->x+cp->x_val*cp->w+0.5, cp->y+cp->y_val*cp->h+0.5, 7.5, cp->point_color, 2.5);
}




/* UIFrame */

UIFrame::UIFrame(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string text)
{
	type = UI_FRAME;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->font = font;
	this->text = text;

	roundness = 6.5;
	padding = 12;

	border_color = al_color_html("c0c0c0");
	fill_color = al_map_rgba_f(0, 0, 0, 0);
	inner_border_color = al_color_html("ffffff");

	draw_func = ui_frame_default_draw;
}

void ui_frame_default_draw(void *obj, void *user)
{
	UIFrame *f = static_cast<UIFrame *>(obj);

	al_draw_filled_rounded_rectangle(f->x-f->padding, f->y-f->padding,
		f->x+f->w+f->padding, f->y+f->h+f->padding,
		f->roundness, f->roundness, f->fill_color);

	al_draw_rounded_rectangle(f->x-f->padding+0.5, f->y-f->padding+0.5,
		f->x+f->w+f->padding+0.5, f->y+f->h+f->padding+0.5,
		f->roundness, f->roundness, f->border_color, 1.0);

	al_draw_rounded_rectangle(f->x-f->padding+0.5+1, f->y-f->padding+0.5+1,
		f->x+f->w+f->padding+0.5-1, f->y+f->h+f->padding+0.5-1,
		f->roundness, f->roundness, f->inner_border_color, 1.0);

	if (f->font && (f->text != ""))
	{
		float text_width = al_get_text_width(f->font, f->text.c_str());
		float text_height = al_get_font_ascent(f->font) + al_get_font_descent(f->font);

		al_draw_filled_rounded_rectangle(f->x-4, f->y-f->padding-al_get_font_ascent(f->font)/2-1 -2,
			f->x + text_width + 4, 
			f->y-f->padding-al_get_font_ascent(f->font)/2-1 + text_height + 2,
			3, 3, al_color_name("white"));

		al_draw_text(f->font, al_color_name("black"),
			f->x, f->y-f->padding-al_get_font_ascent(f->font)/2-1, NULL, f->text.c_str());
	}
}
