#ifndef FGUI_CHECKBOX_HEADER
#define FGUI_CHECKBOX_HEADER



#include <flare_gui/widget.h>




class FGUICheckbox : public FGUIWidget
{
private:
	bool checked;
	placement2d check_placement;
	ALLEGRO_COLOR check_color;
	float check_opacity;

public:
	FGUICheckbox(FGUIWidget *parent, float x, float y, float size);

	void toggle();
	bool is_checked();
	void set_color(ALLEGRO_COLOR color);

	void on_mouse_down() override;
	void on_key_char() override;
	void on_joy_down() override;
	void on_draw() override;
};





#endif