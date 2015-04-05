



#include <allegro5/allegro_primitives.h>
#include <allegro_flare/allegro_flare.h>


#include <flare_gui/window.h>





#include <flare_gui/widget.h>
#include <flare_gui/collision_box.h>

#include <allegro_flare/useful.h> // just for tostring




FGUIWindow::FGUIWindow(FGUIParent *parent, float x, float y, float w, float h)
	: FGUIParent(parent, new FGUICollisionBox(x, y, w, h))
	, border_color(color::color(color::aliceblue, 0.2))
	, background_color(color::hex("3a3c47"))
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIWindow");
	attr.set("id", "Window" + tostring(widget_count));

	no_focus = true;
	//std::cout << "FGUIWindow()" << std::endl;
	//color::color(color::aliceblue, 0.2)
}



void FGUIWindow::on_mouse_enter()
{
	//border_color = color::color(color::aliceblue, 0.9);
}



void FGUIWindow::on_mouse_leave()
{
	//border_color = color::color(color::aliceblue, 0.2);
}



void FGUIWindow::on_timer()
{

}



#include <flare_gui/widget_screen.h>

void FGUIWindow::on_draw()
{
	placement2d &placement = collision_area->placement;


	// the bottom shade
	float shade_depth = 5;
	al_draw_filled_rounded_rectangle(0, placement.size.y/2 + shade_depth, placement.size.x, placement.size.y+shade_depth, 2, 2, color::color(color::black, 0.1));

	// the button face
	al_draw_filled_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, background_color);//color::hex("575962"));

	// the button outline
	al_draw_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, color::color(color::black, 0.2), 2);

	// draw a hilight along the top
	al_draw_line(3.5, 1, placement.size.x-3.5, 1, color::color(color::white, 0.3), 1);

	// draw the shaded bitmap
	draw_stretched_bitmap(3, 3, placement.size.x-6, placement.size.y-6, af::bitmaps["shade_down.png"], 0, color::color(color::white, 0.2));


	//al_draw_filled_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, background_color);
	//al_draw_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, border_color, 2.0);

	// draw the shaded bitmap
	//draw_stretched_bitmap(3, 3, placement.size.x-6, placement.size.y-6, (gimmie_super_screen()->bitmaps)["shade_down.png"], 0, color::color(color::white, 0.4));
}



void FGUIWindow::on_drag(float x, float y, float dx, float dy)
{
	// TODO: I'm not sure exactly how this should be properly implemented.
	// as it is below, it isn't working correctly (at the fault of something else not
	// being correctly implemented in the FGUIWidget and FGUIParent, I believe).
	// For now, I'm going to comment out the dragging window, and presume that,
	// if you want to drag your window (or have a window or other widget that is
	// draggable), then you should add a FGUIDraggableRegion as a child.
	//if (!mouse_blocked)
	//{
	//	placement2d &placement = collision_area->placement;
	//	placement.position.x += dx;
	//	placement.position.y += dy;
	//}
}




void FGUIWindow::on_focus()
{
	//bring_to_front();
}



/*
void FGUIWindow::timer_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->timer_func();
	//FGUIWidget::timer_func();
	FGUIWidget::timer_func();
}



void FGUIWindow::mouse_down_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->mouse_down_func();
	FGUIWidget::mouse_down_func();
}



void FGUIWindow::mouse_up_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->mouse_up_func();
	FGUIWidget::mouse_up_func();
}



void FGUIWindow::key_down_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->key_down_func();
	FGUIWidget::key_down_func();
}



void FGUIWindow::key_up_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->key_up_func();
	FGUIWidget::key_up_func();
}



void FGUIWindow::key_char_func()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->key_char_func();
	FGUIWidget::key_char_func();
}
*/