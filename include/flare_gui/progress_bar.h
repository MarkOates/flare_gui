#ifndef __FGUI_PROGRESS_BAR_HEADER
#define __FGUI_PROGRESS_BAR_HEADER



#include <flare_gui/widget.h>


class FGUIProgressBar : public FGUIWidget
{
private:
	float val; // val from [0 - 1]
	float update_speed;
	ALLEGRO_COLOR current_color;
	ALLEGRO_COLOR normal_color;
	ALLEGRO_COLOR update_color;
public:
	FGUIProgressBar(FGUIParent *parent, float x, float y, float w, float h);
	void set_val(float normalized_val);
	void set_val(float _val, float min, float max);
	void set_update_speed(float speed_in_sec=0.4);
	void on_draw() override;
};



#endif
