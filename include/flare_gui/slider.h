#ifndef __AFGUI_SLIDER_HEADER
#define __AFGUI_SLIDER_HEADER





#include <flare_gui/flare_gui.h>






class FGUIVerticalSlider : public FGUIWidget
{
protected:
	float val;
	float mouse_y;
	int num_notches;

public:
	FGUIVerticalSlider(FGUIParent *parent, float x, float y, float w, float h);

	float wheel_sensitivity;

	void set_notches(int num_notches);
	void on_draw();
	void set_val_by_y(float y);
	void set_val(float val);
	float get_val();
	float get_val(float min, float max); // a helper function, places the normalized value within the [min-max] domain.
	void on_mouse_move(float x, float y, float dx, float dy);
	void on_mouse_down();
	void on_drag(float x, float y, float dx, float dy);
	void on_key_char();
	void on_mouse_wheel();

	virtual void on_change();
};









#endif