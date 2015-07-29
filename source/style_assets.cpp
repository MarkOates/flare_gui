

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




//
// bitmaps
//


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




//
// fonts
//


ALLEGRO_FONT *FGUIStyleAssets::get_title_font()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->title_font)
	{
		inst->title_font = al_load_font("data/fonts/DroidSans.ttf", 28, 0);
		if (!inst->title_font)
		{
			std::cout << "get_title_font(): Could not load font file. using fallback font." << std::endl;
			inst->title_font = al_create_builtin_font();
		} 
	}
	return inst->title_font;
}



ALLEGRO_FONT *FGUIStyleAssets::get_ui_font()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->ui_font)
	{
		inst->ui_font = al_load_font("data/fonts/DroidSans.ttf", 15, 0);
		if (!inst->ui_font)
		{
			std::cout << "get_ui_font(): Could not load font file. using fallback font." << std::endl;
			inst->ui_font = al_create_builtin_font();
		} 
	}
	return inst->ui_font;
}



ALLEGRO_FONT *FGUIStyleAssets::get_mini_font()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->mini_font)
	{
		inst->mini_font = al_load_font("data/fonts/DroidSans.ttf", 14, 0);
		if (!inst->mini_font)
		{
			std::cout << "get_mini_font(): Could not load font file. using fallback font." << std::endl;
			inst->mini_font = al_create_builtin_font();
		} 
	}
	return inst->mini_font;
}



ALLEGRO_FONT *FGUIStyleAssets::get_micro_font()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->micro_font)
	{
		inst->micro_font = al_load_font("data/fonts/DroidSans.ttf", 10, 0);
		if (!inst->micro_font)
		{
			std::cout << "get_micro_font(): Could not load font file. Using fallback font." << std::endl;
			inst->micro_font = al_create_builtin_font();
		} 
	}
	return inst->micro_font;
}




FGUIStyleAssets *FGUIStyleAssets::instance = NULL;



