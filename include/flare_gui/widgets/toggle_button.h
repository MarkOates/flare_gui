#ifndef __FGUI_TOGGLE_BUTTON_HEADER
#define __FGUI_TOGGLE_BUTTON_HEADER




#include <string>

#include <flare_gui/widget.h>




class FGUIToggleButton : public FGUIWidget
{
protected:
	bool pressed;
	std::string text;

public:
	FGUIToggleButton(FGUIWidget *parent, float x, float y, float w, float h, std::string _text="");

	void set_text(std::string text);
	void toggle();

	void on_draw() override;
	void on_click() override;
	void on_change() override;
};





#endif

