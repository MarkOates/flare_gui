#ifndef __FGUI_STYLE_ASSETS_HEADER
#define __FGUI_STYLE_ASSETS_HEADER




#include <allegro5/allegro.h>


class StyleAssets
{
private:
	ALLEGRO_BITMAP *shade_down_circle_gradient;
	ALLEGRO_BITMAP *shade_down_gradient;
	static StyleAssets *instance;

	StyleAssets();
	~StyleAssets();

public:
	ALLEGRO_BITMAP *get_shade_down_circle_gradient();
	ALLEGRO_BITMAP *get_shade_down_gradient();
};




#endif

