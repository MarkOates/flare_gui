

#include <flare_gui/style_assets.h>
#include <allegro_flare/generate_textures.h>



StyleAssets::StyleAssets()
	: shade_down_circle_gradient(NULL)
	, shade_down_gradient(NULL)
{
	instance = this;
}



StyleAssets::~StyleAssets()
{
	al_destroy_bitmap(shade_down_circle_gradient);
	al_destroy_bitmap(shade_down_gradient);
}



ALLEGRO_BITMAP *StyleAssets::get_shade_down_circle_gradient()
{
	if (!shade_down_circle_gradient)
		shade_down_circle_gradient = generate_circle_gradient_bitmap();
	return shade_down_circle_gradient;
}	



ALLEGRO_BITMAP *StyleAssets::get_shade_down_gradient()
{
	if (!shade_down_gradient)
		shade_down_gradient = generate_gradient_bitmap();
	return shade_down_gradient;
}	



StyleAssets *StyleAssets::instance = NULL;



