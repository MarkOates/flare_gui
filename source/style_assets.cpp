

#include <flare_gui/style_assets.h>

#include <allegro_flare/generate_textures.h>
#include <allegro_flare/image_processing.h>



FGUIStyleAssets::FGUIStyleAssets()
	: shade_down_circle_gradient(NULL)
	, shade_down_gradient(NULL)
	, widget_icon(NULL)
	, title_font(NULL)
	, text_font(NULL)
	, ui_font(NULL)
	, mini_font(NULL)
	, micro_font(NULL)
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



ALLEGRO_BITMAP *FGUIStyleAssets::get_widget_icon()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->widget_icon)
		inst->widget_icon = generate_widget_icon(64, color::white, color::transparent);
	return inst->widget_icon;
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



ALLEGRO_FONT *FGUIStyleAssets::get_text_font()
{
	FGUIStyleAssets *inst = get_instance();
	if (!inst->text_font)
	{
		inst->text_font = al_load_font("data/fonts/DroidSans.ttf", 18, 0);
		if (!inst->text_font)
		{
			std::cout << "get_text_font(): Could not load font file. using fallback font." << std::endl;
			inst->text_font = al_create_builtin_font();
		}
	}
	return inst->text_font;
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





//
// shapes
//


void FGUIStyleAssets::draw_inset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
	// draw the background
	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2));

	// draw a nice shade at the top (maybe this shoud be a 9-patch?... maybe not :)
	//draw_stretched_bitmap(1, 1, w-1, min(h, 16), (gimmie_super_screen()->bitmaps)["shade_down.png"], ::ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.2));


	// draw the top line shadow
	al_draw_line(x+roundness, y, x+w-roundness, y, color::color(color::black, 0.3), 1.0);

	// draw the bottom line hilight
	al_draw_line(x+roundness, y+h+1, x+w-roundness, y+h+1, color::color(color::white, 0.3), 1.0);
}



void FGUIStyleAssets::draw_outset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
	float border_thickness = 2.0;
	float texture_inset = border_thickness/2;

	// the button face
	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, col);//color::hex("575962"));

	// draw a hilight along the top
	al_draw_line(x+1, y+1, x+w-1, y+1, color::color(color::white, 0.1), 1);

	// the button outline
	al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2), border_thickness);

	// draw the shaded bitmap
	ALLEGRO_BITMAP *shade_down = FGUIStyleAssets::get_shade_down_gradient();
	draw_stretched_bitmap(x+texture_inset, y+texture_inset, x+w-texture_inset*2, y+h-texture_inset*2, shade_down, 0, color::color(color::white, 0.2));
}



//
// internal
//


ALLEGRO_BITMAP *FGUIStyleAssets::generate_widget_icon(int size, ALLEGRO_COLOR front_color, ALLEGRO_COLOR back_color)
{
	float scale = 4.0; // 4.0 is essentially equivelent to 4x FSAA
	size *= scale;

	ALLEGRO_BITMAP *surface = al_create_bitmap(size, size);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(surface);
	al_clear_to_color(back_color);

	// draw stuff here
	float gear_scale = size / 64.0;
	float gear_radius = size/2;
	float inner_gear_thickness = 10.5 * gear_scale;
	float hw = 4 * gear_scale;
	float hh = 2.5 * gear_scale;

	int num_gears = 9;

	placement2d gear_place;
	gear_place.position = vec2d(size/2, size/2);
	gear_place.anchor = vec2d(0, gear_radius);

	al_draw_circle(size/2, size/2, gear_radius-hh*2-inner_gear_thickness/2, front_color, inner_gear_thickness);
	for (auto i=0; i<num_gears; i++)
	{
		gear_place.start_transform();
		al_draw_filled_rectangle(-hw, -hh*2-inner_gear_thickness*0.05, hw, 0, front_color);
		gear_place.restore_transform();
		gear_place.rotation += TAU/num_gears;
	}

	al_restore_state(&state);

	ALLEGRO_BITMAP *scaled = create_scaled_render(surface, size/scale, size/scale);

	al_destroy_bitmap(surface);

	return scaled;
}




FGUIStyleAssets *FGUIStyleAssets::instance = NULL;



