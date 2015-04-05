



#include <flare_gui/scroll_area.h>
#include <flare_gui/slider.h>



FGUIScrollView::FGUIScrollView(FGUIParent *parent, float x, float y, float w, float h, FGUIParent *content_parent)
	: FGUIParent(parent, new FGUICollisionBox(x, y, w, h))
	, canvas(content_parent)
	, v_slider(NULL)
	, canvas_render(al_create_bitmap(w, h))
{
	if (canvas) FGUIChildren::assign_child_to_new_parent(canvas, this); // I believe this usage is the proper design.

	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScrollView");
	attr.set("id", "ScrollView" + tostring(widget_count));

	v_slider = new FGUIVerticalSlider(this, w, 0, 16, h);
	v_slider->place.align = vec2d(1, 0);
}



FGUIParent *FGUIScrollView::get_canvas()
{
	return canvas;
}



void FGUIScrollView::render_canvas()
{
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_TRANSFORM);

	ALLEGRO_TRANSFORM ident;
	al_identity_transform(&ident);
	al_use_transform(&ident);

	al_set_target_bitmap(canvas_render);
	al_clear_to_color(color::mix(color::coral, color::transparent, 1.0));


	canvas->draw_func();


	al_restore_state(&state);
}



void FGUIScrollView::mouse_axes_func(float mx, float my, float mdx, float mdy)
{
	float tmx = mx;
	float tmy = my;
	float tmdx = mdx;
	float tmdy = mdy;

	if (!collision_area->collides(mx, my))
	{
		parent->mouse_blocked = true; // TODO: this works, but I don't think it's "correct"
										// e.g. what if there is no parent?
	}
	else
	{
		//std::cout << ".";
	}

	FGUIParent::mouse_axes_func(tmx, tmy, tmdx, tmdy);
}



void FGUIScrollView::on_timer()
{
	if (canvas)
		canvas->place.position.y = v_slider->get_val(-(canvas->place.size.y-place.size.y), 0);
	FGUIParent::on_timer();
}



void FGUIScrollView::on_mouse_wheel()
{
	if (focused && !v_slider->is_focused())
		v_slider->set_val(v_slider->get_val() + af::current_event->mouse.dz * v_slider->wheel_sensitivity);
}



void FGUIScrollView::draw_func()
{
	// render the canvas
	if (canvas) render_canvas();

	// draw the inset, canvas_render, and children, but do not draw the canvas child widget;
	place.start_transform();

	FGUIWidget::draw_inset(0, 0, place.size.x, place.size.y);
	if (canvas) al_draw_bitmap(canvas_render, 0, 0, NULL);

	// draw the overhead shade
	draw_stretched_bitmap(1, 1, place.size.x-1, std::min(place.size.y, 16.0f), af::bitmaps["shade_down.png"], ::ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.2));
		
	children.draw_all_except(canvas); // except the canvas?

	place.restore_transform();
}


