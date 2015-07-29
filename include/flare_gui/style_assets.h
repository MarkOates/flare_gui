#ifndef __FGUI_STYLE_ASSETS_HEADER
#define __FGUI_STYLE_ASSETS_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


class FGUIStyleAssets
{
private:
	ALLEGRO_BITMAP *shade_down_circle_gradient;
	ALLEGRO_BITMAP *shade_down_gradient;

	ALLEGRO_FONT *title_font;
	ALLEGRO_FONT *ui_font;
	ALLEGRO_FONT *mini_font;
	ALLEGRO_FONT *micro_font;

	static FGUIStyleAssets *instance;

	FGUIStyleAssets();
	~FGUIStyleAssets();

	static FGUIStyleAssets *get_instance();

public:
	static ALLEGRO_BITMAP *get_shade_down_circle_gradient();
	static ALLEGRO_BITMAP *get_shade_down_gradient();

	static ALLEGRO_FONT *get_title_font();
	static ALLEGRO_FONT *get_ui_font();
	static ALLEGRO_FONT *get_mini_font();
	static ALLEGRO_FONT *get_micro_font();
};




#endif

