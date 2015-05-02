#ifndef __UI_HEADER
#define __UI_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


#include <string>


enum UI_TYPE
{
	UI_ENTITY,
	UI_TEXT,
	UI_BUTTON,
	UI_TOGGLE_BUTTON,
	UI_SLIDER,
	UI_SLIDER_DIAL,
	UI_IMAGE,
	UI_FRAME,
	UI_METER
};



class UIEntity
{
protected:
	static int next_id;
	int id;
	UI_TYPE type;

public:
	ALLEGRO_BITMAP *click_mask;

	void *parent;
	void *first_child;
	void *next_sibling;

	bool mouse_over, mouse_enter, mouse_leave, click_in;
	float x, y, w, h;
	ALLEGRO_DISPLAY *display;
	bool disabled;

	/* low-level - for the UI developer */
	void (*timer_func)(void *obj, ALLEGRO_TIMER_EVENT *e, void *user);
	void (*mouse_up_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);
	void (*mouse_down_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);
	void (*mouse_axes_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);
	void (*set_disabled_func)(void *obj, void *user);
	void (*set_enabled_func)(void *obj, void *user);
	void (*draw_func)(void *obj, void *user);

	/* high-level - for the UI user */
	void (*mouse_enter_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);
	void (*mouse_leave_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);
	void (*mouse_click_func)(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user);

	UIEntity();

	int get_id();
};

void ui_default_set_disabled(void *obj, void *user=NULL);
void ui_default_set_enabled(void *obj, void *user=NULL);
void ui_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_default_timer(void *obj, ALLEGRO_TIMER_EVENT *e, void *user=NULL);





class UIButton : public UIEntity
{
public:
	std::string label;
	ALLEGRO_FONT *font;
	ALLEGRO_COLOR background_color, border_color, inner_border_color, text_color, hilight_color;
	int roundness;
	int label_displacement_x, label_displacement_y;

	float AAAH_fade;
	bool AAAH_direction;

	UIButton(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string label);
};

//void ui_button_default_mouse_enter(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
//void ui_button_default_mouse_leave(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_button_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_button_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_button_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);
void ui_button_default_draw(void *obj, void *user=NULL);
void ui_button_default_set_disabled(void *obj, void *user=NULL);
void ui_button_default_set_enabled(void *obj, void *user=NULL);




class UIToggleButton : public UIButton
{
public:
	bool pressed;

	UIToggleButton(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string label);
};

void ui_toggle_button_default_mouse_up(void *obj, ALLEGRO_MOUSE_EVENT *e, void *user=NULL);




class UIHSlider : public UIEntity
{
public:
	double val;
	double handle_width;
	double axis_padding;

	void (*value_change_func)(void *obj, float new_value, float old_value, void *user);

	UIHSlider(float x, float y, float w);
};

void ui_hslider_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user=NULL);
void ui_hslider_default_draw(void *obj, void *user=NULL);
void ui_hslider_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user=NULL);




class UIImage : public UIEntity
{
public:
	ALLEGRO_BITMAP *image;
	float scale, opacity;

	UIImage(float x, float y, ALLEGRO_BITMAP *image);
};


void ui_image_default_draw(void *obj, void *user=NULL);




class UIText : public UIEntity
{
public:
	ALLEGRO_COLOR color;
	std::string text;
	ALLEGRO_FONT *font;
	int text_align;

	std::string get_text();
	void UIText::set_text(std::string text);

	const ALLEGRO_FONT *get_font();
	UIText(float x, float y, float w, float h, ALLEGRO_FONT *font, std::string text);
};


void ui_text_default_draw(void *obj, void *user=NULL);




class UISliderDial : public UIEntity
{
public:
	ALLEGRO_COLOR back_color, front_color, circle_color;
	float val;
	float radius, inner_radius_percent;

	void (*value_change_func)(void *obj, float new_value, float old_value, void *user);

	UISliderDial(float x, float y, float diameter);
};


void ui_slider_dial_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev,  void *user=NULL);
void ui_slider_dial_default_draw(void *obj, void *user=NULL);



class UIMeter : public UIEntity
{
public:
	ALLEGRO_COLOR back_color, front_color;
	float val;
	int steps;

	UIMeter(float x, float y, float w, float h);
};

void ui_meter_default_draw(void *obj, void *user=NULL);



class UICoordinatePlotter : public UIEntity
{
public:
	ALLEGRO_COLOR background_color, line_color, point_color;
	float x_val, y_val;

	UICoordinatePlotter(float x, float y, float w, float h);
};

void ui_coordinate_plotter_default_mouse_down(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user=NULL);
void ui_coordinate_plotter_default_mouse_axes(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user=NULL);
void ui_coordinate_plotter_default_draw(void *obj, void *user=NULL);




class UIFrame : public UIEntity
{
public:
	float padding, roundness;
	ALLEGRO_FONT *font;
	std::string text;
	ALLEGRO_COLOR border_color, inner_border_color, fill_color;

	UIFrame(float x, float y, float w, float h, ALLEGRO_FONT *font=NULL, std::string text="");
};

void ui_frame_default_draw(void *obj, void *user=NULL);





#endif