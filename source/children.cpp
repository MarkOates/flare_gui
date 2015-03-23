

#include <flare_gui/children.h>
#include <flare_gui/widget_parent.h>



void FGUIChildren::register_as_child(FGUIWidget *widget)
{
	if (!widget) return;

	if (!has_child(widget))
	{
		children.push_back(widget);
		//widget->parent = this; // yikes! just took this out
	}
}



#include <iostream>
void FGUIChildren::unregister_as_child(FGUIWidget *widget)
{
	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i] == widget)
		{
			children.erase(children.begin()+i);
			std::cout << "[FGUIChildren::detach_widget()] widget found and detached successfully." << std::endl;
			return;
		}
	}
	std::cout << "[FGUIChildren::detach_widget()] error - widget not found." << std::endl;
}




bool FGUIChildren::has_child(FGUIWidget *widget)
{
	for (unsigned i=0; i<children.size(); i++)
		if (widget == children[i]) return true;
	return false;
}



bool FGUIChildren::assign_child_to_new_parent(FGUIWidget *child_widget, FGUIParent *new_parent)
{
	// have the current parent remove this child
	if (!child_widget) { std::cout << "err1" << std::endl; return false; } // TODO: fix crappy error messages

	if (child_widget->parent)
	{
		child_widget->parent->children.unregister_as_child(child_widget);
	}

	// assign the parent to the new parent
	if (new_parent)
	{
		new_parent->children.register_as_child(child_widget);
	}
	else
	{
		std::cout << "warning: registering a child to a NULL parent - (TODO: implement this functionality)" << std::endl;
		new_parent->children.register_as_child(NULL); //< is this ok?? right now, nothing really happens with this functionality
													  // it's akin to a dangling pointer and the child is left without
	}

	return true;
}



void FGUIChildren::delete_all()
{
	for (unsigned i=0; i<children.size(); i++)
	{
		delete children[i];
	}
	children.clear();
}



void FGUIChildren::unfocus_all()
{
	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i]->is_focused()) children[i]->set_as_unfocused();
	}
}



FGUIWidget *FGUIChildren::get_element_by_id(std::string id)
{
	//std::cout << "FGUIChildren::get_element_by_id(" << id << ")" << std::endl;
	//std::cout << "searching " << children.size() << " element(s)" << std::endl;

	for (unsigned i=0; i<children.size(); i++)
	{
		//std::cout << "children[" << i << "].id==" << children[i]->attr.get("id") << " " << std::endl;
		if (children[i]->attr.matches("id", id)) return children[i];
	}
	return NULL;
}



FGUIWidget *FGUIChildren::get_1st_element_with_attr(std::string key)
{
	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i]->attr.has(key)) return children[i];
	}
	return NULL;
}



FGUIWidget *FGUIChildren::get_1st_element_with_attr_val(std::string key, std::string val)
{
	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i]->attr.matches(key, val)) return children[i];
	}
	return NULL;
}





int FGUIChildren::_index_count = 0;




FGUIWidget *FGUIChildren::get_nth_child_d(int n)
{
	_index_count = 0;
	// note: the 0th child is the owner of this FGUIChildren.
	// TODO: perhaps this function should be promoted up to the Parent that calls it.
	return __get_nth_child_recursive(*this, n);
}

FGUIWidget *FGUIChildren::__get_nth_child_recursive(FGUIChildren &children, int n)
{
	FGUIWidget *widget = NULL;
	for (unsigned i=0; i<children.children.size(); i++)
	{
		_index_count++;
		if (children.children[i]->attr.matches(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIParent"))
		{
			FGUIParent *p = static_cast<FGUIParent *>(children.children[i]);
			widget = FGUIChildren::__get_nth_child_recursive(p->children, n);
			if (widget) return widget;
		}
	}
	return NULL;
}





int FGUIChildren::get_num_of_widgets_d()
{
	_index_count = 1;
	return __get_num_widgets_recursive(*this);
}

int FGUIChildren::__get_num_widgets_recursive(FGUIChildren &children)
{
	for (unsigned i=0; i<children.children.size(); i++)
	{
		_index_count++;
		if (children.children[i]->attr.matches(FGUI_ATTR__FGUI_IS_PARENT, "true"))
		{
			FGUIParent *p = static_cast<FGUIParent *>(children.children[i]);
			FGUIChildren::__get_num_widgets_recursive(p->children);
		}
	}
	return _index_count;
}





void FGUIChildren::draw_all()
{
	for (unsigned i=0; i<children.size(); i++)
		children[i]->draw_func();
}




void FGUIChildren::draw_all_except(FGUIWidget *widget)
{
	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i] != widget) children[i]->draw_func();
	}
}





/*
bool FGUIChildren::delete_child(FGUIWidget *child)
{
	// I'm not thinking this should be a function

	for (unsigned i=0; i<children.size(); i++)
	{
		if (children[i] == child)
		{
			delete children[i];
			//std::cout << "child deleted" << std::endl;
			//i--;
			return true;
		}
	}
	return false;
}

*/