




#include <flare_gui/window.h>

#include <allegro_flare/allegro_flare.h> // for tostring and af:: bins




FGUIWindow::FGUIWindow(FGUIParent *parent, float x, float y, float w, float h)
	: FGUIParent(parent, new FGUICollisionBox(x, y, w, h))
	, background_color(color::hex("3a3c47"))
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIWindow");
	attr.set("id", "Window" + tostring(widget_count));

	no_focus = true;
}





void FGUIWindow::on_draw()
{
	// the bottom shade
	float shade_depth = 5;
	al_draw_filled_rounded_rectangle(0, place.size.y/2 + shade_depth, place.size.x, place.size.y+shade_depth, 2, 2, color::color(color::black, 0.1));

	// the button face
	al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, background_color);//color::hex("575962"));

	// the button outline
	al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2), 2);

	// draw a hilight along the top
	al_draw_line(3.5, 1, place.size.x-3.5, 1, color::color(color::white, 0.3), 1);

	// draw the shaded bitmap
	draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, af::bitmaps["shade_down.png"], 0, color::color(color::white, 0.2));
}





void FGUIWindow::on_focus()
{
	if (attr.has("bring_to_front_on_focus")) bring_to_front();
}
