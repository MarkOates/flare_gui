

#include <flare_gui/flare_gui.h>



/*

== framed_window_ex.cpp ==

simple example program of how a framed window might be implemented

*/





class FGUIFramedWindow : public FGUIWindow
{
public:
	FGUIDraggableRegion *titlebar_dragger;
	float titlebar_height;
	float frame_thickness;
	std::string window_title;
	FGUIButton *close_button;

	FGUIFramedWindow(FGUIParent *parent, float x, float y, float w, float h)
		: FGUIWindow(parent, x, y, w, h)
		, titlebar_dragger(NULL)
		, titlebar_height(30)
		, frame_thickness(6)
		, window_title("Window")
		, close_button(NULL)
	{
		// todo: there's a bug whereby clicking on the frame also clicks through to any underlying widget.
		// ultimately, this should be a FGUIWindowFrame, and should behave like a separate widget that
		// is derived from FGUIWindow (or any other widget for that matter, actually.)

		titlebar_dragger = new FGUIDraggableRegion(this, 0, -titlebar_height, place.size.x, titlebar_height);
		titlebar_dragger->place.align = vec2d(0, 0);

		float close_button_width = 16;
		close_button = new FGUIButton(this, "", NULL,
			place.size.x-close_button_width/2, 0-frame_thickness*2-close_button_width/2,
			close_button_width, close_button_width);
		close_button->attr.set("on_click_send_message", "close");
	}
	void draw_window_frame_around(float x1, float y1, float x2, float y2)
	{
		FGUIWindow::on_draw();

		ALLEGRO_COLOR frame_color = color::color(color::hex("8e283e"), 0.3);

		// titlebar
		al_draw_filled_rectangle(x1-frame_thickness, y1-frame_thickness-titlebar_height, x2+frame_thickness, y1, frame_color);

		// frame
		al_draw_filled_rectangle(x1-frame_thickness, y1, x1, y2, frame_color); // left
		al_draw_filled_rectangle(x2, y1, x2+frame_thickness, y2, frame_color); // right
		al_draw_filled_rectangle(x1-frame_thickness, y2, x2+frame_thickness, y2+frame_thickness, frame_color); // bottom

		// inset frame shadow
		ALLEGRO_COLOR frame_outline_color = color::color(color::white, 0.2);
		al_draw_rectangle(x1-frame_thickness+0.5, y1-frame_thickness-titlebar_height+0.5,
			x2+frame_thickness-0.5, y2+frame_thickness-0.5, frame_outline_color, 1.0);
	}
	void receive_message(std::string message)
		// when implemented in FGUIWindowFrame, on_draw() should not need to be overridden at all
	{
		if (message == "close") this->delete_me = true;
	}
	void on_draw() override
		// ultimately when implemented as FGUIWindowFrame, on_draw() should not need to be overridden at all
	{
		// draw the window's regular widgets
		FGUIWindow::on_draw();

		// draw the frame
		draw_window_frame_around(0, 0, place.size.x, place.size.y);

		// draw the title text
		al_draw_text(af::fonts["DroidSans.ttf 16"], color::black, 6+1, -25+2, 0, window_title.c_str());
		al_draw_text(af::fonts["DroidSans.ttf 16"], color::white, 6, -25, 0, window_title.c_str());
	}
};




class Project : public FGUIScreen
{
public:
	Project(Display *display)
		: FGUIScreen(display)
	{
		draw_focused_outline = false;
		new FGUIFramedWindow(this, 200, 200, 300, 200);
		new FGUIFramedWindow(this, 280, 300, 100, 80);
		new FGUIFramedWindow(this, 570, 280, 400, 320);
	}
};




int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display(800, 500);
	Project *proj = new Project(display);
	af::run_loop();
}
