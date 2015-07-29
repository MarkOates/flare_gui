#ifndef __FGUI_STYLE_ASSETS_HEADER
#define __FGUI_STYLE_ASSETS_HEADER




#include <allegro5/allegro.h>


class FGUIStyleAssets
{
private:
	ALLEGRO_BITMAP *shade_down_circle_gradient;
	ALLEGRO_BITMAP *shade_down_gradient;
	static FGUIStyleAssets *instance;

	FGUIStyleAssets();
	~FGUIStyleAssets();

	static FGUIStyleAssets *get_instance();

public:
	static ALLEGRO_BITMAP *get_shade_down_circle_gradient();
	static ALLEGRO_BITMAP *get_shade_down_gradient();
};




#endif

