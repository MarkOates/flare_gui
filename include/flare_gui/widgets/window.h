#ifndef FGUI_WINDOW_HEADER
#define FGUI_WINDOW_HEADER




#include <flare_gui/widget.h>




class FGUIWindow : public FGUIWidget
{
public:
	ALLEGRO_COLOR background_color;

	FGUIWindow(FGUIWidget *parent, float x, float y, float w, float h);

	void on_draw() override;
	void on_focus() override;
};




#endif
