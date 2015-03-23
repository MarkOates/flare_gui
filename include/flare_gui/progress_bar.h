#ifndef __FGUI_PROGRESS_BAR_HEADER
#define __FGUI_PROGRESS_BAR_HEADER



#include <flare_gui/widget.h>


class FGUIProgressBar : public FGUIWidget
{
private:
	float val; // val from [0 - 1]
	ALLEGRO_COLOR current_color;
	ALLEGRO_COLOR normal_color;
	ALLEGRO_COLOR update_color;
public:
	FGUIProgressBar(FGUIParent *parent, float x, float y, float w=300, float h=26, float val=0.6);
	void set_val(float normalized_val, float update_speed=0.5);
	void set_val(float _val, float min, float max, float update_speed=0.5);
	void on_draw() override;
};



#endif