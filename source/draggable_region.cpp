



#include <flare_gui/widgets/draggable_region.h>



#include <allegro_flare/color.h>
#include <allegro_flare/useful.h>

#include <allegro5/allegro_primitives.h>

#include <flare_gui/surface_areas/box.h>


std::string tostring(int v); // so as not to have to declare  #include <allegro_flare/useful.h>




FGUIDraggableRegion::FGUIDraggableRegion(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
	, background_color(color::color(color::black, 0.1))
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIDraggableRegion");
	attr.set("id", "DraggableRegion" + tostring<int>(FGUIWidget::get_num_created_widgets()));
}



void FGUIDraggableRegion::set_color(ALLEGRO_COLOR new_color)
{
	background_color = new_color;
}



void FGUIDraggableRegion::on_draw()
{
	al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 5, 5, background_color);
}



void FGUIDraggableRegion::on_drag(float x, float y, float dx, float dy)
{
	if (family.parent)
	{
		// This might not be the best method, that is, directly controlling the parameters
		// of a parent object.  It might interfere with other events or other actions on
		// or around the parent's parameters.  For example, if the parent is being animated, etc.
		placement2d &parent_placement = family.parent->place;
		parent_placement.position.x += dx;
		parent_placement.position.y += dy;
	}
}
