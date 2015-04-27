#ifndef FGUI_WINDOW_HEADER
#define FGUI_WINDOW_HEADER




#include <deque>


#include <allegro_flare/vec2d.h>

#include <flare_gui/widget.h>
#include <flare_gui/collision_box.h>
#include <allegro_flare/color.h>
#include <allegro5/allegro_primitives.h>



class FGUIWindow : public FGUIWidget
{
public:
	ALLEGRO_COLOR background_color;

	FGUIWindow(FGUIWidget *parent, float x, float y, float w, float h);

	void on_draw();
	void on_focus();
};




#endif
