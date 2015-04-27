#ifndef __AFGUI_MUSIC_NOTATION_HEADER
#define __AFGUI_MUSIC_NOTATION_HEADER




#include <flare_gui/widget.h>

#include <allegro_flare/music_notation.h>



class FGUIMusicNotation : public FGUIWidget
{
protected:
	MusicNotation notation;
public:
	std::string content;
	FGUIMusicNotation(FGUIWidget *parent, float x, float y);
	void on_draw() override;
};




#endif
