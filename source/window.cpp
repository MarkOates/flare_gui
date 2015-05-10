




#include <flare_gui/widgets/window.h>

#include <allegro_flare/allegro_flare.h> // for tostring and af:: bins

#include <flare_gui/surface_areas/box.h>




FGUIWindow::FGUIWindow(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
	, background_color(color::hex("3a3c47"))
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIWindow");
	attr.set("id", "Window" + tostring(get_num_created_widgets()));

	no_focus = true;
}





void FGUIWindow::on_draw()
{
	FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
	draw_textured_rectangle(1, 1, place.size.x-1, place.size.y-1, af::bitmaps["rough.jpg"], color::color(color::white, 0.1));
}





void FGUIWindow::on_focus()
{
	if (attr.has("bring_to_front_on_focus")) bring_to_front();
}



