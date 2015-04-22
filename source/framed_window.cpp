



#include <allegro_flare/allegro_flare.h>

#include <flare_gui/framed_window.h>
#include <flare_gui/collision_box_padded.h>



FGUIFramedWindow::FGUIFramedWindow(FGUIParent *parent, float x, float y, float w, float h)
	: FGUIParent(parent, new FGUICollisionBoxPadded(x, y, w, h, 30+6, 6, 6, 6))
	, titlebar_dragger(NULL)
	, titlebar_height(30)
	, frame_thickness(6)
	, window_title("Window")
	, close_button(NULL)
{
	// it might be nice to have an FGUIWindowFrame, and should behave like a separate widget that
	// is derived from FGUIWindow (or any other widget for that matter, actually.)

	titlebar_dragger = new FGUIDraggableRegion(this, 0, -titlebar_height, place.size.x, titlebar_height);
	titlebar_dragger->place.align = vec2d(0, 0);

	// create the close button in the top right of the window
	float close_button_width = 16;
	close_button = new FGUIButton(this, "", place.size.x-close_button_width/2, 0-frame_thickness*2-close_button_width/2,
		close_button_width, close_button_width);
	close_button->attr.set("on_click_send_message", "close");
}



void FGUIFramedWindow::draw_window_frame_around(float x1, float y1, float x2, float y2)
{
	ALLEGRO_COLOR frame_color = color::color(color::hex("8e283e"), 0.6);

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



void FGUIFramedWindow::receive_message(std::string message)
	// when implemented in FGUIWindowFrame, on_draw() should not need to be overridden at all
{
	if (message == "close") this->delete_me = true;
}



void FGUIFramedWindow::on_draw() 
	// ultimately when implemented as FGUIWindowFrame, on_draw() should not need to be overridden at all
{
	// draw the background of the window
	FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);

	// draw the window's regular widgets
	FGUIWidget::on_draw();

	// draw the frame
	draw_window_frame_around(0, 0, place.size.x, place.size.y);

	// draw the title text
	al_draw_text(af::fonts["DroidSans.ttf 16"], color::black, 6+1, -25+2, 0, window_title.c_str());
	al_draw_text(af::fonts["DroidSans.ttf 16"], color::white, 6, -25, 0, window_title.c_str());
}



void FGUIFramedWindow::on_focus() 
{
	bring_to_front();
}



void FGUIFramedWindow::set_title(std::string title)
{
	window_title = title;
}




