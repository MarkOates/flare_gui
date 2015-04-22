#ifndef FGUI_BUTTON_HEADER
#define FGUI_BUTTON_HEADER




#include <flare_gui/widget.h>
#include <allegro_flare/motion.h>
#include <allegro5/allegro_font.h>




class FGUIButton : public FGUIWidget
{
public:
//	MotionManager motion;
	ALLEGRO_BITMAP *icon;
	ALLEGRO_FONT *font;
	std::string text;
	//int text_alignment; // since the addition of the icon, text_alignment referes to content alignment
	float content_alignment; // since the addition of the icon, text_alignment referes to content alignment

	FGUIButton(FGUIParent *parent, float x, float y, float w, float h, std::string text);

	void set_text(std::string text);
	void set_icon(ALLEGRO_BITMAP *icon);

	virtual void on_timer();
	virtual void on_draw();
	virtual void on_click();
	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_key_down() override;
	virtual void on_joy_down() override;

	//virtual void simulate_click(); // triggers a click action
};




#endif
