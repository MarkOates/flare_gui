#ifndef __AF_SCROLL_AREA_HEADER
#define __AF_SCROLL_AREA_HEADER




#include <allegro5/bitmap.h>

#include <flare_gui/widget_parent.h>


class FGUIVerticalSlider;


class FGUIScrollView : public FGUIParent
{
private:
	FGUIVerticalSlider *v_slider;
	FGUIParent *canvas;
	ALLEGRO_BITMAP *canvas_render;


public:
	FGUIScrollView(FGUIParent *parent, float x, float y, float w, float h, FGUIParent *content_parent);

	FGUIParent *get_canvas();
	void render_canvas();
	void mouse_axes_func(float mx, float my, float mdx, float mdy) override;
	void on_timer() override;
	void on_mouse_wheel() override;
	void draw_func();
};






#endif