

#include <flare_gui/style_assets.h>
#include <allegro_flare/generate_textures.h>



FGUIStyleAssets::FGUIStyleAssets()
	: shade_down_circle_gradient(NULL)
	, shade_down_gradient(NULL)
{
	instance = this;
}



FGUIStyleAssets::~FGUIStyleAssets()
{
	al_destroy_bitmap(shade_down_circle_gradient);
	al_destroy_bitmap(shade_down_gradient);
}



FGUIStyleAssets *FGUIStyleAssets::get_instance()
{
	if (!instance) instance = new FGUIStyleAssets();
	return instance;
}



ALLEGRO_BITMAP *FGUIStyleAssets::get_shade_down_circle_gradient()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->shade_down_circle_gradient)
		inst->shade_down_circle_gradient = generate_circle_gradient_bitmap();
	return inst->shade_down_circle_gradient;
}	



ALLEGRO_BITMAP *FGUIStyleAssets::get_shade_down_gradient()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->shade_down_gradient)
		inst->shade_down_gradient = generate_gradient_bitmap();
	return inst->shade_down_gradient;
}	



FGUIStyleAssets *FGUIStyleAssets::instance = NULL;



