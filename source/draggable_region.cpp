



#include <flare_gui/draggable_region.h>



#include <allegro_flare/color.h>

#include <allegro5/allegro_primitives.h>

#include <flare_gui/collision_box.h>
#include <flare_gui/widget_parent.h>


std::string tostring(int v); // so as not to have to declare  #include <allegro_flare/useful.h>




FGUIDraggableRegion::FGUIDraggableRegion(FGUIParent *parent, float x, float y, float w, float h)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIDraggableRegion");
	attr.set("id", "DraggableRegion" + tostring(widget_count));
}



void FGUIDraggableRegion::on_draw()
{
	placement2d *placement = gimmie_placement();
	al_draw_filled_rounded_rectangle(0, 0, placement->size.x, placement->size.y, 5, 5, color::color(color::black, 0.1));
}



void FGUIDraggableRegion::on_drag(float x, float y, float dx, float dy)
{
	if (parent)
	{
		placement2d *parent_placement = parent->gimmie_placement();
		parent_placement->position.x += dx;
		parent_placement->position.y += dy;
	}
}
