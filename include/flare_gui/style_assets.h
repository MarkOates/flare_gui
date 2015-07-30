#ifndef __FGUI_STYLE_ASSETS_HEADER
#define __FGUI_STYLE_ASSETS_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <allegro_flare/color.h> // should be removed eventually



class FGUIStyleAssets
{
private:
	ALLEGRO_BITMAP *shade_down_circle_gradient;
	ALLEGRO_BITMAP *shade_down_gradient;
	ALLEGRO_BITMAP *widget_icon;

	ALLEGRO_FONT *title_font;
	ALLEGRO_FONT *ui_font;
	ALLEGRO_FONT *mini_font;
	ALLEGRO_FONT *micro_font;

	static FGUIStyleAssets *instance;

	FGUIStyleAssets();
	~FGUIStyleAssets();

	static FGUIStyleAssets *get_instance();

	static ALLEGRO_BITMAP *generate_widget_icon(int size, ALLEGRO_COLOR front_color, ALLEGRO_COLOR back_color);

public:
	static ALLEGRO_BITMAP *get_shade_down_circle_gradient();
	static ALLEGRO_BITMAP *get_shade_down_gradient();

	static ALLEGRO_FONT *get_title_font();
	static ALLEGRO_FONT *get_ui_font();
	static ALLEGRO_FONT *get_mini_font();
	static ALLEGRO_FONT *get_micro_font();

	static void draw_inset(float x, float y, float w, float h, ALLEGRO_COLOR col=color::hex("575962"), float roundness=2);
	static void draw_outset(float x, float y, float w, float h, ALLEGRO_COLOR col=color::hex("575962"), float roundness=2);
	static ALLEGRO_BITMAP *get_widget_icon();
};




#endif
