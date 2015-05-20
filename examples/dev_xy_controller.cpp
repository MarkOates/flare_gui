

#include <flare_gui/flare_gui.h>

#include <limits>



class FGUIXYController : public FGUIWidget
{
private:
	vec2d mouse_pos;
	vec2d marker;
	ALLEGRO_COLOR guide_color;
	float guide_opacity;

public:
	FGUIXYController(FGUIWidget *parent, float x, float y, float w, float h)
		: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
		, mouse_pos(0)
		, marker(0.5, 0.5)
		, guide_color(color::white)
		, guide_opacity(0.3)
	{
	}
	void set_point(float x, float y)
	{
		marker = vec2d(limit<float>(0.0f, 1.0f, x), limit<float>(0.0f, 1.0f, y));
	}
	vec2d get_point()
	{
		return marker;
	}
	void on_mouse_down() override
	{
		set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);	
	}
	void on_mouse_move(float x, float y, float dx, float dy) override
	{
		place.transform_coordinates(&x, &y);
		mouse_pos = vec2d(x, y);
		
		if (mouse_down_on_over)
			set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);	
	}
	void on_draw() override
	{
		FGUIWidget::draw_inset(0, 0, place.size.x, place.size.y);

		// draw the guides
		vec2d local_marker = vec2d(marker.x * place.size.x, marker.y * place.size.y);

		ALLEGRO_COLOR guide_mixed_color = color::color(color::white, guide_opacity);
		al_draw_line(local_marker.x, 0, local_marker.x, place.size.y, color::color(color::white, guide_opacity), 1.0);
		al_draw_line(0, local_marker.y, place.size.x, local_marker.y, color::color(color::white, guide_opacity), 1.0);

		al_draw_circle(local_marker.x, local_marker.y, 10, color::color(color::dodgerblue, 0.2), 6);
	}
};




class XYControllerDevProgram : public FGUIScreen
{
public:
	XYControllerDevProgram(Display *display)
		: FGUIScreen(display)
	{
		new FGUIText(this, 100, display->height()/5, "Click in the XY Controller to set the marker.");
		FGUIXYController *controller = new FGUIXYController(this, display->width()/2, display->height()/2, 200, 200);	
	}
};




int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display(1000, 700);
	XYControllerDevProgram *rubber_band_dev = new XYControllerDevProgram(display);
	af::run_loop();
}
