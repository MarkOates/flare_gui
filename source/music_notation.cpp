



#include <allegro5/allegro_primitives.h>

#include <allegro_flare/color.h>
#include <allegro_flare/drawing_interfaces/drawing_interface_allegro5.h>

#include <flare_gui/music_notation.h>
#include <flare_gui/collision_box.h>
#include <flare_gui/widget_parent.h>

#include <allegro_flare/useful.h>



FGUIMusicNotation::FGUIMusicNotation(FGUIWidget *parent, float x, float y)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, 300, 80))
	, notation(new DrawingInterfaceAllegro5())
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIMusicNotation");
	attr.set("id", "MusicNotation" + tostring(widget_count));
}




void FGUIMusicNotation::on_draw()
{
	placement2d &place = this->collision_area->placement;
	al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::white, mouse_over ? 0.2 : 0.1));
	place.size.x = std::max(10, notation.draw(0, place.size.y/2, content));
}

