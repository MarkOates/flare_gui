#ifndef __AFGUI_MUSIC_NOTATION_HEADER
#define __AFGUI_MUSIC_NOTATION_HEADER




#include <flare_gui/widget.h>

#include <allegro_flare/music_notation.h>



class FGUIMusicNotation : public FGUIWidget
{
protected:
	MusicNotation notation;
	std::string val;

public:
	FGUIMusicNotation(FGUIWidget *parent, float x, float y);

	std::string get_val();
	void set_val(std::string);

	void on_draw() override;
};




#endif
