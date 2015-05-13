#ifndef FGUI_NOTIFICATION_BUBBLE_HEADER
#define FGUI_NOTIFICATION_BUBBLE_HEADER



#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/color.h>

#include <flare_gui/widget.h>
#include <flare_gui/surface_areas/box.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


class FGUINotificationBubble : public FGUIWidget
{
private:
	std::string text;
	bool paused;
	float spawn_time, lifespan;
	float opacity;
	ALLEGRO_FONT *font;

public:
	FGUINotificationBubble(FGUIWidget *parent, float x, float y, std::string text)
		: FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 280, 90))
		, text(text)
		, font(af::fonts["DroidSerif.ttf 20"])
		, spawn_time(af::time_now)
		, lifespan(4.0)
		, paused(false)
		, opacity(0)
	{
		attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUINotificationBubble");
		attr.set("id", "NotificationBubble" + tostring(FGUIWidget::get_num_created_widgets()));

		af::motion.cmove_to(&this->opacity, 1.0, 0.5);

		this->surface_area->placement.align.x = 1.0;
		this->surface_area->placement.align.y = 1.0;
	}

	~FGUINotificationBubble()
	{
		af::motion.clear_animations_on(&this->opacity);
	}

	void on_timer()
	{
		if (paused || delete_me) return;

		if ((af::time_now - spawn_time) > lifespan)
		{
			delete_me = true;
			af::motion.cmove_to(&this->opacity, 0, 0.6);
		}
	}

	void on_mouse_enter()
	{
		if (delete_me) return;

		paused = true;
		af::motion.cmove_to(&this->opacity, 1.0, 0.5);
	}

	void on_mouse_leave()
	{
		if (delete_me) return;

		paused = false;
		spawn_time  = af::time_now;
	}

	void on_draw()
	{
		if (delete_me) return;

		al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 6, 6, color::hex("#fce566", opacity));
		al_draw_text(font, color::hex("645710", opacity), 23, 20, 0, text.c_str());
	}
};







#endif




// TODO: write a FGUIScreen project




int main(int argc, char *argv[])
{
	af::initialize();
	Display *display = af::create_display(1280, 800, false);


	af::run_loop();
}




