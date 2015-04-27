#ifndef FGUI_CHECKBOX_HEADER
#define FGUI_CHECKBOX_HEADER



#include <flare_gui/widget.h>




class FGUICheckbox : public FGUIWidget
{
private:
	bool checked;
	placement2d check_placement;
	float check_opacity;
public:
	FGUICheckbox(FGUIWidget *parent, float x, float y, float size);

	// used
	void on_mouse_down();
	void on_key_char();
	void on_joy_down();
	void on_draw();

	void toggle();
	bool is_checked();
};





#endif
