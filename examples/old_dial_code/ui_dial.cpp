#include "framework.h"

#include "ui.h"

Framework framework(800, 600);


ALLEGRO_COLOR mycolor;



void my_button_enter(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	UIButton *b = static_cast<UIButton *>(obj);
	b->AAAH_direction = true;
}

void my_button_leave(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
	UIButton *b = static_cast<UIButton *>(obj);
	b->AAAH_direction = false;
}


void custom_ui_button_draw(void *obj, void *user)
{
	UIButton *b = static_cast<UIButton *>(obj);

	b->background_color = al_color_html("505050");
	b->roundness = 6;

	if (b->AAAH_direction) b->AAAH_fade += 0.1;
	if (!b->AAAH_direction) b->AAAH_fade -= 0.05;
	if (b->AAAH_fade > 1) b->AAAH_fade = 1;
	if (b->AAAH_fade < 0) b->AAAH_fade = 0;

	ALLEGRO_COLOR border_color = al_color_html("70dcff");
	border_color.a = b->AAAH_fade;
	border_color.r *= border_color.a;
	border_color.g *= border_color.a;
	border_color.b *= border_color.a;

	al_draw_filled_rounded_rectangle(b->x, b->y,
		b->x+b->w, b->y+b->h,
		b->roundness, b->roundness, b->background_color);

	//if (b->mouse_over)
		al_draw_rounded_rectangle(b->x+0.5, b->y+0.5,
			b->x+b->w-0.5, b->y+b->h-0.5,
			b->roundness, b->roundness, border_color, 2.0*b->AAAH_fade);

	if (b->font) al_draw_text(b->font, b->text_color,
		b->x+b->w/2+b->label_displacement_x, b->y+b->h/2-al_get_font_ascent(b->font)/2+b->label_displacement_y,
		ALLEGRO_ALIGN_CENTRE, b->label.c_str());
}


void custom_ui_frame_draw(void *obj, void *user)
{
	UIFrame *f = static_cast<UIFrame *>(obj);

	f->fill_color = al_color_html("c9c2ae");
	f->fill_color.a = 0.03;
	f->fill_color.r *= f->fill_color.a;
	f->fill_color.g *= f->fill_color.a;
	f->fill_color.b *= f->fill_color.a;

	f->roundness = 11;

	al_draw_filled_rounded_rectangle(f->x-f->padding, f->y-f->padding,
		f->x+f->w+f->padding, f->y+f->h+f->padding,
		f->roundness, f->roundness, f->fill_color);

	al_draw_rounded_rectangle(f->x-f->padding+0.5, f->y-f->padding+0.5,
		f->x+f->w+f->padding-0.5, f->y+f->h+f->padding-0.5,
		f->roundness, f->roundness, f->fill_color, 3.0);

	//al_draw_rounded_rectangle(f->x-f->padding+0.5+1, f->y-f->padding+0.5+1,
	//	f->x+f->w+f->padding+0.5-1, f->y+f->h+f->padding+0.5-1,
	//	f->roundness, f->roundness, f->inner_border_color, 1.0);

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



void custom_ui_slider_dial_draw(void *obj, void *user)
{
	UISliderDial *d = static_cast<UISliderDial *>(obj);
	
	//al_draw_filled_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5, d->radius, d->circle_color);

	d->inner_radius_percent = 0.6;
	//d->back_color = al_color_html("404040");

	float min_theta = -FULL_ROTATION/4 - FULL_ROTATION*0.35;
	float max_theta = -FULL_ROTATION/4 + FULL_ROTATION*0.35;
	float full_theta = max_theta - min_theta;

	al_draw_arc(d->x+d->radius, d->y+d->radius,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta, d->back_color, d->radius-d->radius*d->inner_radius_percent);

	al_draw_arc(d->x+d->radius, d->y+d->radius,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta*d->val, d->front_color, d->radius-d->radius*d->inner_radius_percent);

	float dial_point_x = cos(min_theta+d->val*full_theta);
	float dial_point_y = sin(min_theta+d->val*full_theta);

	//al_draw_line(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->x+d->w/2+0.5 + dial_point_x*d->radius*d->inner_radius_percent,
	//	d->y+d->h/2+0.5 + dial_point_y*d->radius*d->inner_radius_percent,
	//	d->front_color, 3.0);

	ALLEGRO_COLOR dot_color = d->front_color;
	if (d->val==0) dot_color = d->back_color;

	al_draw_filled_circle(
		d->x+d->w/2 + dial_point_x*d->radius*d->inner_radius_percent*0.6,
		d->y+d->h/2 + dial_point_y*d->radius*d->inner_radius_percent*0.6,
		d->radius*d->inner_radius_percent*0.25, dot_color);


	//al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->radius*d->inner_radius_percent-1, al_color_name("white"), 1.0);
	//al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->radius*d->inner_radius_percent, al_color_html("a0a0a0"), 1.0);
}




void custom_ui_slider_dial_draw2(void *obj, void *user)
{
	UISliderDial *d = static_cast<UISliderDial *>(obj);
	
	//al_draw_filled_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5, d->radius, d->circle_color);

	float steps = 8;

	d->inner_radius_percent = 0.5;
	d->back_color = al_color_html("efefef");

	float min_theta = -FULL_ROTATION/4 - FULL_ROTATION*0.35;
	float max_theta = -FULL_ROTATION/4 + FULL_ROTATION*0.35;
	float full_theta = max_theta - min_theta;

	float val = d->val;
	val = (int)(d->val*steps)/steps;

	al_draw_arc(d->x+d->radius, d->y+d->radius,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta, d->back_color, d->radius-d->radius*d->inner_radius_percent);

	al_draw_arc(d->x+d->radius, d->y+d->radius,
		d->radius*d->inner_radius_percent + (d->radius-d->radius*d->inner_radius_percent)/2,
		min_theta, full_theta*val, d->front_color, d->radius-d->radius*d->inner_radius_percent);

	float dial_point_x = cos(min_theta+val*full_theta);
	float dial_point_y = sin(min_theta+val*full_theta);

	//al_draw_line(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->x+d->w/2+0.5 + dial_point_x*d->radius*d->inner_radius_percent,
	//	d->y+d->h/2+0.5 + dial_point_y*d->radius*d->inner_radius_percent,
	//	d->front_color, 3.0);

	ALLEGRO_COLOR dot_color = d->front_color;
	if (val==0) dot_color = d->back_color;

	al_draw_filled_circle(
		d->x+d->w/2 + dial_point_x*d->radius*d->inner_radius_percent*0.6,
		d->y+d->h/2 + dial_point_y*d->radius*d->inner_radius_percent*0.6,
		d->radius*d->inner_radius_percent*0.25, dot_color);


	//al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->radius*d->inner_radius_percent-1, al_color_name("white"), 1.0);
	//al_draw_circle(d->x+d->w/2+0.5, d->y+d->h/2+0.5,
	//	d->radius*d->inner_radius_percent, al_color_html("a0a0a0"), 1.0);
}




int meter_id = NULL;
int text_val_id = NULL;
UIEntity *ui_get_entity_by_id(int id);
void my_dial_change_func(void *obj, float new_value, float old_value, void *user)
{
	//UISliderDial *d = static_cast<UISliderDial *>(obj);
	UIMeter *m = (UIMeter *)ui_get_entity_by_id(meter_id);
	UIText *t = (UIText *)ui_get_entity_by_id(text_val_id);
	if (!m || !t)
	{
		std::cout << "NULL UIEntity.get_id() or UIText.get_id()" << std::endl;
		return;
	}
	m->val = new_value;
	t->text = tostring((int)(new_value*100));
}





vector<UIEntity *> ui_entity;

UIEntity *ui_get_entity_by_id(int id)
{
	for (int i=0; i<(int)ui_entity.size(); i++)
		if (ui_entity[i]->get_id() == id) return ui_entity[i];
	return NULL;
}




ALLEGRO_FONT *myfont = NULL;
ALLEGRO_FONT *bigfont = NULL;




/********************/

void initialize()
{
	myfont = al_load_font("data/fonts/Ger4ronL.ttf", -18, NULL);
	bigfont = al_load_font("data/fonts/SteelTongs.ttf", -29, NULL);
	//bigfont = get

	ui_entity.push_back(new UIFrame(235, 100, 200, 150, NULL, ""));
	ui_entity.back()->draw_func = custom_ui_frame_draw;

	for (int i=0; i<4; i++)
	{
		ui_entity.push_back(new UISliderDial(250+60*i, 200, 50));
		UISliderDial *d = static_cast<UISliderDial *>(ui_entity.back());
		//d->draw_func = custom_ui_slider_dial_draw;
		if (i==0) d->front_color = al_color_html("cf2f2f");
		if (i==1) d->front_color = al_color_html("3dbe3f");
		if (i==2) d->front_color = al_color_html("2964c9");
		if (i==3) d->x = 600;
	}

	UISliderDial *last_dial = ((UISliderDial *)ui_entity.back());
	last_dial->value_change_func = my_dial_change_func;

	ui_entity.push_back(new UIFrame(last_dial->x, last_dial->y, last_dial->w, last_dial->h, NULL, ""));
	ui_entity.back()->draw_func = custom_ui_frame_draw;
	//((UIFrame *)ui_entity.back())->text_align = ALLEGRO_ALIGN_CENTRE;

	ui_entity.push_back(new UIText(last_dial->x, last_dial->y+last_dial->h-last_dial->h*0.5, last_dial->w, 20, bigfont, "0"));
	((UIText *)ui_entity.back())->text_align = ALLEGRO_ALIGN_CENTRE;
	text_val_id = ui_entity.back()->get_id();

	for (int i=0; i<10; i++)
	{
		//ui_entity.push_back(new UIHSlider(100, 70+i*35, 130));
	}
	
	ui_entity.push_back(new UIMeter(700, 200, 30, 100));
	meter_id = ui_entity.back()->get_id();

	//((UISliderDial *)ui_entity.back())->user = my_dial_change_func;

	ui_entity.push_back(new UIFrame(300, 400, 300, 140, NULL, ""));
	ui_entity.back()->draw_func = custom_ui_frame_draw;

	ui_entity.push_back(new UIButton(300, 400, 100, 30, myfont, "open"));
	ui_entity.back()->draw_func = custom_ui_button_draw;
	ui_entity.back()->mouse_enter_func = my_button_enter;
	ui_entity.back()->mouse_leave_func = my_button_leave;

	ui_entity.push_back(new UIButton(300, 440, 100, 30, myfont, "load"));
	ui_entity.back()->draw_func = custom_ui_button_draw;
	ui_entity.back()->mouse_enter_func = my_button_enter;
	ui_entity.back()->mouse_leave_func = my_button_leave;

	ui_entity.push_back(new UIButton(300, 480, 100, 30, myfont, "save"));
	ui_entity.back()->draw_func = custom_ui_button_draw;
	ui_entity.back()->mouse_enter_func = my_button_enter;
	ui_entity.back()->mouse_leave_func = my_button_leave;

	ui_entity.push_back(new UICoordinatePlotter(100, 400, 130, 100));

	//ui_entity.push_back(new UIButton(200, 200, 100, 30, myfont, "Button"));
}

void key_down_func(Framework *f, ALLEGRO_EVENT *ev)
{
}

void mouse_down_func(Framework *f, ALLEGRO_EVENT *ev)
{
	for (int i=0; i<(int)ui_entity.size(); i++)
		if (ui_entity[i]->mouse_down_func)
			ui_entity[i]->mouse_down_func(ui_entity[i], &ev->mouse, NULL);
}

void mouse_up_func(Framework *f, ALLEGRO_EVENT *ev)
{
	for (int i=0; i<(int)ui_entity.size(); i++)
		if (ui_entity[i]->mouse_up_func)
			ui_entity[i]->mouse_up_func(ui_entity[i], &ev->mouse, NULL);
}

void mouse_axes_func(Framework *f, ALLEGRO_EVENT *ev)
{
	for (int i=0; i<(int)ui_entity.size(); i++)
		if (ui_entity[i]->mouse_axes_func)
			ui_entity[i]->mouse_axes_func(ui_entity[i], &ev->mouse, NULL);
}

void timer_func(Framework *f, ALLEGRO_EVENT *ev)
{
	al_clear_to_color(al_color_html("faf8f7"));
	al_draw_bitmap(get_image("thats_better.png"), 0, 0, NULL);

	for (int i=0; i<(int)ui_entity.size(); i++)
		if (ui_entity[i]->draw_func) ui_entity[i]->draw_func(ui_entity[i], NULL);

	al_draw_filled_rounded_rectangle(300-20, 110, 300-20+100, 110+70, 9, 9,
		al_map_rgba_f(((UISliderDial*)ui_entity[1])->val,
		((UISliderDial*)ui_entity[2])->val,
		((UISliderDial*)ui_entity[3])->val, 1.0));

	al_flip_display();
}

void display_close_func(Framework *f, ALLEGRO_EVENT *ev)
{
	f->abort_game();
}

/********************/

int main(int argc, char *argv[])
{
	initialize();
	framework.display_close_func = display_close_func;
	framework.timer_func = timer_func;
	framework.mouse_down_func = mouse_down_func;
	framework.mouse_up_func = mouse_up_func;
	framework.mouse_axes_func = mouse_axes_func;
	framework.run_loop();
	return 0;
}