



#include <flare_gui/family.h>
#include <flare_gui/widget.h>




FGUIFamily::FGUIFamily(FGUIWidget *parent)
	: FGUIChildren()
	, progenitor(NULL)
	, parent(parent)
{}


bool FGUIFamily::set_focus_to_child(FGUIWidget *widget)
{
	// make sure the child is not already focused
	if (widget && widget->is_focused()) return false;

	// if there are other widgets that have focus, blur them
	for (unsigned i=0; i<this->children.size(); i++)
	{
		if (children[i]->is_focused())
			children[i]->set_as_unfocused();
	}

	if (widget)
	{
		widget->focused = true;
		widget->on_focus();
	}

	return true;
}




