#ifndef __AF_TEXTURES_HEADER
#define __AF_TEXTURES_HEADER



#include <allegro5/allegro.h>
#include <allegro_flare/useful.h>


extern ALLEGRO_BITMAP *wood_texture;
extern ALLEGRO_BITMAP *noise_texture;
extern ALLEGRO_BITMAP *gradient_texture;
extern ALLEGRO_BITMAP *brush_metal_texture;


void generate_textures();
void draw_interpolator_graph(float(* interpolator_func)(float), float x, float y, float size=100);


void af_draw_textured_rectangle(float x, float y, float x2, float y2, ALLEGRO_BITMAP *texture);


//void curve_it(ALLEGRO_BITMAP *img);
void apply_curves(ALLEGRO_BITMAP *img, float(* interpolator_func)(float));




#endif











//#include "textures.h"


#include <allegro5/allegro.h>
#include <allegro_flare/useful.h>
#include <allegro_flare/interpolators.h>
#include <allegro5/allegro_color.h>



ALLEGRO_BITMAP *wood_texture = NULL;
ALLEGRO_BITMAP *noise_texture = NULL;
ALLEGRO_BITMAP *gradient_texture = NULL;
ALLEGRO_BITMAP *brush_metal_texture = NULL;


static void __generate_noise_texture(float w, float h)
{
	if(noise_texture) al_destroy_bitmap(noise_texture);

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

	noise_texture = al_create_bitmap(w, h);

	al_set_target_bitmap(noise_texture);
	al_lock_bitmap(noise_texture, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);
	for (int x=0; x<w; x++)
	{
		for (int y=0; y<h; y++)
		{
			float val = random_float(0.5, 0.7);
			al_put_pixel(x, y, al_map_rgba_f(val, val, val, 1.0));
		}
	}
	al_unlock_bitmap(noise_texture);

	al_restore_state(&state);
}



static void __generate_gradient_texture(float w, float h)
{
	if (gradient_texture) al_destroy_bitmap(gradient_texture);
	gradient_texture = al_create_bitmap(w, h);

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);


	al_set_target_bitmap(gradient_texture);
	al_lock_bitmap(gradient_texture, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);
	for (int y=0; y<h; y++)
	{
		float val = 1.0 - (float)y/h;
		for (int x=0; x<w; x++)
		{
			al_put_pixel(x, y, al_map_rgba_f(val, val, val, 1.0));
		}
	}
	al_unlock_bitmap(gradient_texture);



	al_restore_state(&state);
}



static void __generate_wood_texture(float w, float h)
{
	float h_stretch = 12;
	float angle = 1.0;
	ALLEGRO_STATE state;

	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);



	if (wood_texture) al_destroy_bitmap(wood_texture);
		
	wood_texture = al_create_bitmap(w, h);
	al_set_target_bitmap(wood_texture);

	al_clear_to_color(al_color_name("sienna"));


	//al_draw_tinted_bitmap(gradient_texture, color("white", 0.3), 0, 0, NULL);


	// subtraction blender! :D
	//al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE);
	//al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
	al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

	al_draw_tinted_scaled_bitmap(noise_texture, color("white", 1.0), -300, -300, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
		0, 0, al_get_bitmap_width(noise_texture)*h_stretch*1.736, al_get_bitmap_height(noise_texture)*2, NULL);

	al_draw_tinted_bitmap(noise_texture, color("white", 0.2), -200, -200, NULL);

	// additive blender! :D
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

	al_draw_tinted_scaled_bitmap(noise_texture, color("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
		0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture), NULL);




	al_restore_state(&state);
}

#include <iostream>

static void __generate_brush_metal_texture(int w, int h)
{
	float h_stretch = 1.0;
	float v_stretch = 26.0;
	float angle = 1.0;
	ALLEGRO_STATE state;
	ALLEGRO_BITMAP *&tex = brush_metal_texture;
	//*tex = *brush_metal_texture;

	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);




	if (tex) al_destroy_bitmap(tex);
		
	tex = al_create_bitmap(w, h);
	al_set_target_bitmap(tex);

	al_clear_to_color(al_color_name("white"));


	al_draw_tinted_bitmap(gradient_texture, color("white", 0.1), 0, 0, NULL);


	// subtraction blender! :D
	//al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE);
	//al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
	al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

	al_draw_tinted_scaled_bitmap(noise_texture, color("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
		0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture)*v_stretch, NULL);

	al_draw_tinted_bitmap(noise_texture, color("white", 0.1), -200, -200, NULL);

	// additive blender! :D
	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

	//al_draw_tinted_scaled_bitmap(noise_texture, color("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
	//	0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture), NULL);


	std::cout << "called!";


	al_restore_state(&state);
}



void draw_interpolator_graph(float(* interpolator_func)(float), float x, float y, float size)
{
	float padding = size*0.2;
	float line_width = size/100.0;
	float roundness = 6;

	float w = size;
	float h = size;

	al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, al_color_name("seashell"));
	al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, al_color_name("rosybrown"), line_width);
	
	//al_draw_rectangle(x+padding, y+padding, x+w-padding, y+h-padding, al_color_name("rosybrown"), line_width);

	float offset_y = h;

	x += padding;
	y += padding;
	w -= padding*2;
	h -= padding*2;

	//y *= -1;
	h *= -1;

	int num_points = 50;
	for (int i=0; i<=(num_points-1); i++)
	{
		float point_x = (float)i/(num_points-1);
		float point_y = interpolator_func(point_x);

		point_x *= (size-padding*2);
		point_y *= -(size-padding*2);

		point_x += x;
		point_y += y+(size-padding*2);

		al_draw_filled_circle(point_x, point_y, line_width*1.3, al_color_name("saddlebrown"));
	}
}



void process_color(ALLEGRO_COLOR &col, float(* interpolator_func)(float))
{
	col.r = interpolator_func(col.r);
	col.g = interpolator_func(col.g);
	col.b = interpolator_func(col.b);
	col.a = interpolator_func(col.a);
}



void apply_curves(ALLEGRO_BITMAP *img, float(* interpolator_func)(float))
{
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	ALLEGRO_COLOR col;



	al_set_target_bitmap(img);
	al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);
	for (int y=0; y<al_get_bitmap_height(img); y++)
	{
		float val = 1.0 - (float)y/al_get_bitmap_height(img);
		for (int x=0; x<al_get_bitmap_width(img); x++)
		{
			col = al_get_pixel(img, x, y);
			process_color(col, interpolator_func);
			al_put_pixel(x, y, col);
		}
	}
	al_unlock_bitmap(img);



	al_restore_state(&state);
}




void generate_textures()
{
	__generate_noise_texture(800, 600);
	__generate_gradient_texture(300, 300);
	__generate_wood_texture(300, 300);
	__generate_brush_metal_texture(300, 300);
}






static void __build_vertex(ALLEGRO_VERTEX &vertex, float x, float y, float z, float u, float v, ALLEGRO_COLOR color)
{
	vertex.x = x;
	vertex.y = y;
	vertex.u = u;
	vertex.v = v;
	vertex.z = z;
	vertex.color = color;
}

void af_draw_textured_rectangle(float x, float y, float x2, float y2, ALLEGRO_BITMAP *texture)
{
	ALLEGRO_VERTEX vertex[4];

	if (!texture) return;
	__build_vertex(vertex[0], x, y, 0, x, y, color("white"));
	__build_vertex(vertex[1], x2, y, 0, x2, y, color("white"));
	__build_vertex(vertex[2], x2, y2, 0, x2, y2, color("white"));
	__build_vertex(vertex[3], x, y2, 0, x, y2, color("white"));

	al_draw_prim(vertex, NULL, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}


