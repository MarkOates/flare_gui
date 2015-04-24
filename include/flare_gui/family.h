#ifndef __FGUI_FAMILY_HEADER
#define __FGUI_FAMILY_HEADER



#include <flare_gui/children.h>


class FGUIWidget;



class FGUIFamily : public FGUIChildren
{
public:
	FGUIWidget *progenitor;
	FGUIWidget *parent;

	FGUIFamily(FGUIWidget *parent);

	bool set_focus_to_child(FGUIWidget *child);
};




#endif
