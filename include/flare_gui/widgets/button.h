#ifndef FGUI_BUTTON_HEADER
#define FGUI_BUTTON_HEADER




#include <flare_gui/widget.h>
#include <allegro_flare/motion.h>
#include <allegro5/allegro_font.h>




class FGUIButton : public FGUIWidget
{
private:
	ALLEGRO_BITMAP *icon;
	ALLEGRO_FONT *font;
	std::string text;
	float content_alignment;

public:
	FGUIButton(FGUIWidget *parent, float x, float y, float w, float h, std::string text);

	void set_text(std::string text);
	void set_icon(ALLEGRO_BITMAP *icon);
	void set_content_alignment(float alignment=0.5);

	virtual void on_timer();
	virtual void on_draw();
	virtual void on_click();
	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_key_down() override;
	virtual void on_joy_down() override;
};




#endif